// insert copyright and license
// insert brief overview

// standard Rpi Pico SDK libraries (included via Wizio Platform)
#include <stdint.h>
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/adc.h"

// application-specific libraries
#include "palled.h"				// all pin definitions used in various functions are here
#include "console.h"			// for the Serial I/O console (works over UART and USB)
#include "utils.h"				// handy time and heartbeat code
#include "encoders.h"			// driver for encoders
#include "ws2812.h"				// driver for WS2812 addressable LED strips
#include "ledpatterns.h"		// creates LED patterns using the WS2812 driver
#include "brightness.h"			// reads brightness from ADC, manipulates Color structure

// Encoder Structures and ISR
Encoder Right = {RIGHTA, RIGHTB, 0, 0, 0};
Encoder Middle = {MIDDLEA, MIDDLEB, 0, 0, 0};
Encoder Left = {LEFTA, LEFTB, 0, 0, 0};
volatile uint8_t enc_count_update = 0;

void isr_gpio_callback(uint gpio, uint32_t events) {

	switch (gpio) {
		case RIGHTA: {
			enc_count_update = encoder_readA(&Right);
			break;
		}
		case RIGHTB: {
			enc_count_update = encoder_readB(&Right);
			break;
		}
		case MIDDLEA: {
			enc_count_update = encoder_readA(&Middle);
			break;
		}
		case MIDDLEB: {
			enc_count_update = encoder_readB(&Middle);
			break;
		}
		case LEFTA: {
			enc_count_update = encoder_readA(&Left);
			break;
		}
		case LEFTB: {
			enc_count_update = encoder_readB(&Left);
			break;
		}
	}
}

// Color Structures and Globals
Color mainColor = {2, 0, 0};
Color solidColor = {53, 0, 62};
Color solidColor2 = {0, 53, 62};
Strip Matrix = {5, MATRIX_PIXELS, LED_MATRIX, MATRIX_SM};
Strip Ring = {5, RING_PIXELS, LED_RING, RING_SM};
Color MatrixColors[MATRIX_PIXELS] = {0};
Color RingColors[RING_PIXELS] = {0};
uint8_t gammaCorr = 1;	// toggles gamma correction for brightness on/off, used in ledpatterns.c
//enum colorState{RED, GRN, BLU};

int main() {

	// To Do: move initializations to other libs?

	// UART and onboard LED initialization
	stdio_init_all();	// UART and UART to USB setup for both input and output
	heartbeat_init();	// onboard LED blinking

	// Encoder initialization
	encoder_init(RIGHTA, RIGHTB);
	encoder_init(MIDDLEA, MIDDLEB);
	encoder_init(LEFTA, LEFTB);
	gpio_set_irq_enabled_with_callback(RIGHTA, GPIO_IRQ_EDGE_RISE, 1, &isr_gpio_callback);

	// WS2812 LED Ring initialization via PIO
	PIO pio = pio0;
    uint offset_ring = pio_add_program(pio, &ws2812_program);
	uint offset_matrix = pio_add_program(pio, &ws2812_program);
	ws2812_program_init(pio, RING_SM, offset_ring, LED_RING, 800000, RGB_ONLY);
	ws2812_program_init(pio, MATRIX_SM, offset_matrix, LED_MATRIX, 800000, RGB_ONLY);

	// ADC and Brightness initialization
	adc_init();
	adc_gpio_init(BRIGHT_POT);  // set up pin for analog input
	adc_select_input(0);		// select which ADC channel to read
	brightInit();				// loads buffer with 1s of brightness pot readings

	sleep_ms(3000);		// gives IDE time to re-establish COM port before initiating output
	ConsoleInit();

	// Packs some Color arrays
	loadSolidColor(Matrix, MatrixColors, solidColor);
	loadColorWheel(Ring, RingColors, RGB);



	while(1) 
	{

		// prints encoder position to serial port only when moved
		static uint32_t lastPrintTime = 0;
		if (enc_count_update) {
			printf("Left: %d \tMiddle: %d\tRight: %d\n", Left.counts, Middle.counts, Right.counts);
			enc_count_update = 0;
		}

		// // Hello World Serial Heartbeat
		// static uint32_t lastPrint = 0;
		// if (time_ms() - lastPrint > PRINT_TIME)	{
		// 	printf("Hello World\n");
		// 	lastPrint = time_ms();
		// }

		ConsoleProcess();
		heartbeat();
    	sleep_ms(2); 

		uint8_t brtness;
		brtness = brightRead(&Matrix);
		brtness = brightRead(&Ring);
		static uint32_t lastPrint = 0;
		if (time_ms() - lastPrint > PRINT_TIME)	{
			printf("%d", brtness);
			printf("\n");
			lastPrint = time_ms();
		}
		showIt(Matrix, MatrixColors);
		showIt(Ring, RingColors);
		//ringSolidColor(mainColor);
		//ringInitRYB();
		

		// static enum colorState whichColor = RED;
		// static uint32_t lastRingTime = 0;
		// if (time_ms() - lastRingTime > 100) {
		// 	switch(whichColor) {
		// 		case RED: {
		// 			if (mainColor.red >= 255) {
		// 				mainColor.red = 0;
		// 				whichColor = GRN;
		// 			}
		// 			else mainColor.red++;
		// 			break;
		// 		}
		// 		case GRN: {
		// 			if (mainColor.grn >= 255) {
		// 				mainColor.grn = 0;
		// 				whichColor = BLU;
		// 			}
		// 			else mainColor.grn++;
		// 			break;
		// 		}
		// 		case BLU: {
		// 			if (mainColor.blu >= 255) {
		// 				mainColor.blu = 0;
		// 				whichColor = RED;
		// 			}
		// 			else mainColor.blu++;
		// 			break;
		// 		}
		// 	}
		// 	ringSolidColor(mainColor);
		// 	lastRingTime = time_ms();
		// }
	}	
	sleep_ms(100);
}
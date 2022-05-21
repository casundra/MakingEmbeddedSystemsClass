// insert copyright and license
// insert brief overview

// standard Rpi Pico SDK libraries (included via Wizio Platform)
#include <stdint.h>
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"

// application-specific libraries
#include "console.h"			// for the Serial I/O console (works over UART and USB)
#include "pinout.h"				// all pin definitions used in various functions are here
#include "utils.h"				// handy time and heartbeat code
#include "encoders.h"			// driver for encoders
#include "ws2812.h"				// driver for WS2812 addressable LED strips


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


// bouncing way more evident now that looking @ counts instead of just dir
// seems to be working but needs some RC love

// brightness is way the fuck up on the Pico test code, no wonder they print out "Smoke Test"
// integrate the parallel WS2812 code and turn the brightness down
// hopefully parallel also means non-blocking?  Uses DMA.

int main() {

	// UART and onboard LED initialization
	stdio_init_all();	// UART and UART to USB setup for both input and output
	heartbeat_init();

	// Encoder initialization
	encoder_init(RIGHTA, RIGHTB);
	encoder_init(MIDDLEA, MIDDLEB);
	encoder_init(LEFTA, LEFTB);
	gpio_set_irq_enabled_with_callback(RIGHTA, GPIO_IRQ_EDGE_RISE, 1, &isr_gpio_callback);

	// PIO pio = pio0;
    // int sm = 0;
    // uint offset = pio_add_program(pio, &ws2812_program);
	//  ws2812_program_init(pio, sm, offset, WS2812_PIN, 800000, IS_RGBW);
	// int t = 0;

	sleep_ms(3000);		// gives IDE time to re-establish COM port before initiating output
	ConsoleInit();
	printf("WS2812 Smoke Test, using pin %d", WS2812_PIN);


	while(1) 
	{

		static uint32_t lastPrintTime = 0;
		if (enc_count_update) {
			printf("Left: %d \tMiddle: %d\tRight: %d\n", Left.counts, Middle.counts, Right.counts);
			lastPrintTime = time_ms();
			enc_count_update = 0;
		}


		// // Hello World Heartbeat
		// static uint32_t lastPrint = 0;
		// if (time_ms() - lastPrint > PRINT_TIME)	{
		// 	printf("Hello World\n");
		// 	lastPrint = time_ms();
		// }

		ConsoleProcess();
		heartbeat();
    	sleep_ms(2); 

		// int pat = rand() % count_of(pattern_table);
        // int dir = (rand() >> 30) & 1 ? 1 : -1;
        // puts(pattern_table[pat].name);
        // puts(dir == 1 ? "(forward)" : "(backward)");
        // for (int i = 0; i < 1000; ++i) {
        //     pattern_table[pat].pat(NUM_PIXELS, t);
        //     sleep_ms(10);
        //     t += dir;
        // }
	}	
}
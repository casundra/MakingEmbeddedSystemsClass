// Copyright 2022 by Carrie Sundra, Alpenglow Industries
// www.alpenglowindustries.com
// @alpenglowind on twitter & instagram
// Alpenglow Industries on GitHub & YouTube
//
// MIT License

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
#include "version.h"			// holds version string

// Encoder Structures and ISR
// To Do: make a structure of structures for encoders?  Or array?  
// 		Make it easier to pass all encoder info to different functions?
Encoder Right = {RIGHTA, RIGHTB, 0, 0, 0, 0};
Encoder Middle = {MIDDLEA, MIDDLEB, 0, 0, 0, 0};
Encoder Left = {LEFTA, LEFTB, 0, 0, 0, 0};
volatile uint8_t enc_count_update = 0;		// encoder count update flag
volatile uint8_t butt_date = 0; 			// button update flag (sorry I am 12)

// Interrupts for all GPIOs
// They have one shared interrupt and you have to figure out who called it (gpio)
// Used for encoders and button
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
		case MODE_BUTT: {
			butt_date = button_read(MODE_BUTT);
			break;
		}
	}
}

// LED Strip Structures, Color Structures, and Globals
Color activeColor = {255, 0, 0};
Color solidColor = {0, 53, 62};
Strip Matrix = {5, MATRIX_PIXELS, LED_MATRIX, MATRIX_SM};
Strip Ring = {5, RING_PIXELS, LED_RING, RING_SM};
Color MatrixColors[MATRIX_PIXELS] = {0};
Color RingColors[RING_PIXELS] = {0};
uint8_t gammaCorr = 1;	// toggles gamma correction for brightness on/off, used in ledpatterns.c

// State Machine
enum deviceState {RGB_PICKER, HUE_PICKER, COMPLEMENTARY, NUM_STATES};

int main() {

	// To Do: move initializations to other libs so that main code is less Pico-specific?
	// 			ex: the single line ConsoleInit();

	// UART and onboard LED initialization
	stdio_init_all();	// UART and UART to USB setup for both input and output
	heartbeat_init();	// onboard LED blinking
	
	// Button initialization
	button_init(MODE_BUTT);

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
	brightInit();				// loads buffer with 1 second of brightness pot readings

	// Serial over USB initialization
	sleep_ms(3000);		// gives IDE time to re-establish COM port before initiating Console
	printf("What rolls downs stairs, alone or in pairs, runs over your over neighbor's dog?\n");
	printf("What's great for a snack and fits on your back, it's ");
	printf(VERSION_STRING);
	printf("!\n");
	ConsoleInit();		// initializes the serial console command interface

	// State Machine initialization
	enum deviceState State = RGB_PICKER;

	// To Do:
	// Should probably break out LED show commands and put in separate loop that can be run at constant rate
	// 	That would allow patterns and possibly brightness dithering in the future
	// Code currently works in RGB primarly and converts to HSL on the fly wheen needed.
	//	Turns out I need HSL way more than I anticipated.  Need to refactor code to generate HSL values
	// 	once upon a color change, and maintain that info persistently, along with the RGB values.
	// I did a lot with structures because I wanted to be able to refer to colors in a human-readable way
	//	as color.red, color.grn, etc.  I don't know how much overhead this adds, could perhaps redo
	//	using a normal array with index #defines as color[RED]?  But then would need 2D array and maybe
	//	would require more nested loops which aren't as easy to understand.
	while(1) 
	{

		// Checks for State change
		if (butt_date) {
			State += 1;
			State %= NUM_STATES;
			butt_date = 0;
			blinkStrips(Matrix, Ring);
		}

		// State Machine for palLED palette functions
		switch (State) {
			case RGB_PICKER: { 
				loadSolidColor(Matrix, MatrixColors, activeColor);
				loadActiveWheel(Ring, RingColors, activeColor, RGB);
				if (enc_count_update) {
					// To Do:
					// break out into separate function & file
					// handle full on/full off wrapping?  It's kind of handy for testing
					enc_count_update = 0; // clear first so I don't miss counts
					activeColor.red += Left.change;
					Left.change = 0;
					activeColor.grn += Middle.change;
					Middle.change = 0;
					activeColor.blu += Right.change;
					Right.change = 0;
					printColor(activeColor);
					loadSolidColor(Matrix, MatrixColors, activeColor);
					loadActiveWheel(Ring, RingColors, activeColor, RGB);
				}
				break;
			}
			case HUE_PICKER: {
				loadSolidColor(Matrix, MatrixColors, activeColor);
				loadActiveWheel(Ring, RingColors, activeColor, RGB);
				if (enc_count_update) {
					// To Do: encoder 
					// break out into separate function & file
					// handle full on/full off wrapping?  It's kind of handy for testing
					enc_count_update = 0; // clear first so I don't miss counts

					// goes to HSL to slide active Color around the wheel based on Left encoder
					HSL hueColor = rgb2hsl(activeColor);
					hueColor.hue += Left.change * 4; // 30 detents on the encoder = 3 encoder rotations per color wheel rotation
					Left.change = 0;
					if (hueColor.hue > 65000) hueColor.hue = 360 - (65535 - hueColor.hue);
					if (hueColor.hue >= 360) hueColor.hue -= 360;

					activeColor = hsl2rgb(hueColor);

					Middle.change = 0;	// ignores middle and right
					Right.change = 0;

					// Sends new color out serial port and updates LEDs
					printColor(activeColor);
					loadSolidColor(Matrix, MatrixColors, activeColor);
					loadActiveWheel(Ring, RingColors, activeColor, RGB);
				}
				break;
			}
			case COMPLEMENTARY: {
				// very rudimentary implementation, just shown as an example
				loadFixedWheel(Ring, RingColors, RYB);
				loadComplement(Matrix, MatrixColors, activeColor);
				Left.change = 0;		// ignores encoders and doesn't retain changed counts
				Middle.change = 0;
				Right.change = 0;
				enc_count_update = 0;
				break;
			}
		}

		// Reads brightness setting from pot and adjusts LED output
		uint8_t brtness;
		brtness = brightRead(&Matrix);
		Ring.brt = brtness;
		showIt(Matrix, MatrixColors);
		showIt(Ring, RingColors);

		// End of Loop Housekeeping
		ConsoleProcess();	// process serial commands
		heartbeat(); 		// onboard LED blinking
		sleep_ms(10); 		// ensures minimum loop time
	}	
}
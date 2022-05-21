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

#define DEBOUNCE_ENC	1	// ms of debounce time

Encoder Right = {RIGHTA, RIGHTB, 0, 0, 0};
Encoder Middle = {MIDDLEA, MIDDLEB, 0, 0, 0};
Encoder Left = {LEFTA, LEFTB, 0, 0, 0};

typedef void (*pattern)(uint len, uint t);
const struct {
    pattern pat;
    const char *name;
} pattern_table[] = {
        {pattern_snakes,  "Snakes!"},
        {pattern_random,  "Random data"},
        {pattern_sparkle, "Sparkles"},
        {pattern_greys,   "Greys"},
};

// // this is not going to work if 2 knobs are moved simultaneously
// int64_t encoder_debounce_callback(alarm_id_t id, void *encoder) {
// 	encoder_read(encoder);

// 	return 0;
// }

void isr_gpio_callback(uint gpio, uint32_t events) {
	switch (gpio) {
		case RIGHTA: {
			encoder_readA(&Right);
			break;
		}
		case RIGHTB: {
			encoder_readB(&Right);
			break;
		}
		case MIDDLEA: {
			encoder_readA(&Middle);
			break;
		}
		case MIDDLEB: {
			encoder_readB(&Middle);
			break;
		}
		case LEFTA: {
			encoder_readA(&Left);
			break;
		}
		case LEFTB: {
			encoder_readB(&Left);
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
	stdio_init_all();	// UART and UART to USB setup for both input and output
	heartbeat_init();

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
		// if ( (Left.dir) == CW) gpio_put(PICO_DEFAULT_LED_PIN, 1);
		// else gpio_put(PICO_DEFAULT_LED_PIN, 0);

		static uint32_t lastPrintTime = 0;
		if (time_ms() - lastPrintTime > PRINT_TIME) {
			int16_t rt = Right.counts;
			int16_t md = Middle.counts;
			int16_t lf = Left.counts;
			printf("Left: %d \tMiddle: %d\tRight: %d\n", lf, md, rt);
			lastPrintTime = time_ms();
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
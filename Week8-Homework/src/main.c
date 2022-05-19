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

//#include <cmsis_armclang.h>

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

uint8_t initglobalVariable = 1;
uint32_t uninitglobalVariable;

// // this is not going to work if 2 knobs are moved simultaneously
// int64_t encoder_debounce_callback(alarm_id_t id, void *encoder) {
// 	encoder_read(encoder);

// 	return 0;
// }

void isr_gpio_callback(uint gpio, uint32_t events) {
	switch (gpio) {
		case RIGHTA: {
			encoder_read(&Right);
			break;
		}
		case RIGHTB: {
			encoder_inc(&Right);
			break;
		}
		case MIDDLEA: {
			encoder_read(&Middle);
			break;
		}
		case MIDDLEB: {
			encoder_inc(&Middle);
			break;
		}
		case LEFTA: {
			encoder_read(&Left);
			break;
		}
		case LEFTB: {
			encoder_inc(&Left);
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

	PIO pio = pio0;
    int sm = 0;
    uint offset = pio_add_program(pio, &ws2812_program);
	 ws2812_program_init(pio, sm, offset, WS2812_PIN, 800000, IS_RGBW);
	int t = 0;

	sleep_ms(3000);		// gives IDE time to re-establish COM port before initiating output
	ConsoleInit();
	printf("WS2812 Smoke Test, using pin %d", WS2812_PIN);

	// found these in cmsis_armclang.h on Rpi Pico github but couldn't include it, would have to check local path and presence.
	// uint32_t stackPointer = __TZ_get_SP_NS;
	// uint32_t mainStackPointer = __get_MSP;
	// uint32_t processStackPointer = __get_PSP;

	// many thanks to Daniel who helped with heap and stack pointers


	uint8_t initSetupVariable = 1;
	uint32_t uninitSetupVariable;


	while(1) 
	{
		// if ( (Left.dir) == CW) gpio_put(PICO_DEFAULT_LED_PIN, 1);
		// else gpio_put(PICO_DEFAULT_LED_PIN, 0);

		static uint32_t lastPrintTime = 0;
		if (time_ms() - lastPrintTime > PRINT_TIME) {
			int16_t rt = Right.counts;
			int16_t md = Middle.counts;
			int16_t lf = Left.counts;
		//	printf("Right: %d\tMiddle: %d\tLeft: %d\n", rt, md, lf);
			uint32_t stackPointer;
			__asm volatile ("mov %0, r13" : "=r" (stackPointer) );  // thank you for your help, Daniel!
			uint32_t *heapPointer = malloc(1);
			printf("Stack Pointer:\t%x\n", (uint) stackPointer);
			printf("Heap Pointer:\t%x\n", (uint) heapPointer);
			printf("Initialized Global Variable:\t%x\n", (uint) &initglobalVariable);
			printf("Uninitialized Global Variable:\t%x\n", (uint) &uninitglobalVariable);
			printf("Initialized Setup Variable:\t%x\n", (uint) &initSetupVariable);
			printf("Uninitialized Setup Variable:\t%x\n", (uint) &uninitSetupVariable);
			printf("Static While(1) Variable:\t%x\n", (uint) &lastPrintTime);
			printf("Normal While(1) Variable:\t%x\n", (uint) &rt);
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

	// 	int pat = rand() % count_of(pattern_table);
    //     int dir = (rand() >> 30) & 1 ? 1 : -1;
    //     puts(pattern_table[pat].name);
    //     puts(dir == 1 ? "(forward)" : "(backward)");
    //     for (int i = 0; i < 1000; ++i) {
    //         pattern_table[pat].pat(NUM_PIXELS, t);
    //         sleep_ms(10);
    //         t += dir;
    //     }
	}	
}
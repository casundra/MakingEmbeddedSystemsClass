
#include <stdint.h>
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "console.h"
#include "pinout.h"				// all pin definitions used in various functions are here
#include "utils.h"				// handy time and heartbeat code
#include "encoders.h"

#define DEBOUNCE_ENC	1	// ms of debounce time

Encoder Right = {RIGHTA, RIGHTB, 0, 0, 0};
Encoder Middle = {MIDDLEA, MIDDLEB, 0, 0, 0};
Encoder Left = {LEFTA, LEFTB, 0, 0, 0};

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

int main() {
	stdio_init_all();	// UART and UART to USB setup for both input and output
	heartbeat_init();
	encoder_init(RIGHTA, RIGHTB);
	encoder_init(MIDDLEA, MIDDLEB);
	encoder_init(LEFTA, LEFTB);
	gpio_set_irq_enabled_with_callback(RIGHTA, GPIO_IRQ_EDGE_RISE, 1, &isr_gpio_callback);
	sleep_ms(3000);		// gives IDE time to re-establish COM port before initiating output
	ConsoleInit();

	while(1) 
	{
		if ( (Left.dir) == CW) gpio_put(PICO_DEFAULT_LED_PIN, 1);
		else gpio_put(PICO_DEFAULT_LED_PIN, 0);

		static uint32_t lastPrintTime = 0;
		if (time_ms() - lastPrintTime > PRINT_TIME) {
			int16_t rt = Right.counts;
			int16_t md = Middle.counts;
			int16_t lf = Left.counts;
			printf("Right: %d\tMiddle: %d\tLeft: %d\n", rt, md, lf);
			lastPrintTime = time_ms();
		}


		// // Hello World Heartbeat
		// static uint32_t lastPrint = 0;
		// if (time_ms() - lastPrint > PRINT_TIME)	{
		// 	printf("Hello World\n");
		// 	lastPrint = time_ms();
		// }

		ConsoleProcess();
	//	heartbeat();
    	sleep_ms(2); 
	}	
}

#include <stdint.h>
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "console.h"
#include "pinout.h"				// all pin definitions used in various functions are here
#include "utils.h"				// handy time and heartbeat code
#include "encoders.h"

volatile uint8_t dir = CW;

void isr_gpio_callback(uint gpio, uint32_t events) {
	uint8_t righta = gpio_get(RIGHTA);
	uint8_t rightb = gpio_get(RIGHTB);
	if (righta) {
		if (rightb) {
			dir = CCW;
			gpio_put(PICO_DEFAULT_LED_PIN, 0);
		}
		else {
			dir = CW;
			gpio_put(PICO_DEFAULT_LED_PIN, 1);
		}
	}
}

int main() {
	stdio_init_all();	// UART and UART to USB setup for both input and output
	heartbeat_init();
	encoder_init(RIGHTA, RIGHTB);
	gpio_set_irq_enabled_with_callback(RIGHTA, GPIO_IRQ_EDGE_RISE, 1, &isr_gpio_callback);
	sleep_ms(3000);		// gives IDE time to re-establish COM port before initiating output
	ConsoleInit();





	while(1) 
	{


		// // Hello World Heartbeat
		// static absolute_time_t lastPrint = 0;
		// if (get_absolute_time() - lastPrint > PRINT_TIME)	{
		// 	printf("Hello World\n");
		// 	lastPrint = get_absolute_time();
		// }

		ConsoleProcess();
	//	heartbeat();
    	sleep_ms(2); 
	}	
}
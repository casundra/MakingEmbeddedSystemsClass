
#include <stdint.h>
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "console.h"
#include "pinout.h"				// all pin definitions used in various functions are here
#include "utils.h"				// handy time and heartbeat code
#include "encoders.h"

volatile uint8_t rtDir = 2;
volatile uint8_t mdDir = 2;
volatile uint8_t lfDir = 2;
volatile int16_t rtCounts = 0;
volatile int16_t mdCounts = 0;
volatile int16_t lfCounts = 0;
volatile uint8_t rtdebounce = 0;
volatile uint8_t mddebounce = 0;
volatile uint8_t lfdebounce = 0;

typedef struct EncoderStruct {
	const uint8_t phPinA;
	const uint8_t phPinB;
	volatile int16_t counts;
	volatile uint8_t dir;
} Encoder;

Encoder Right = {RIGHTA, RIGHTB, 0, 2};
Encoder Middle = {MIDDLEA, MIDDLEB, 0, 2};
Encoder Left = {LEFTA, LEFTB, 0, 2};

// need to add tracking for which phase called, so that can send the correct info and 
// clear the correct debounce flag.
int64_t encoder_debounce_callback(alarm_id_t id, Encoder encoder) {
	encoder_read(encoder.phPinA, encoder.phPinB, encoder.counts, encoder.dir);
	
}

void isr_gpio_callback(uint gpio, uint32_t events) {
	uint8_t phasea;
	uint8_t phaseb;
	switch (gpio) {
		case RIGHTA: {
			if (!rtdebounce) add_alarm_in_ms(30, encoder_debounce_callback, &Right, 0);
			rtdebounce = 1;
			//encoder_read(RIGHTA, RIGHTB, &rtCounts, &rtDir);
			break;
		}
		case MIDDLEA: {
			if (!mddebounce) add_alarm_in_ms(30, encoder_debounce_callback, &Middle, 0);
			mddebounce = 1;
			//encoder_read(MIDDLEA, MIDDLEB, &mdCounts, &mdDir);
			break;
		}
		case LEFTA: {
			if (!lfdebounce) add_alarm_in_ms(30, encoder_debounce_callback, &Left, 0);
			lfdebounce = 1;
			//encoder_read(LEFTA, LEFTB, &lfCounts, &lfDir);
			break;
		}
	}
}

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
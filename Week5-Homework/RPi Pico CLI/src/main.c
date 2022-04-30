/*************************************************
** Command Line Interface
** This is from https://github.com/eleciawhite/reusable
** (MIT license)
**
** To use it in the simulator, press run 
**    It should print `Welcome to the Consolinator, your gateway to testing code and hardware`
** Type 'help' in the white box at the bottom and hit return.
** It lists the commands it supports.
**
** There are several files here:
** Console.c is a command parser. 
**    Call the init function during init and
**    then call the process function on every pass through a loop.
** You probably don't need to modify this file much.
**
** The interface is in consoleIo.c which currently
** uses the RPi Pico interface. You will need to modify this
** for your own hardware, connecting it to a UART in your embedded system.
**
** The command table and commands are implemented in consoleCommands.c.
** This is where you add commands, probably by copying one that is 
** already there. You need to modify mConsoleCommandTable 
** to add the command.
*************************************************/
#include <stdio.h>
#include "pico/stdlib.h"
#include "console.h"

#define LED_PIN	25
#define BLINK_TIME	500000	// microseconds

int main() {
  stdio_init_all(); // UART setup for both input and output
  gpio_init(LED_PIN);
  gpio_set_dir(LED_PIN, GPIO_OUT);
  sleep_ms(500);
  ConsoleInit();

  absolute_time_t lastBlink = 0;
  absolute_time_t lastWrite = 0;

	while(1) 
	{
		// does not work
		ConsoleProcess();

		// // does not work
		// while (uart_is_readable(uart0)) 
		// {
		// 	uint8_t ch = uart_getc(uart0);
		// 	uart_putc(uart0, ch); // echo
		// }

		// // this works, sort of.  Echoes but LED doesn't blink
		// char ch = 0;
		// ch = getchar();
		// putchar(ch);

		if ( get_absolute_time() - lastBlink > BLINK_TIME ) {
			gpio_xor_mask(1 << LED_PIN);
			lastBlink = get_absolute_time();
		}

		// if ( get_absolute_time() - lastWrite > BLINK_TIME*10 ) {
		// 	lastWrite = get_absolute_time();
		// 	ConsoleSendString("blink\n");

		// }

    	sleep_ms(2); 
	}	
}
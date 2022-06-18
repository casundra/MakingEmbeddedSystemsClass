// Modified by Carrie Sundra 2022
// MIT License
// Based on:

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

// Console IO is a wrapper between the actual in and output and the console code
// In an embedded system, this might interface to a UART driver.

#include "consoleIo.h"
#include <stdio.h>

eConsoleError ConsoleIoInit(void)
{
	return CONSOLE_SUCCESS;
}

// Modified to run on USB UART interface on RPi Pico.
// Elecia's original code was specific to hardware UART pins.
eConsoleError ConsoleIoReceive(uint8_t *buffer, const uint32_t bufferLength, uint32_t *readLength)
{
	// Elecia's original code:
	// This is modified for the Wokwi RPi Pico simulator. It works fine 
	// but that's partially because the serial terminal sends all of the 
	// characters at a time without losing any of them. What if this function
	// wasn't called fast enough?
	// uint32_t i = 0;
	// char ch;

	// while (uart_is_readable(uart0)) 
	// {
  	// 	ch = uart_getc(uart0);
  	// 	uart_putc(uart0, ch); // echo
	// 	buffer[i] = (uint8_t) ch;
	// 	i++;
	// }

	// *readLength = i;
	// return CONSOLE_SUCCESS;

	uint32_t i = 0;
	int ch = getchar_timeout_us(0);

	while ((ch != PICO_ERROR_TIMEOUT) && (ch != EOF) && (i < bufferLength)) 
	{
  		putchar(ch); // echo
		buffer[i] = (uint8_t) ch;
		i++;
		ch = getchar_timeout_us(0);
	}

	*readLength = i;
	return CONSOLE_SUCCESS;
}

eConsoleError ConsoleIoSendString(const char *buffer)
{
	printf("%s", buffer);
	return CONSOLE_SUCCESS;
}


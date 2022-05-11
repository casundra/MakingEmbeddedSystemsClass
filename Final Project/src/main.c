
#include <stdio.h>
#include "pico/stdlib.h"
#include "console.h"
#include "pinout.h"				// all pin definitions used in various functions are here
#include "utils.h"				// handy time and heartbeat code



int main() {
	stdio_init_all();	// UART and UART to USB setup for both input and output
	heartbeat_init();
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
		heartbeat();
    	sleep_ms(2); 
	}	
}
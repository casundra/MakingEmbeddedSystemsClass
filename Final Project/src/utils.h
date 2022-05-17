/* Utilities for the general happy running of code  */

#ifndef UTILS_H
#define UTILS_H

#include <stdint.h>

#define BLINK_TIME	1000	// milliseconds
#define PRINT_TIME	1000

uint32_t time_ms();
void heartbeat_init();
void heartbeat();


#endif
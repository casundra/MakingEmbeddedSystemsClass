/* Utilities for the general happy running of code and testing */

#ifndef UTILS_H
#define UTILS_H

#include <stdint.h>

// times are in milliseconds
// for periodic blinking and serial printing
#define BLINK_TIME	1000	
#define PRINT_TIME	250

uint32_t time_ms();
void heartbeat_init();
void heartbeat();
void serialHeartbeat();


#endif
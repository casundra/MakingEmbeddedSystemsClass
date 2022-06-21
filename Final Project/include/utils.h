// Copyright 2022 by Carrie Sundra, Alpenglow Industries
// www.alpenglowindustries.com
// @alpenglowind on twitter & instagram
// Alpenglow Industries on GitHub & YouTube
//
// MIT License


/* Utilities for the general happy running of code and testing */

#ifndef UTILS_H
#define UTILS_H

#include <stdint.h>

// times are in milliseconds
// for periodic blinking and serial printing
#define BLINK_TIME	1000	
#define PRINT_TIME	250

uint32_t time_ms();         // returns the current time since boot in milliseconds
void heartbeat_init();      // sets up onboard LED pin
void heartbeat();           // blinks the onboard LED
void serialHeartbeat();     // prints "Hello World" out the serial port at a certain rate


#endif
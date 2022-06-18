#ifndef BRIGHTNESS_H
#define BRIGHTNESS_H

#include "pico/stdlib.h"
#include "ledpatterns.h"

// Handles reading the ADC and calculating a brightness value

uint8_t brightInit();
uint8_t brightRead(Strip *strip);

#endif
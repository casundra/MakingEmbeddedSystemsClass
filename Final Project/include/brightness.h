#ifndef BRIGHTNESS_H
#define BRIGHTNESS_H

#include "pico/stdlib.h"
#include "ledpatterns.h"

uint8_t brightInit(Color *color);
uint8_t brightRead(Color *color);

#endif
// Copyright 2022 by Carrie Sundra, Alpenglow Industries
// www.alpenglowindustries.com
// @alpenglowind on twitter & instagram
// Alpenglow Industries on GitHub & YouTube
//
// MIT License

#ifndef BRIGHTNESS_H
#define BRIGHTNESS_H

#include "pico/stdlib.h"
#include "ledpatterns.h"

// Handles reading the ADC and calculating a brightness value

uint8_t brightInit();                   // initial brightness readings, populates circular buffer
uint8_t brightRead(Strip *strip);       // reads brightness, calculates new average
void brightPrint(uint8_t brightness);   // test function for printing brightness to the serial port

#endif
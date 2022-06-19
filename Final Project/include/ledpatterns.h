#ifndef LEDPATTERNS_H
#define LEDPATTERNS_H

#include "pico/stdlib.h"
#include "ws2812.h"
#include "palled.h"

#define RYB 0
#define RGB 1

// Takes in an array of Colors and returns the array with brightness-adjusted values
Color adjustBrightness(Color *color, uint8_t brtness);

// outputs colors according to the values in the stripColors buffer, adjusts brightness first
void showIt(Strip strip, Color stripColors[]);                          

// prints RGB values to serial port, useful for testing encoders and adjustments
void printColor(Color color);

// loads colors into the stripColor buffer and shows them
void loadSolidColor(Strip strip, Color stripColors[], Color color);     // one solid color for entire strip
void loadComplement(Strip strip, Color stripColors[], Color color);     // half active color, half complement
void loadColorWheel (Strip strip, Color stripColors[], uint8_t type);   // wheel only, fixed 16 LEDs

#endif
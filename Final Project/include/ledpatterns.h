#ifndef LEDPATTERNS_H
#define LEDPATTERNS_H

#include "pico/stdlib.h"
#include "ws2812.h"

#define RYB 0
#define RGB 1

typedef struct colorStruct {
    uint8_t red;
    uint8_t grn;
    uint8_t blu;
} Color;

// outputs colors according to the values in the stripColors buffer, adjusts brightness first
void showIt(Strip strip, Color stripColors[]);                          

// prints RGB values to serial port, useful for testing encoders and adjustments
void printColor(Color color);

// loads colors into the stripColor buffer and shows them
void loadSolidColor(Strip strip, Color stripColors[], Color color);     // any strip of any length
void loadColorWheel (Strip strip, Color stripColors[], uint8_t type);   // wheel only, fixed 16 LEDs

#endif
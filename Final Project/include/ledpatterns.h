#ifndef LEDPATTERNS_H
#define LEDPATTERNS_H

#include "pico/stdlib.h"
#include "ws2812.h"

typedef struct colorStruct {
    uint8_t red;
    uint8_t grn;
    uint8_t blu;
} Color;

// display patterns
void showIt(Strip strip, Color stripColors[]);
//void ringSolidColor(Color color);   // single color
void matrixSolidColor(Color color, Strip strip, Color stripColors[]); // single color
//void matrixMono(Color color);   // single color with different brightnesses, doesn't work very well
void ringInitRYB ();    // RYB color wheel
void ringInitRGB ();    // RGB color wheel


#endif
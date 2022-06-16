#ifndef LEDPATTERNS_H
#define LEDPATTERNS_H

#include "pico/stdlib.h"
#include "ws2812.h"

// Gamma is a lookup table for brightness that corrects for our eyeballs' non-linear perception of brightness
// currently not used
// another great article on gamma correction: https://hackaday.com/2016/08/23/rgb-leds-how-to-master-gamma-and-hue-for-perfect-brightness/



typedef struct colorStruct {
    uint8_t red;
    uint8_t grn;
    uint8_t blu;
    uint8_t brt;
} Color;


void solidRingColor(Color color);
void solidMatrixColor(Color color);
void matrixMono(Color color);
void ringInitRYB ();
void ringInitRGB ();


#endif
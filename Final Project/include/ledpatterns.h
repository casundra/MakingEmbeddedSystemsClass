#ifndef LEDPATTERNS_H
#define LEDPATTERNS_H

#include "pico/stdlib.h"
#include "ws2812.h"

typedef struct colorStruct {
    uint8_t red;
    uint8_t grn;
    uint8_t blu;
    uint8_t brt;
} Color;

void solidRingColor(Color color);
void solidMatrixColor(Color color);
void matrixMono(Color color);
void ringInitRGB ();


#endif
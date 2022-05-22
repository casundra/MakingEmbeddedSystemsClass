// Created from Raspberry Pi Pico example:
// https://github.com/raspberrypi/pico-examples/tree/master/pio/ws2812
/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
// Modified by Carrie Sundra 2022


#ifndef WS2812_H
#define WS2812_H

#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "ws2812.pio.h"

#define IS_RGBW     0
#define RING_PIXELS  16
#define WS2812_PIN LED_RING

typedef struct colorStruct {
    uint8_t red;
    uint8_t grn;
    uint8_t blu;
    uint8_t brt;
} Color;

static inline void put_pixel(uint32_t pixel_grb);
static inline uint32_t urgb_u32(uint8_t r, uint8_t g, uint8_t b);
void solidRingColor(Color *color, uint8_t numLEDs);

// void pattern_snakes(uint len, uint t);
// void pattern_random(uint len, uint t);
// void pattern_sparkle(uint len, uint t);
// void pattern_greys(uint len, uint t);




#endif

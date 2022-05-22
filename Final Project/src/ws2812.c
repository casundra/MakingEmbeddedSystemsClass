
// Created from Raspberry Pi Pico example:
// https://github.com/raspberrypi/pico-examples/tree/master/pio/ws2812
/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
// Modified by Carrie Sundra 2022

#include <stdio.h>
#include <stdlib.h>
#include "ws2812.h"


static inline void put_pixel(uint32_t pixel_grb) {
    pio_sm_put_blocking(pio0, 0, pixel_grb << 8u);
}

static inline uint32_t urgb_u32(uint8_t r, uint8_t g, uint8_t b) {
    return
            ((uint32_t) (r) << 8) |
            ((uint32_t) (g) << 16) |
            (uint32_t) (b);
}

void solidRingColor(Color *color, uint8_t numLEDs) {
    uint32_t red = (color->red * color->brt) >> 8;
    uint32_t grn = (color->grn * color->brt) >> 8;
    uint32_t blu = (color->blu * color->brt) >> 8;
    for (uint8_t i = 0; i < numLEDs; i++) {
        put_pixel(urgb_u32((uint8_t) red, (uint8_t) grn, (uint8_t) blu));
    }
}


// void pattern_snakes(uint len, uint t) {
//     for (uint i = 0; i < len; ++i) {
//         uint x = (i + (t >> 1)) % 64;
//         if (x < 10)
//             put_pixel(urgb_u32(0xff, 0, 0));
//         else if (x >= 15 && x < 25)
//             put_pixel(urgb_u32(0, 0xff, 0));
//         else if (x >= 30 && x < 40)
//             put_pixel(urgb_u32(0, 0, 0xff));
//         else
//             put_pixel(0);
//     }
// }

// void pattern_random(uint len, uint t) {
//     if (t % 8)
//         return;
//     for (int i = 0; i < len; ++i)
//         put_pixel(rand());
// }

// void pattern_sparkle(uint len, uint t) {
//     if (t % 8)
//         return;
//     for (int i = 0; i < len; ++i)
//         put_pixel(rand() % 16 ? 0 : 0xffffffff);
// }

// void pattern_greys(uint len, uint t) {
//     int max = 100; // let's not draw too much current!
//     t %= max;
//     for (int i = 0; i < len; ++i) {
//         put_pixel(t * 0x10101);
//         if (++t >= max) t = 0;
//     }
// }




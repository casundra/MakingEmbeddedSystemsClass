
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


static inline void put_pixel_ring(uint32_t pixel_grb) {
    pio_sm_put_blocking(pio0, RING_SM, pixel_grb << 8u);
}

static inline void put_pixel_matrix(uint32_t pixel_grb) {
    pio_sm_put_blocking(pio0, MATRIX_SM, pixel_grb << 8u);
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
        put_pixel_ring(urgb_u32((uint8_t) red, (uint8_t) grn, (uint8_t) blu));
    }
}

void solidMatrixColor(Color *color, uint8_t numLEDs) {
    uint32_t red = (color->red * color->brt) >> 8;
    uint32_t grn = (color->grn * color->brt) >> 8;
    uint32_t blu = (color->blu * color->brt) >> 8;
    for (uint8_t i = 0; i < numLEDs; i++) {
        put_pixel_matrix(urgb_u32((uint8_t) red, (uint8_t) grn, (uint8_t) blu));
    }
}

void matrixMono(Color *color, uint8_t *size) {
    uint32_t red = (color->red * color->brt) >> 8;
    uint32_t grn = (color->grn * color->brt) >> 8;
    uint32_t blu = (color->blu * color->brt) >> 8;
    uint8_t rows = size[0];
    uint8_t cols = size[1];
    uint8_t firstMonoPixel = (rows >> 1)*cols;
    uint8_t monoCols = cols >> 2;
    uint8_t monoRows = rows = (rows >> 1);
    for (uint8_t i = 0; i < firstMonoPixel; i++) {
        put_pixel_matrix(urgb_u32((uint8_t) red, (uint8_t) grn, (uint8_t) blu));
    }
    for (uint8_t i = 0; i < monoRows; i++) {
        for (uint8_t j = 0; j < 4; j++) {
            for (uint8_t k = 0; k < monoCols; k++ ) {
                uint8_t brtInit = color->brt *3;
                uint8_t brtFactor = j*(color->brt);
                red = (color->red * (brtInit - brtFactor)) >> 8;
                grn = (color->grn * (brtInit - brtFactor)) >> 8;
                blu = (color->blu * (brtInit - brtFactor)) >> 8;
                put_pixel_matrix(urgb_u32((uint8_t) red, (uint8_t) grn, (uint8_t) blu)); 
            }

        }
    }
}




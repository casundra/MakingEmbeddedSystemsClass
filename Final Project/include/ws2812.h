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

#define RGB_ONLY    0
#define RGB_WHITE   1
#define RING_SM         0
#define RING_PIXELS     16
#define MATRIX_SM       1
#define MATRIX_ROWS     8
#define MATRIX_COLS     8

typedef struct colorStruct {
    uint8_t red;
    uint8_t grn;
    uint8_t blu;
    uint8_t brt;
} Color;

static inline void put_pixel_ring(uint32_t pixel_grb);
static inline void put_pixel_matrix(uint32_t pixel_grb);
static inline uint32_t urgb_u32(uint8_t r, uint8_t g, uint8_t b);
void solidRingColor(Color *color, uint8_t numLEDs);
void solidMatrixColor(Color *color, uint8_t numLEDs);
void matrixMono(Color *color, uint8_t *size);


#endif

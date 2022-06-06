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
#include "pinout.h"

// Strip Types
#define RGB_ONLY    0
#define RGB_WHITE   1

// State Machine instances for Ring and Matrix
#define RING         0
#define MATRIX       1

static inline void put_pixel(uint32_t pixel_grb, uint8_t strip) {
    pio_sm_put_blocking(pio0, strip, pixel_grb << 8u);
}

static inline uint32_t urgb_u32(uint8_t r, uint8_t g, uint8_t b) {
    return
            ((uint32_t) (r) << 8) |
            ((uint32_t) (g) << 16) |
            (uint32_t) (b);
}

#endif

/* palLED setup specific to RPi Pico board */

#ifndef PALLED_H
#define PALLED_H

#include "pico/stdlib.h"

// RPi Pico GPIO Assignments
// These do not correlate 1:1 to pin numbers, see datasheet
// 0 temporarily reserved for UART TX
// 1 temporarily reserved for UART RX
#define LED_RING    2   // WS2812B addressable LED 16 pixel ring
#define LED_MATRIX  3   // WS2812B addressable LED 8x8 matrix
// Reserved for future LCD integration
// #define LCD_SDA     4   // TFT LCD, I2C but could potentially set up for SPI
// #define LCD_SCK     5
// #define LCD_A0      6
// #define LCD_CS      7
// #define LCD_RES     8
// #define LCD_BL      9   // TFT LCD backlight
#define LEFTA       10  // Left rotary encoder, quadrature
#define LEFTB       11
#define MIDDLEA     12  // Middle rotary encoder, quadrature
#define MIDDLEB     13
#define RIGHTA      14  // Right rotary encoder, quadrature
#define RIGHTB      15
#define MODE_BUTT   16  // Mode button, momentary
#define COLOR_BUTT  17  // Color button, momentary
#define LED_AUX     18  // WS2812B addressable LED strip, user-definable
#define BRIGHT_POT  26  // rotary potentiometer, ADC 0-3 only GPIO 26-29

#define LED_PIN     PICO_DEFAULT_LED_PIN // 25


// Addressable LED Ring and Matrix Properties
#define RING_PIXELS     16
#define MATRIX_ROWS     8
#define MATRIX_COLS     8
#define MATRIX_PIXELS   (MATRIX_ROWS * MATRIX_COLS)

typedef struct stripStruct {
    uint8_t brt;
    uint8_t len;
    uint8_t pin;
    uint8_t sm;
} Strip;

#endif
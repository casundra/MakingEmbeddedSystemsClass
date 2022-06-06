/* Pinout specific to palLED Pico board */

#include "pico/stdlib.h"

// RPi Pico Pinout
// 0 temporarily reserved for UART TX
// 1 temporarily reserved for UART RX
#define LED_RING    2   // WS2812B addressable LED 16 pixel ring
#define LED_MATRIX  3   // WS2812B addressable LED 8x8 matrix
#define LCD_SDA     4   // TFT LCD, I2C but could potentially set up for SPI
#define LCD_SCK     5
#define LCD_A0      6
#define LCD_CS      7
#define LCD_RES     8
#define LCD_BL      9   // TFT LCD backlight
#define LEFTA       10  // Left rotary encoder, quadrature
#define LEFTB       11
#define MIDDLEA     12  // Middle rotary encoder, quadrature
#define MIDDLEB     13
#define RIGHTA      14  // Right rotary encoder, quadrature
#define RIGHTB      15
#define MODE_BUTT   16  // Mode button, momentary
#define COLOR_BUTT  17  // Color button, momentary
#define BRIGHT_POT  18  // rotary potentiometer
#define LED_AUX     19  // WS2812B addressable LED strip, user-definable

#define LED_PIN     PICO_DEFAULT_LED_PIN // 25


// Addressable LED Ring and Matrix Properties
#define RING_PIXELS     16
#define MATRIX_ROWS     8
#define MATRIX_COLS     8
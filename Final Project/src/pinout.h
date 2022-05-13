/* Pinout specific to palLED Pico board */

#include "pico/stdlib.h"

#define LED_MATRIX  0   // WS2812B addressable LED 8x8 matrix
#define LED_RING    1   // WS2812B addressable LED 16 pixel ring
#define LED_AUX     2   // WS2812B addressable LED strip, user-definable
#define BRIGHT_POT  3   // rotary potentiometer
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

#define LED_PIN     PICO_DEFAULT_LED_PIN // 25

#include <stdio.h>
#include <stdlib.h>
#include "ledpatterns.h"

// The pattern functions create a local copy of the Color structure so that RGB values can be modified for
// correct brightness display. 

// Modifies the local copy of Color for proper brightness display
static void adjustBrightness(Color *brtadj) {
    // colors are multiplied by brightness %
    // brightness = 0-255, ">> 8" divides by 256
    uint32_t red = (brtadj->red * brtadj->brt) >> 8;
    uint32_t grn = (brtadj->grn * brtadj->brt) >> 8;
    uint32_t blu = (brtadj->blu * brtadj->brt) >> 8;
    brtadj->red = (uint8_t) red;
    brtadj->grn = (uint8_t) grn;
    brtadj->blu = (uint8_t) blu;
}

void solidRingColor(Color color) {
    adjustBrightness(&color);
    uint8_t numLEDs = RING_PIXELS;
    for (uint8_t i = 0; i < numLEDs; i++) {
        put_pixel(urgb_u32((uint8_t) color.red, (uint8_t) color.grn, (uint8_t) color.blu), RING);
    }
}

void solidMatrixColor(Color color) {
    adjustBrightness(&color);
    uint8_t numLEDs = MATRIX_ROWS * MATRIX_COLS;
    for (uint8_t i = 0; i < numLEDs; i++) {
        put_pixel(urgb_u32((uint8_t) color.red, (uint8_t) color.grn, (uint8_t) color.blu), MATRIX);
    }
}

void matrixMono(Color color) {
    adjustBrightness(&color);
    uint8_t rows = MATRIX_ROWS;
    uint8_t cols = MATRIX_COLS;
    uint8_t firstMonoPixel = (rows >> 1)*cols;
    uint8_t monoCols = cols >> 2;
    uint8_t monoRows = rows = (rows >> 1);
    for (uint8_t i = 0; i < firstMonoPixel; i++) {
         put_pixel(urgb_u32((uint8_t) color.red, (uint8_t) color.grn, (uint8_t) color.blu), MATRIX);
    }
    for (uint8_t i = 0; i < monoRows; i++) {
        for (uint8_t j = 0; j < 4; j++) {
            for (uint8_t k = 0; k < monoCols; k++ ) {
                uint8_t brtInit = color.brt *3;
                uint8_t brtFactor = j*(color.brt);
                uint32_t red = (color.red * (brtInit - brtFactor)) >> 8;
                uint32_t grn = (color.grn * (brtInit - brtFactor)) >> 8;
                uint32_t blu = (color.blu * (brtInit - brtFactor)) >> 8;
                 put_pixel(urgb_u32((uint8_t) red, (uint8_t) grn, (uint8_t) blu), MATRIX); 
            }

        }
    }
}

void ringInitRGB () {


}
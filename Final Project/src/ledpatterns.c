
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
    Color initColor = color;
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
                uint32_t red = initColor.red * (brtInit - brtFactor) >> 8;
                uint32_t grn = initColor.grn * (brtInit - brtFactor) >> 8;
                uint32_t blu = initColor.blu * (brtInit - brtFactor) >> 8;
                put_pixel(urgb_u32((uint8_t) red, (uint8_t) grn, (uint8_t) blu), MATRIX); 
            }

        }
    }
}
#define STEPS   (256 / RING_PIXELS)
#define TRIAD1  (RING_PIXELS / 3)
#define TRIAD2  (RING_PIXELS - TRIAD1)

void ringInitRYB () {
    
    // a decent RYB color wheel
    put_pixel(urgb_u32(10, 0, 0), RING);  // 0, RED
    put_pixel(urgb_u32(10, 0, 1), RING);  // 1
    put_pixel(urgb_u32(5, 0, 5), RING);   // 2, PURPLE
    put_pixel(urgb_u32(3, 0, 7), RING);   // 3
    put_pixel(urgb_u32(1, 0, 10), RING);  // 4
    put_pixel(urgb_u32(0, 0, 12), RING);  // 5, BLUE
    put_pixel(urgb_u32(0, 2, 8), RING);   // 6
    put_pixel(urgb_u32(0, 7, 3), RING);   // 7
    put_pixel(urgb_u32(0, 10, 0), RING);  // 8, GREEN
    put_pixel(urgb_u32(1, 10, 0), RING);  // 9
    put_pixel(urgb_u32(3, 7, 0), RING);   // A
    put_pixel(urgb_u32(5, 5, 0), RING);   // B, YELLOW
    put_pixel(urgb_u32(5, 4, 0), RING);   // C
    put_pixel(urgb_u32(8, 4, 0), RING);   // D, ORANGE
    put_pixel(urgb_u32(9, 2, 0), RING);   // E
    put_pixel(urgb_u32(10, 1, 0), RING);  // F

    // for (uint8_t i = 0; i < RING_PIXELS; i++) {
    //     if (i == 0) put_pixel(urgb_u32(10, 0, 0), RING);
    //     else if (i == TRIAD1) put_pixel(urgb_u32(0, 0, 10), RING);
    //     else if (i == TRIAD2) put_pixel(urgb_u32(10, 10, 0), RING);
    //     else put_pixel(urgb_u32(0, 0, 0), RING);
    // }

}

void ringInitRGB () {
    
    // a decent RGB color wheel
    put_pixel(urgb_u32(10, 0, 0), RING);  // 0, RED
    put_pixel(urgb_u32(10, 0, 1), RING);  // 1
    put_pixel(urgb_u32(5, 0, 5), RING);   // 2, MAGENTA
    put_pixel(urgb_u32(3, 0, 7), RING);   // 3
    put_pixel(urgb_u32(1, 0, 10), RING);  // 4
    put_pixel(urgb_u32(0, 0, 12), RING);  // 5, BLUE
    put_pixel(urgb_u32(0, 1, 10), RING);   // 6
    put_pixel(urgb_u32(0, 2, 8), RING);   // 7
    put_pixel(urgb_u32(0, 4, 5), RING);   // 8, CYAN
    put_pixel(urgb_u32(0, 6, 4), RING);   // 9
    put_pixel(urgb_u32(0, 8, 2), RING);   // A
    put_pixel(urgb_u32(0, 10, 0), RING);  // B, GREEN
    put_pixel(urgb_u32(2, 7, 0), RING);   // C
    put_pixel(urgb_u32(5, 5, 0), RING);   // D, YELLOW
    put_pixel(urgb_u32(7, 3, 0), RING);   // E
    put_pixel(urgb_u32(9, 2, 0), RING);   // F

    // for (uint8_t i = 0; i < RING_PIXELS; i++) {
    //     if (i == 0) put_pixel(urgb_u32(10, 0, 0), RING);
    //     else if (i == TRIAD1) put_pixel(urgb_u32(0, 0, 10), RING);
    //     else if (i == TRIAD2) put_pixel(urgb_u32(10, 10, 0), RING);
    //     else put_pixel(urgb_u32(0, 0, 0), RING);
    // }

}
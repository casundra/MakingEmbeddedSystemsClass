
#include <stdio.h>
#include <stdlib.h>
#include "ledpatterns.h"

// To Do:
// - 

extern uint8_t gammaCorr;

const uint8_t gammaMatrix[2][256] =
{ 
    // linear / uncorrected
    { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 
    16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 
    32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 
    48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 
    64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 
    80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 
    96, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 
    112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 
    128, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 
    144, 145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158, 159, 
    160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172, 173, 174, 175, 
    176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186, 187, 188, 189, 190, 191, 
    192, 193, 194, 195, 196, 197, 198, 199, 200, 201, 202, 203, 204, 205, 206, 207, 
    208, 209, 210, 211, 212, 213, 214, 215, 216, 217, 218, 219, 220, 221, 222, 223, 
    224, 225, 226, 227, 228, 229, 230, 231, 232, 233, 234, 235, 236, 237, 238, 239, 
    240, 241, 242, 243, 244, 245, 246, 247, 248, 249, 250, 251, 252, 253, 254, 255},

    // corrected by factor of 2.8 re: adafruit tutorial
    // https://learn.adafruit.com/led-tricks-gamma-correction/the-longer-fix
    // Con: large dead zone near zero
   {0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,
    1,  1,  1,  1,  1,  1,  1,  1,  1,  2,  2,  2,  2,  2,  2,  2,
    2,  3,  3,  3,  3,  3,  3,  3,  4,  4,  4,  4,  4,  5,  5,  5,
    5,  6,  6,  6,  6,  7,  7,  7,  7,  8,  8,  8,  9,  9,  9, 10,
   10, 10, 11, 11, 11, 12, 12, 13, 13, 13, 14, 14, 15, 15, 16, 16,
   17, 17, 18, 18, 19, 19, 20, 20, 21, 21, 22, 22, 23, 24, 24, 25,
   25, 26, 27, 27, 28, 29, 29, 30, 31, 32, 32, 33, 34, 35, 35, 36,
   37, 38, 39, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 50,
   51, 52, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 66, 67, 68,
   69, 70, 72, 73, 74, 75, 77, 78, 79, 81, 82, 83, 85, 86, 87, 89,
   90, 92, 93, 95, 96, 98, 99,101,102,104,105,107,109,110,112,114,
  115,117,119,120,122,124,126,127,129,131,133,135,137,138,140,142,
  144,146,148,150,152,154,156,158,160,162,164,167,169,171,173,175,
  177,180,182,184,186,189,191,193,196,198,200,203,205,208,210,213,
  215,218,220,223,225,228,231,233,236,239,241,244,247,249,252,255}
};


// All pattern functions create a local copy of the Color structure so that RGB values can be modified for
// correct brightness display. 

// Local function, always called from pattern functions.
// Modifies the local copy of Color for proper brightness display.
static void adjustBrightness(Color *brtadj) {
    // colors are multiplied by brightness %
    // brightness = 0-255, ">> 8" divides by 256
    uint8_t brtness = gammaMatrix[gammaCorr][brtadj->brt];
    uint32_t red = (brtadj->red * brtness) >> 8;
    uint32_t grn = (brtadj->grn * brtness) >> 8;
    uint32_t blu = (brtadj->blu * brtness) >> 8;
    brtadj->red = (uint8_t) red;
    brtadj->grn = (uint8_t) grn;
    brtadj->blu = (uint8_t) blu;
}

void ringSolidColor(Color color) {
    adjustBrightness(&color);
    uint8_t numLEDs = RING_PIXELS;
    for (uint8_t i = 0; i < numLEDs; i++) {
        put_pixel(urgb_u32((uint8_t) color.red, (uint8_t) color.grn, (uint8_t) color.blu), RING);
    }
}

void matrixSolidColor(Color color) {
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
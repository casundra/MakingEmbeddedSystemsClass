
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "ledpatterns.h"
#include "console.h"

// from main.c
extern uint8_t gammaCorr;

// gammaMatrix is a lookup table for brightness that corrects for our eyeballs' non-linear perception of brightness
// another great article on gamma correction: https://hackaday.com/2016/08/23/rgb-leds-how-to-master-gamma-and-hue-for-perfect-brightness/
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

// Order of Operations:
// Strip info, an array of color values for the strip, and new Color value are passed into pattern functions
// Pattern functions overwrite the array of color values for the strip
// Pattern function then calls showIt
// showIt adjusts a copy of individual color values for brightness, then sends the adjusted color to the strip
// Done this way to preserve showIt as an independent function that could be called if PWM dithering is added in the future.

// Local function, called inside of show
// Returns a brightness-adjusted single Color
Color adjustBrightness(Color color, uint8_t brtness) {
    // colors are multiplied by brightness %
    // brightness = 0-255, ">> 8" divides by 256
    uint8_t gammaBright = gammaMatrix[gammaCorr][brtness];
    uint32_t grn = (color.grn * gammaBright) >> 8;
    uint32_t red = (color.red * gammaBright) >> 8;
    uint32_t blu = (color.blu * gammaBright) >> 8;
    Color adjColor;
    adjColor.red = (uint8_t) red;
    adjColor.grn = (uint8_t) grn;
    adjColor.blu = (uint8_t) blu;
    return adjColor;
}

// Shows the colors loaded in stripColors on the physical strip
// Adjusts for brightness just before
void showIt(Strip strip, Color stripColors[]) {
    for (uint8_t i = 0; i < strip.len; i++) {
        Color adjustedColor = adjustBrightness(stripColors[i], (uint8_t) strip.brt);
        put_pixel(urgb_u32((uint8_t) adjustedColor.red, (uint8_t) adjustedColor.grn, (uint8_t) adjustedColor.blu), strip.sm);
    }
}

// Prints the RGB values of a Color to the serial port
// Used for testing encoder adjustment of color
void printColor(Color color) {
    printf("Red: %d  \tGrn: %d  \tBlu: %d\n", color.red, color.grn, color.blu);
}

// Loads a solid color into a strip of a given length
// Also shows because why not
void loadSolidColor(Strip strip, Color stripColors[], Color color) {
    for (uint8_t i = 0; i < strip.len; i++) {
        stripColors[i].red = color.red;
        stripColors[i].grn = color.grn;
        stripColors[i].blu = color.blu;
    }
    showIt(strip, stripColors);
}

// To Do:
// Figure out the split if a matrix has an odd number of rows or cols
// or is rectangular, would be nice to not change in the middle of a row

// Loads half the strip with the active color and half with its complement
void loadComplement(Strip strip, Color stripColors[], Color color) {
    uint8_t halfStrip = strip.len >> 1;
    for (uint8_t i = 0; i < halfStrip; i++) {
        stripColors[i].red = color.red;
        stripColors[i].grn = color.grn;
        stripColors[i].blu = color.blu;
    }

    for (uint8_t i = halfStrip; i < strip.len; i++) {
        stripColors[i].red = 255 - color.red;
        stripColors[i].grn = 255 - color.grn;
        stripColors[i].blu = 255 - color.blu;
    }
    showIt(strip, stripColors);
}

#define STEPS   (256 / RING_PIXELS)
#define TRIAD1  (RING_PIXELS / 3)
#define TRIAD2  (RING_PIXELS - TRIAD1)

const uint8_t wheelColors[][48] = {
    { // RYB hand adjusted
    200,0,0,
    200,0,20,
    100,0,100,
    60,0,140,
    20,0,200,
    0,0,240,
    0,40,160,
    0,140,60,
    0,200,0,
    20,200,0,
    60,140,0,
    100,100,0,
    100,80,0,
    160,80,0,
    180,40,0,
    200,20,0,
    }, 

    // { // RGB perfectly even angles but looks bad   
    // 255,0,0,
    // 255,94,0,
    // 255,191,0,
    // 255,255,0,
    // 128,255,0,
    // 34,255,0,
    // 0,255,64,
    // 0,255,157,
    // 0,255,255,
    // 0,162,255,
    // 0,64,255,
    // 30,0,255,
    // 128,0,255,
    // 221,0,255,
    // 255,0,191,
    // 255,0,98,
    // }

    { // RGB hand adjusted    
    200,0,0,
    200,0,20,
    100,0,100,
    60,0,140,
    20,0,200,
    0,0,240,
    0,20,200,
    0,40,160,
    0,80,100,
    0,120,80,
    0,160,40,
    0,200,0,
    40,140,0,
    100,100,0,
    140,60,0,
    180,40,0,
    }
};

// assumes a fixed 16 LED wheel
// To Do: make dynamic based off of wheel size
void loadColorWheel (Strip strip, Color stripColors[], uint8_t type) {
    
    for (uint8_t i = 0; i < strip.len; i++) {
        stripColors[i].red = wheelColors[type][i*3];
        stripColors[i].grn = wheelColors[type][i*3+1];
        stripColors[i].blu = wheelColors[type][i*3+2];
    }
    showIt(strip, stripColors);
}

// The following is for RGB to HSL colorspace transformation.
// This is needed to get the appropriate position of a color around the wheel.
// I'm initially going to throw caution to the wind and do it all floating point
// because I have cycles to buuuuuuuuuurn, bitcheeeeeees!  If I have time, 
// I'll profile this and then switch to integer math and see if there's a
// big time difference.  I'd do it by toggling an output at the beginning and 
// end of the transformation and measuring it with a scope.

// the following algorithm is from:
// Nikolai Waldman
// https://www.niwa.nu/2013/05/math-behind-colorspace-conversions-rgb-hsl/

// hue is basically the color in degrees around the color wheel
HSL rgb2hsl (Color color) {

    HSL hslColor = {0};

    // Calculates max and min
    // To Do: 
    // Refactor to multiple by 1000 first, and not have to deal with floating point
    float red = (float) color.red / 255;
    float grn = (float) color.grn / 255;
    float blu = (float) color.blu / 255;
    float maxrg = fmaxf(red, grn);
    float maxgb = fmaxf(grn, blu);
    float maxmax = fmaxf(maxrg, maxgb);
    float minrg = fminf(red, grn);
    float mingb = fminf(grn, blu);
    float minmin = fminf(minrg, mingb);

    // Calculate luminesence
    float lumin = (maxmax + minmin) / 2;

    // Calculate Saturation
    float satur;
    if (maxmax == minmin) satur = 0;
    else if (lumin <= 0.5) satur = (maxmax - minmin) / (maxmax + minmin);
    else satur = (maxmax - minmin) / (2.0 - maxmax - minmin);

    // Calculate Hue, which is degrees around the color wheel
    float hue;
    if ( (color.red == color.grn) && (color.grn == color.blu) ) {
        hue = 0;
        hslColor.hue = (uint16_t) hue;
        hslColor.sat = satur;
        hslColor.lum = lumin;
        return hslColor;
    }

    if (maxmax == red)      hue = (grn - blu) / (maxmax - minmin);
    else if (maxmax == grn) hue = 2.0 + (blu - red) / (maxmax - minmin);    // 2.09 is 120 deg in radians?
    else                    hue = 4.0 + (red - grn) / (maxmax - minmin);    // 4.19 is 240 deg in radians?

    hue *= 60;
    if (hue < 0) hue += 360;

    // Pack HSL into the HSL structure
    hslColor.hue = (uint16_t) hue;
    hslColor.sat = satur;
    hslColor.lum = lumin;

    return hslColor;
}

// Helper function for hsl2rgb
// Calculates intermediate terms for red, green, blue
static float hslCalcColor (float colorInt, float lI1, float lI2) {
    float color = 0;
    if ( (6.0 * colorInt) < 1)        color = lI2 + (lI1 - lI2) * 6.0 * colorInt;
    else if ( (2.0 * colorInt) < 1)   color = lI1;
    else if ( (3.0 * colorInt) < 2)   color = lI2 + (lI1 - lI2) * (0.666 - colorInt) * 6.0;
    else                            color = lI2;
    return color;
}

// To Do: 
// Refactor to not use floating point
// Properly round up/down
Color hsl2rgb (HSL hslColor) {

    Color color = {0};
    float fred, fgrn, fblu = 0;

    if (hslColor.sat == 0) {
        float rgb = hslColor.lum * 255;
        color.red = (uint8_t) rgb;
        color.grn = (uint8_t) rgb;
        color.blu = (uint8_t) rgb;
        return color;
    }

    float lumInt1, lumInt2 = 0;
    if (hslColor.lum < 0.5) lumInt1 = hslColor.lum * (1.0 + hslColor.sat);
    else lumInt1 = hslColor.lum + hslColor.sat - (hslColor.lum * hslColor.sat);
 
    lumInt2 = (2.0 * hslColor.lum) - lumInt1;

    float hue = hslColor.hue / 360.0;

    float rInt, gInt, bInt = 0;
    rInt = hue + 0.333;
    if (rInt > 1) rInt -= 1.0;
    gInt = hue;
    bInt = hue - 0.333;
    if (bInt < 0) bInt += 1.0;

    fred = hslCalcColor(rInt, lumInt1, lumInt2);
    fgrn = hslCalcColor(gInt, lumInt1, lumInt2);
    fblu = hslCalcColor(bInt, lumInt1, lumInt2);

    // printf("\nlumInt1: ");
    // printf("%f\n", lumInt1);
    // printf("lumInt2: ");
    // printf("%f\n", lumInt2);
    // printf("hue: ");
    // printf("%f\n", hue); 
    // printf("rInt: ");
    // printf("%f\n", rInt);
    // printf("gInt: ");
    // printf("%f\n", gInt);
    // printf("bInt: ");
    // printf("%f\n", bInt);
    // printf("fred: ");
    // printf("%f\n", fred);
    // printf("fgrn: ");
    // printf("%f\n", fgrn);
    // printf("fblu: ");
    // printf("%f\n", fblu);

    fred *= 255.0;
    fgrn *= 255.0;
    fblu *= 255.0;

    // printf("fred: ");
    // printf("%f\n", fred);
    // printf("fgrn: ");
    // printf("%f\n", fgrn);
    // printf("fblu: ");
    // printf("%f\n", fblu);


    color.red = (uint8_t) fred;
    color.grn = (uint8_t) fgrn;
    color.blu = (uint8_t) fblu;

    return color;
}



  // // a decent RYB color wheel
    // put_pixel(urgb_u32(10, 0, 0), RING_SM);  // 0, RED
    // put_pixel(urgb_u32(10, 0, 1), RING_SM);  // 1
    // put_pixel(urgb_u32(5, 0, 5), RING_SM);   // 2, PURPLE
    // put_pixel(urgb_u32(3, 0, 7), RING_SM);   // 3
    // put_pixel(urgb_u32(1, 0, 10), RING_SM);  // 4
    // put_pixel(urgb_u32(0, 0, 12), RING_SM);  // 5, BLUE
    // put_pixel(urgb_u32(0, 2, 8), RING_SM);   // 6
    // put_pixel(urgb_u32(0, 7, 3), RING_SM);   // 7
    // put_pixel(urgb_u32(0, 10, 0), RING_SM);  // 8, GREEN
    // put_pixel(urgb_u32(1, 10, 0), RING_SM);  // 9
    // put_pixel(urgb_u32(3, 7, 0), RING_SM);   // A
    // put_pixel(urgb_u32(5, 5, 0), RING_SM);   // B, YELLOW
    // put_pixel(urgb_u32(5, 4, 0), RING_SM);   // C
    // put_pixel(urgb_u32(8, 4, 0), RING_SM);   // D, ORANGE
    // put_pixel(urgb_u32(9, 2, 0), RING_SM);   // E
    // put_pixel(urgb_u32(10, 1, 0), RING_SM);  // F

    // display RYB at approx 120 degrees
    // for (uint8_t i = 0; i < RING_PIXELS; i++) {
    //     if (i == 0) put_pixel(urgb_u32(10, 0, 0), RING_SM);
    //     else if (i == TRIAD1) put_pixel(urgb_u32(0, 0, 10), RING_SM);
    //     else if (i == TRIAD2) put_pixel(urgb_u32(10, 10, 0), RING_SM);
    //     else put_pixel(urgb_u32(0, 0, 0), RING_SM);
    // }

//     // a decent RGB color wheel
//     put_pixel(urgb_u32(10, 0, 0), RING_SM);  // 0, RED
//     put_pixel(urgb_u32(10, 0, 1), RING_SM);  // 1
//     put_pixel(urgb_u32(5, 0, 5), RING_SM);   // 2, MAGENTA
//     put_pixel(urgb_u32(3, 0, 7), RING_SM);   // 3
//     put_pixel(urgb_u32(1, 0, 10), RING_SM);  // 4
//     put_pixel(urgb_u32(0, 0, 12), RING_SM);  // 5, BLUE
//     put_pixel(urgb_u32(0, 1, 10), RING_SM);   // 6
//     put_pixel(urgb_u32(0, 2, 8), RING_SM);   // 7
//     put_pixel(urgb_u32(0, 4, 5), RING_SM);   // 8, CYAN
//     put_pixel(urgb_u32(0, 6, 4), RING_SM);   // 9
//     put_pixel(urgb_u32(0, 8, 2), RING_SM);   // A
//     put_pixel(urgb_u32(0, 10, 0), RING_SM);  // B, GREEN
//     put_pixel(urgb_u32(2, 7, 0), RING_SM);   // C
//     put_pixel(urgb_u32(5, 5, 0), RING_SM);   // D, YELLOW
//     put_pixel(urgb_u32(7, 3, 0), RING_SM);   // E
//     put_pixel(urgb_u32(9, 2, 0), RING_SM);   // F
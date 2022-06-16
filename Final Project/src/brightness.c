#include <stdio.h>
#include <stdlib.h>
#include "brightness.h"
#include "hardware/adc.h"
#include "console.h"

#define OFFSET_MV   220

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

uint8_t readBright(Color *color) {
    uint16_t brightness = adc_read();
    color->brt = brightness >> 4;
    return color->brt;
}

// eCommandResult_T calBright () {
//     uint8_t received = 0;
//     uint16_t loOffset;
//     uint16_t hiOffset;
// 	eCommandResult_T result;
//     ConsoleIOSendString("Turn knob all the way CCW (left), then press <Enter>");
//     result = ConsoleReceiveParamUint8(buffer, 1, &received);
//     if (received == '\n') {
//         loOffset = adc_read;
//         received = 0;
//     }
//     else {
//         ConsoleIOSendString("Invalid Entry");
//         return result;
//     }
//     ConsoleIOSendString("Turn knob all the way CW (right), then press <Enter>");
//     result = ConsoleReceiveParamUint8(buffer, 1, &received);
//     if (received == '\n') {
//         hiOffset = adc_read;
//     }
//     else {
//         ConsoleIOSendString("Invalid Entry");
//         return result;
//     }

// }

// static eCommandResult_T ConsoleCommandParamExampleInt16(const char buffer[])
// {
// 	int16_t parameterInt;
// 	eCommandResult_T result;
// 	result = ConsoleReceiveParamInt16(buffer, 1, &parameterInt);
// 	if ( COMMAND_SUCCESS == result )
// 	{
// 		ConsoleIoSendString("Parameter is ");
// 		ConsoleSendParamInt16(parameterInt);
// 		ConsoleIoSendString(" (0x");
// 		ConsoleSendParamHexUint16((uint16_t)parameterInt);
// 		ConsoleIoSendString(")");
// 		ConsoleIoSendString(STR_ENDLINE);
// 	}
// 	return result;
// }
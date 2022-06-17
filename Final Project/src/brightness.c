#include <stdio.h>
#include <stdlib.h>
#include "brightness.h"
#include "hardware/adc.h"
#include "console.h"

#define OFFSET_MV   220
#define BRTLEN      16  // if this is changed, also need to change averaging bit-shifting

static uint16_t Brightness[BRTLEN] = {0};
static uint16_t *pBright = &Brightness[0];



// Loads brightness values into array and returns average
// Sleep time is calculated so it takes ~ 1s
uint8_t brightInit(Color *color) {
    uint16_t brightNow = 0;
    uint32_t brightSum = 0;
    for (uint8_t i = 0; i < BRTLEN; i++) {
        brightNow = adc_read();
        Brightness[i] = brightNow;
        brightSum += brightNow;
        sleep_ms(50);
    }
    return brightSum >> 8;  // divide by 16 for average, and again for uint8 transformation
}

// Reads the potentiometer and adds new brightness value to circular buffer
// Places the new brightness average into Color structure to be output to LEDs
// Also returns the average
// This might be a brute force inelegant buffer, but it's easy for me to write & understand.
uint8_t brightRead(Color *color) {
    uint16_t brightNow = adc_read();
    *pBright = brightNow;
    uint32_t brightSum = 0;
    for (uint8_t i = 0; i < BRTLEN; i++) {
        brightSum += Brightness[i];
    }

    if (pBright >= &Brightness[0] + BRTLEN) pBright = &Brightness[0];
    else pBright++;

    color->brt = brightSum >> 8;
    return color->brt;
}

//  To Do: a calibration via serial port for each end of the knob
//
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
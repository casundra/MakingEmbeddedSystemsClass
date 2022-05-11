
#ifndef ENCODERS_H
#define ENCODERS_H

#include <stdlib.h>

#define CW  0
#define CCW 1

void encoder_init(uint phasea, uint phaseb);
uint8_t encoder_read();


#endif
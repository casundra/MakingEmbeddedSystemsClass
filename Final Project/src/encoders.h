
#ifndef ENCODERS_H
#define ENCODERS_H

#include <stdlib.h>

#define CW  0
#define CCW 1

void encoder_init(uint phasea, uint phaseb);
void encoder_read(uint8_t phasea, uint8_t phaseb, int16_t *counts, uint8_t *dir);


#endif
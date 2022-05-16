
#ifndef ENCODERS_H
#define ENCODERS_H

#include <stdlib.h>

#define CW  0
#define CCW 1

typedef struct EncoderStruct {
	const uint8_t phPinA;
	const uint8_t phPinB;
	volatile uint8_t debounce;
	volatile int16_t counts;
	volatile uint8_t dir;
} Encoder;

void encoder_init(uint phasea, uint phaseb);
void encoder_read(Encoder encoder);
//void encoder_read(uint8_t phasea, uint8_t phaseb, int16_t *counts, uint8_t *dir);
//void encoder_read(uint8_t phasea, uint8_t phaseb, int16_t counts, uint8_t dir);

#endif
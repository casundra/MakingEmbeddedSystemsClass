
#ifndef ENCODERS_H
#define ENCODERS_H

#include <stdlib.h>

#define CW  1
#define CCW -1

typedef struct EncoderStruct {
	const uint8_t phPinA;
	const uint8_t phPinB;
	volatile uint8_t debounce;
	volatile int16_t counts;
	volatile int8_t dir;
} Encoder;

void encoder_init(uint phasea, uint phaseb);
void encoder_read(Encoder *encoder);
void encoder_inc(Encoder *encoder);

#endif
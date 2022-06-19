
#ifndef ENCODERS_H
#define ENCODERS_H

#include <stdlib.h>

#define CW  1
#define CCW -1

typedef struct EncoderStruct {
	const uint8_t phPinA;
	const uint8_t phPinB;
	volatile uint8_t debounce;
	volatile int16_t counts;	// absolute position, -256 to 255 gives 8.5 turns in either direction
	volatile int8_t change;		// change in counts since last reading
	volatile int8_t dir;
} Encoder;

// see .c file for full comments on each function
void encoder_init(uint phasea, uint phaseb);
void button_init(uint pin);
uint8_t button_read(uint8_t pin);
uint8_t encoder_readA(Encoder *encoder);
uint8_t encoder_readB(Encoder *encoder);
uint8_t encoder_inc(Encoder *encoder);
uint8_t encoder_print(int16_t lcounts, int16_t mcounts, int16_t rcounts, uint8_t update);

#endif
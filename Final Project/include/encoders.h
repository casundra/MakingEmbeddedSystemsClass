
// Copyright 2022 by Carrie Sundra, Alpenglow Industries
// www.alpenglowindustries.com
// @alpenglowind on twitter & instagram
// Alpenglow Industries on GitHub & YouTube
//
// MIT License

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
void encoder_init(uint phasea, uint phaseb);	// initializes phase pins and interrupts
void button_init(uint pin);						// initializes button pin and interrupt
uint8_t button_read(uint8_t pin);			// reads the button (physically part of the encoders)
uint8_t encoder_readA(Encoder *encoder);	// reads phase A of encoder
uint8_t encoder_readB(Encoder *encoder);	// reads phase B of encoder
uint8_t encoder_inc(Encoder *encoder);		// increments encoder counts
uint8_t encoder_print(int16_t lcounts, int16_t mcounts, int16_t rcounts, uint8_t update);	// test function, prints encoder values to serial port

#endif
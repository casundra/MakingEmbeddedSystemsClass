/* functions to read rotary encoders
*/

#include <stdio.h>
#include "encoders.h"
#include "palled.h"
#include <hardware/gpio.h>



// phasea and phaseb are the encoder pins
// sets them as inputs with pullups and irqs enabled
void encoder_init(uint phasea, uint phaseb) {
    gpio_init(phasea);
    gpio_init(phaseb);
    gpio_set_dir(phasea, GPIO_IN);
    gpio_set_dir(phaseb, GPIO_IN);
    gpio_pull_up(phasea);
    gpio_pull_up(phaseb);
    sleep_ms(10);
    gpio_set_irq_enabled(phasea, GPIO_IRQ_EDGE_RISE, 1);
    gpio_set_irq_enabled(phaseb, GPIO_IRQ_EDGE_FALL, 1);
}

// for now buttons are part of the encoders
// (push down on stalk)
// sets them as inputs with pullups and irqs enabled
void button_init(uint pin) {
    gpio_init(pin);
    gpio_set_dir(pin, GPIO_IN);
    gpio_pull_up(pin);
    sleep_ms(10);
    gpio_set_irq_enabled(pin, GPIO_IRQ_EDGE_FALL, 1);
}

// Since the RP2040 doesn't have both edge interrupt capability,
// we have to read Phase A on rising edge interrupt and 
// Phase B on a falling edge interrupt.  With both, we can get
// a count change with every detent.  Otherwise, it would take 
// two detents to register a count change.  This is because encoders
// are either shorted to the common terminal (usually C or GND) or 
// detached from the common with every detent.  In other words, 
// each phase is either open or closed with respect to COM with
// each twist/detent.

// Note that when breadboarding encoders, the wires are very sensitive to crosstalk.
// Encoders are debounced in hardware with 4.99k resistor and 0.1uF cap.

// Reads encoder phase A pins and determines direction of rotation
// It is assumed that this is called from an interrupt,
// just after Phase A has gone high.
uint8_t encoder_readA(Encoder *encoder) {
    uint8_t changed = 0;
    uint8_t pha = gpio_get(encoder->phPinA);
    uint8_t phb = gpio_get(encoder->phPinB);
    if (pha) {
        if (phb) {
            encoder->dir = CCW;
            changed = encoder_inc(encoder);
        }
        else {
            encoder->dir = CW;
            changed = encoder_inc(encoder);
        }
    }
    // ignores it as bounce if Phase A is low immediately after interrupt fires
    return changed;
}

// Reads encoder phase B pins and determines direction of rotation
// It is assumed that this is called from an interrupt,
// just after Phase B has gone low.
uint8_t encoder_readB(Encoder *encoder) {
    uint8_t changed = 0;
    uint8_t pha = gpio_get(encoder->phPinA);
    uint8_t phb = gpio_get(encoder->phPinB);
    if (!phb) {
        if (pha) {
            encoder->dir = CCW;
            changed = encoder_inc(encoder);
        }
        else {
            encoder->dir = CW;
            changed = encoder_inc(encoder);
        }
    }
    // ignores it as bounce if Phase B is low immediately after interrupt fires
    return changed;
}

// Increments the encoder's count
// Direction is either -1 or +1
// Adding dir to counts automatically inc/dec depending on direction
uint8_t encoder_inc(Encoder *encoder) {
    encoder->counts += encoder->dir;
    encoder->change += encoder->dir;
    return 1;
}

// Prints encoder count to the serial port only when knobs are moved
uint8_t encoder_print(int16_t lcounts, int16_t mcounts, int16_t rcounts, uint8_t update) {
    if (update) {
        printf("Left: %d \tMiddle: %d\tRight: %d\n", lcounts, mcounts, rcounts);
        update = 0;
    }
    return update;
}
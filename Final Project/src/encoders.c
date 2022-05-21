/* functions to read rotary encoders
*/

#include "encoders.h"
#include "pinout.h"
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

// Reads encoder phase A pins and determines direction of rotation
// It is assumed that this is called from an interrupt,
// just after Phase A has gone high.
void encoder_readA(Encoder *encoder) {
    uint8_t pha = gpio_get(encoder->phPinA);
    uint8_t phb = gpio_get(encoder->phPinB);
    if (pha) {
        if (phb) {
            encoder->dir = CCW;
            encoder_inc(encoder);
        }
        else {
            encoder->dir = CW;
            encoder_inc(encoder);
        }
    }
    // ignores it as bounce if Phase A is low immediately after interrupt fires
}

// Reads encoder phase B pins and determines direction of rotation
// It is assumed that this is called from an interrupt,
// just after Phase B has gone low.
void encoder_readB(Encoder *encoder) {
    uint8_t pha = gpio_get(encoder->phPinA);
    uint8_t phb = gpio_get(encoder->phPinB);
    if (!phb) {
        if (pha) {
            encoder->dir = CCW;
            encoder_inc(encoder);
        }
        else {
            encoder->dir = CW;
            encoder_inc(encoder);
        }
    }
    // ignores it as bounce if Phase B is low immediately after interrupt fires
}

// Increments the encoder's count
// Direction is either -1 or +1
// Adding dir to counts automatically inc/dec depending on direction
void encoder_inc(Encoder *encoder) {
    encoder->counts += encoder->dir;
}

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
    gpio_set_irq_enabled(phasea, GPIO_IRQ_EDGE_RISE, 1);
}

// phasea and phaseb are the encoder pins
// counts is a global variable that keeps track of that encoder's relative position
// dir is a global variable that keeps track of direction
void encoder_read(Encoder *encoder) {
    uint8_t pha = gpio_get(encoder->phPinA);
    uint8_t phb = gpio_get(encoder->phPinB);
    if (pha) {
        if (phb) {
            // *dir = CCW;
            // *counts--;
            encoder->dir = CCW;
            encoder->counts--;
        }
        else {
            // *dir = CW;
            // *counts++;
            encoder->dir = CW;
            encoder->counts++;
        }
    }
    // ignores it as bounce if Phase A is low immediately after interrupt fires
    encoder->debounce = 0;
}

// // phasea and phaseb are the encoder pins
// // counts is a global variable that keeps track of that encoder's relative position
// // dir is a global variable that keeps track of direction
// void encoder_read(uint8_t phasea, uint8_t phaseb, int16_t counts, uint8_t dir) {
//     uint8_t pha = gpio_get(phasea);
//     uint8_t phb = gpio_get(phaseb);
//     if (pha) {
//         if (phb) {
//             // *dir = CCW;
//             // *counts--;
//             dir = CCW;
//             counts--;
//         }
//         else {
//             // *dir = CW;
//             // *counts++;
//             dir = CW;
//             counts++;
//         }
//     }
//     // ignores it as bounce if Phase A is low immediately after interrupt fires
// }
/* functions to read rotary encoders
*/

#include "encoders.h"
#include "pinout.h"
#include <hardware/gpio.h>

void encoder_init(uint phasea, uint phaseb) {
    gpio_init(RIGHTA);
    gpio_init(RIGHTB);
    gpio_set_dir(RIGHTA, GPIO_IN);
    gpio_set_dir(RIGHTB, GPIO_IN);
    gpio_pull_up(RIGHTA);
    gpio_pull_up(RIGHTB);
   // gpio_set_irq_enabled(phasea, GPIO_IRQ_EDGE_RISE, 1);


        
}
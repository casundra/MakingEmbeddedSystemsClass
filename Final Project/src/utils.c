/*
    Helpful general functions

*/

#include "utils.h"
#include "pinout.h"

uint32_t time_ms() {
    return to_ms_since_boot( get_absolute_time() );
}


// could probably use Pico built-in alarm/timers to do this
void heartbeat() {
    static uint32_t lastBlink = 0;
    if ( time_ms() - lastBlink > BLINK_TIME ) {
        gpio_xor_mask(1 << LED_PIN);
        lastBlink = time_ms();
    }
}
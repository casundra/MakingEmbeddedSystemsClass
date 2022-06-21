// Copyright 2022 by Carrie Sundra, Alpenglow Industries
// www.alpenglowindustries.com
// @alpenglowind on twitter & instagram
// Alpenglow Industries on GitHub & YouTube
//
// MIT License

/*
    Helpful general functions

*/
#include <stdio.h>
#include "utils.h"
#include "palled.h"

uint32_t time_ms() {
    return to_ms_since_boot( get_absolute_time() );
}

void heartbeat_init() {
	gpio_init(LED_PIN);
	gpio_set_dir(LED_PIN, GPIO_OUT);
}

// could probably use Pico built-in alarm/timers to do this
void heartbeat() {
    static uint32_t lastBlink = 0;
    if ( time_ms() - lastBlink > BLINK_TIME ) {
        gpio_xor_mask(1 << LED_PIN);
        lastBlink = time_ms();
    }
}

// Hello World Serial Heartbeat
void serialHeartbeat() {
    static uint32_t lastPrint = 0;
    if (time_ms() - lastPrint > PRINT_TIME)	{
        printf("Hello World\n");
        lastPrint = time_ms();
    }
}
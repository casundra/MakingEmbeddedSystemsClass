#include <stdio.h>
#include "pico/stdlib.h"

int main(void)
{  
    stdio_init_all();
    sleep_ms(3000);
    printf("\n\nHello World\n");
    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);
    while (true)
    {
        gpio_put(PICO_DEFAULT_LED_PIN, 1);
        sleep_ms(500);
        gpio_put(PICO_DEFAULT_LED_PIN, 0);
        sleep_ms(500);
        printf("\n\nHello World\n");
    }
}

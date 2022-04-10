// Example code grabbed from https://github.com/platformio/platform-raspberrypi/blob/master/examples/arduino-blink/src/main.cpp
// Where are the HAL source files for direct register access?
// ah-ha! C:\Users\(username)\.platformio\packages\framework-arduino-mbed\cores\arduino\mbed\hal
// and registers & structs .platformio\packages\framework-arduino-mbed\cores\arduino\mbed\targets\TARGET_RASPBERRYPI\TARGET_RP2040\pico-sdk\rp2040
//
// To first program a Pico with Platformio, run Build.  Do NOT Upload.
// Build creates a "firmware.uf2" file in your project folder/.pio\build\pico
// Drag and drop this onto the Mass Storage Device your Pico identified as (should be "RPI-RP2")
// Afterwards it will enumerate as a COM port, and then you can upload with the "Upload" button.
// To get back in bootloader/UF2 mode, unplug and replug while pressing BOOTSEL button.

#include <Arduino.h>
#include <hardware/gpio.h>

#define LED_PIN   25    // looked @ schematic, this is the built-in LED
#define BUTT_PIN  1
#define DEBOUNCE_TIME 200

volatile uint32_t buttTime = 0;
volatile uint8_t buttPressed = 0;

void irq_butt (uint gpio, uint32_t events) {
  if (!buttPressed) {
    buttTime = millis();
    buttPressed = 1;
  }
}

// the setup routine runs once when you press reset:
void setup() {

  _gpio_init(LED_PIN);
  gpio_set_dir(LED_PIN, GPIO_OUT);
  _gpio_init(BUTT_PIN);
  gpio_set_dir(BUTT_PIN, GPIO_IN);
  gpio_pull_up(BUTT_PIN);
  gpio_set_irq_enabled_with_callback(BUTT_PIN, GPIO_IRQ_EDGE_FALL, 1, &irq_butt);

}

// the loop routine runs over and over again forever:
void loop() {

  if (buttPressed && (millis() - buttTime > DEBOUNCE_TIME)){
    gpio_xor_mask(1 << LED_PIN);   // toggles LED
    buttPressed = 0;
  }
 
  // delay(250);

  // while (!gpio_get(BUTT_PIN)) gpio_put(LED_PIN, HIGH);
  // gpio_put(LED_PIN, LOW);
}
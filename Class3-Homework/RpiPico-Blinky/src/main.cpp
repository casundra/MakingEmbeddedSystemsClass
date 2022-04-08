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

// the setup routine runs once when you press reset:
void setup() {
  // initialize the digital pin as an output.
  pinMode(LED_BUILTIN, OUTPUT);
}

// the loop routine runs over and over again forever:
void loop() {
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);               // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);               // wait for a second
}
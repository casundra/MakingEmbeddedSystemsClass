# Blinky on Raspberry Pi Pico with PlatoformIO
Example code grabbed from https://github.com/platformio/platform-raspberrypi/blob/master/examples/arduino-blink/src/main.cpp

Where are the HAL source files for direct register access?

ah-ha! C:\Users\(username)\.platformio\packages\framework-arduino-mbed\cores\arduino\mbed\hal

and registers & structs .platformio\packages\framework-arduino-mbed\cores\arduino\mbed\targets\TARGET_RASPBERRYPI\TARGET_RP2040\pico-sdk\rp2040

To first program a Pico with Platformio, run Build.  Do NOT Upload.

Build creates a "firmware.uf2" file in your project folder/.pio\build\pico

Drag and drop this onto the Mass Storage Device your Pico identified as (should be "RPI-RP2")

Afterwards it will enumerate as a COM port, and then you can upload with the "Upload" button.

To get back in bootloader/UF2 mode, unplug and replug while pressing BOOTSEL button.

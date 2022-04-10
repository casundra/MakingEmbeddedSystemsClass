# RPi Pico Blinky via Wizio platform, "baremetal" framework, with PlatformIO

This basically installs the Raspberry Pi SDK as the only dependency in PlatformIO.  I think it's more or less equivalent to using VSCode with the SDK without PlatformIO?  I'm still figuring out this toolchain, it's new to me.

Followed tutorial here, except that the default main.c is already set up for Blinky  
https://dev.to/admantium/raspberry-pico-the-simple-startup-with-platformio-5451

Using WizIO plaform (advanced installation) here:  
https://github.com/Wiz-IO/wizio-pico

Board: pico-dap  
Framework: baremetal

Looked at options here for adjusting platformio.ini to spit data out of USB serial port:  
https://github.com/Wiz-IO/wizio-pico/wiki/BAREMETAL

added the following to the minimal .ini file.  Note that you'll probably have to do 2 programming steps - pick any COM port at first, then once the Pico enumerates, change it to whatever number it enumerates as.

monitor_port = COM9  
monitor_speed = 115200  
build_flags = -D LIB_PICO_STDIO_USB

To get the Serial Console running in PlatformIO, I had to type CNTL-ALT-S.  It picked up the Pico's COM port & 115200 by default.  
Also, I was suddenly able to load code via USB, without doing the BOOTSEL button dance.  Yay!

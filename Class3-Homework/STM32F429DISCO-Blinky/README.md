# Blinky Project for STM32F429DISCO board using PlatformIO

I created a new project in Platformio.
For whatever reason, even though the STM32F429 Discovery board showed up in the supported boards list, it wasn't a choice in the new projects wizard.  So I created a new project with STM32F4 Discovery boards, then pasted the board ID (disco_f429zi) in the platformio.ini file.  Seemed to work?

I used the STM32Cube framework.

example code found here: https://github.com/platformio/platform-ststm32/blob/master/examples/stm32cube-hal-blink/src/main.c

more example code (actually used) and really nice instructions for compiling: https://stm32-base.org/guides/platformio.html

ah-ha!  Platformio installs HAL drivers in (username)/.platformio\packages\framework-stm32cubef4\Drivers\STM32F4xx_HAL_Driver

Under Platformio -> Project Tasks there was a folder specific to the board (disco_f429zi)

  Then -> General, clicked Build.  Compiled with no errors woo!
  
  Tried Upload, got a Error: libusb_open() failed with LIBUSB_ERROR_NOT_FOUND Error: open failed
  
  Had to install proper STM drivers for the board, from here: https://www.st.com/content/st_com/en/products/development-tools/software-development-tools/stm32-software-development-tools/stm32-utilities/stsw-link009.html
  
  Had to verify email and crap, blah, blah.
  
  Unplugged/replugged board and uploading worked!
  
  Changed #defines for my board's LED pin and port (clock enable too!)
  
  It works!

 STM32F429 DISCOVERY kit has LEDs on LD3 (orange) PG13 and LD4 (green) PG14

// Blinky Project for STM32F429DISCO board
// I created a new project in Platformio.
// For whatever reason, even though the STM32F429 Discovery board showed up in the supported boards list, it wasn't a choice in the 
//  new projects wizard.  So I created a new project with STM32F4 Discovery boards, then pasted the board ID (disco_f429zi) in the 
//  platformio.ini file.  Seemed to work?
// I used the STM32Cube framework.
// example code found here: https://github.com/platformio/platform-ststm32/blob/master/examples/stm32cube-hal-blink/src/main.c
// more example code (actually used) and really nice instructions for compiling: https://stm32-base.org/guides/platformio.html
// ah-ha!  Platformio installs HAL drivers in (username)/.platformio\packages\framework-stm32cubef4\Drivers\STM32F4xx_HAL_Driver
// 
// Under Platformio -> Project Tasks there was a folder specific to the board (disco_f429zi)
//  Then -> General, clicked Build.  Compiled with no errors woo!
//  Tried Upload, got a Error: libusb_open() failed with LIBUSB_ERROR_NOT_FOUND Error: open failed
//  Had to install proper STM drivers for the board, from here: https://www.st.com/content/st_com/en/products/development-tools/software-development-tools/stm32-software-development-tools/stm32-utilities/stsw-link009.html
//  Had to verify email and crap, blah, blah.
//  Unplugged/replugged board and uploading worked!
//  Changed #defines for my board's LED pin and port (clock enable too!)
//  It works!

// STM32F429 DISCOVERY kit has LEDs on LD3 (orange) PG13 and LD4 (green) PG14


#include "stm32f4xx_hal.h"

#define LED_PIN                                GPIO_PIN_14
#define LED_GPIO_PORT                          GPIOG
#define LED_GPIO_CLK_ENABLE()                  __HAL_RCC_GPIOG_CLK_ENABLE()

void LED_Init();

int main(void) {
  HAL_Init();
  LED_Init();

  while (1)
  {
    HAL_GPIO_TogglePin(LED_GPIO_PORT, LED_PIN);
    HAL_Delay(1000);
  }
}

void LED_Init() {
  LED_GPIO_CLK_ENABLE();
  GPIO_InitTypeDef GPIO_InitStruct;
  GPIO_InitStruct.Pin = LED_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
  HAL_GPIO_Init(LED_GPIO_PORT, &GPIO_InitStruct);
}

void SysTick_Handler(void) {
  HAL_IncTick();
}
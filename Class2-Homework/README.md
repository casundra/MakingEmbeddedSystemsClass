# STM32L496GDISCOVERY VS RASPBERRY PI PICO...

![image](https://64.media.tumblr.com/260a9af0a13acf413a97eeb4579ea535/tumblr_p4do4yRl5Z1v4u49oo1_1280.gifv)

The STM32L496AG packs a powerful punch with a veritably INSAAAAANE host of special knock-out peripherals making it an audio and graphics powerhouse.  However at an unlucky average of $13 per processor, only the wealthy can afford to hire this special-purpose hitperson to kill their competition.  In fact, they're so in demand, that they're not available for jobs until 2023!  This makes the comparatively small and svelte RPi 2040 our ninja assassin, proving that you don't have to be one of the big brawlers to win a fight.  If you have a wide variety of moves and can flexibly deploy them according to the adversary at hand, and more importantly, if you just show up to the fight, you'll probably win.

|                    |STM32L496GDISCOVERY |RASPBERRY PI PICO |
|--------------------|--------------------|------------------|
|Datasheets | [Board](https://www.st.com/resource/en/user_manual/um2160-discovery-kit-with-stm32l496ag-mcu-stmicroelectronics.pdf) [Processor](https://www.st.com/resource/en/datasheet/stm32l496ag.pdf)| [Board](https://datasheets.raspberrypi.com/pico/pico-datasheet.pdf) [Processor](https://datasheets.raspberrypi.com/rp2040/rp2040-datasheet.pdf)
|Processor | STM32L496AG ARM Cortex-M4, 32-bits, 80 MHz MCU + FPU (floating-point unit)| Dual core ARM Cortex-M0, 32-bits, 133 MHz,  |
|Flash and RAM| 512K or 1MB flash, 320K RAM | No on-board flash, supports up to 16M off-board, 246K RAM |
|Special Peripherals| CAN, USB, SDMMC, audio (SAI), IR LED interface (IRTIM), digital camera interface (DCMI)| 8 Programmable I/O, USB, 16 PWM, QSPI|
|Other Interesting Features| digital sigma-delta filters, graphics accelerator, touch sense controller, LCD controller, true random number generator|integer dividing peripheral, PIO is incredibly flexible (can be used for VGA video) |
|ADC Features | special sigma-delta periph, normal SAR ADC is 12-bit, 5.33 Msps, 24 ch, single & diff, AVdd and AVref pins, 5 internal | SAR ADC is 12-bit, 500Ksps, 4 ch, single-ended only, AVdd pin only, 1 internal |
|App Note | [Vocoder implementation](https://www.st.com/resource/en/application_note/an4229-how-to-implement-a-vocoder-solution-using-stm32-microcontrollers-stmicroelectronics.pdf) (so many good software diagrams!)| [Hardware design with RP2040](https://datasheets.raspberrypi.com/rp2040/hardware-design-with-rp2040.pdf) (tons of practical board layout tips)|
|Package | BGA only noooooooooooo | Friendly 7x7 QFN |
|Board Cost | $75 | $4 |
|Processor Cost |$12-$14 in 100 | $1.00 in 100 + $0.50 for flash|
|Processor Stock | Ha! [Quest](https://www.questcomp.com/part/4/stm32l496agi6p/434132810) maybe, but doubtful in reality | Everywhere! (Digi, Newark, Mouser, RPi Direct) |

## Block Diagrams
### STM32L496GDISCO
Ok, so maybe I cheated on this one, but the [user manual](https://www.st.com/resource/en/user_manual/um2160-discovery-kit-with-stm32l496ag-mcu-stmicroelectronics.pdf) had such a nice hardware diagram that I didn't see the need to reinvent the wheel.  I would have noted the interfaces on the connection lines instead of blocks within the processor, and I would have added some text about amount of flash & RAM onboard the processor inside of it.  Also I would have noted that MFX = multi-functional expander being used to expand an I2C bus, and CTP = touch peripheral.
![image](https://user-images.githubusercontent.com/17057481/161195546-d42627db-ae8f-4083-8417-090988052541.png)

### RASPBERRY PI PICO
Note that the Programmable I/O interface provides great flexibility in being able to implement several comms interfaces simultaneously, see also the pinout diagram.

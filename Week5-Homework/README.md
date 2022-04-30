# Week 5 Homework - Adding a CLI

## Saturday Update
UPDATE: The problem was that the Wokwi sim code used the hardware UART via GPIO pins, while my hardware was using UART via USB.  The read function in consoleIo used a uart_getc function that is specific to UART via GPIO.  I needed to use functions one layer up in the HAL, pico_stdio, which is mapped to either UART or USB depending on which build flag is used.

Code now works, and incorporated the extra commands written in Wokwi.

## Friday Evening Status
OK, so I thought I was going to be able to cheat on this and just use the Pico code as-is, but apparently not?  Serial data transmitting / writing is working fine, but reading is not working.  Not quite sure what to make of it.

I was sort of able to get getchar and putchar to work, but it weirdly blocked my LED blinking.

ConsoleProcess() and uart_getc did not work.

Added extra commands via the Wokwi simulator.  That was cool!

Also, I already did the bonus last week which was creating Chapter 2 diagrams for my final project.  They're in the Week 4 folder.
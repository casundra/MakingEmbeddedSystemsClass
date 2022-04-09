# Class 3 Homework - Blinky, Button, & Debouncing!

I only did the initial blinky in the STM32, the rest I did with the RPi Pico.

I used the PlatformIO IDE.

The only option for frameworks with the RPi Pico is Arduino, so for now I'm stuck with the setup() loop() structure.

I started digging into the RPi SDK and am using their HAL rather than Arduino.

I got a button hooked up and working, though my debounce sucks ass.  Though in my defense, I'm using an arcade button and those things are bouncy as hell and keep bouncing.  I wanted to try to both debounce AND change the LED state in the ISR, but couldn't figure a good way of doing that.  Right now the ISR is setting a buttonPressed variable and then main is checking for elapsed time and state.


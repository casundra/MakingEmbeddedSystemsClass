# The palLED
## Making Embedded Systems Final Project
## Orange Stars Cohort

For All The Details, see the final report.

Hardware and IDE Details:
* RP2040 on an Rpi Pico dev board
* Using VSCode with Platformio
* Platform is Wizio, baremetal framework (using Rpi Pico SDK)
* Debug tool is a Picoprobe

### Minimum Viable Project
I do believe I have achieved this!  I have implemented:
* State Machine - very basic, changes modes on the Matrix
* State Machine - the Consolinator, but this wasn't really mine, I just added to it
* Interrupt - via button to change modes
* Interrupt - via encoders x3 to count counts
* Peripheral 1 - encoders x3, Left Middle Right, (custom GPIO driver)
* Peripheral 2 - rotary potentiometer (ADC)
* Peripheral 3 - LED strips x2, Matrix & Ring (WS2812 x2 via PIO)
* Serial Port Output - yes, over USB
* Cortex-M processor - RP2040, Dual ARM Cortex-M0+
* Algorithmically interesting - maybe light on this at the moment, but the bigger picture project definitely will have an interesting large state machine and algorithms for transforming color spaces

### Report

### Video

### Bonus Points
Pico sort of has firmware updates built in, I could explain this in the report.  Probably will not get to the other 2.
* analysis of power used in the system (expected vs actual)
* implementation of firmware update with a description in the report of how it works
* a description of profiling the system to make it run faster

### Misc Thoughts:
I want to make this code easily extensible so more LED strips can be controlled.  I'm not sure how to do this without the use of C++ classes.  In that case, each LED strip could be a class and initialization could be handled upon declaration.  It seems like with just using structures, there's a lot of manual stuff that needs to be added when a new strip is added.  I've tried to make it so that palled.h is the only file that needs additions, along with intitial declaration in main.c.

Haha oh shit maths.  I really didn't think this whole color wheel aspect through very well, thinking I was going to be able to bracket colors easily with comparisons in order to place them on the color wheel.  Turns out that it's a lot more complicated to go from RGB to color wheel position.  I mean, I should have figured that it was more trig-happy with the whole wheel thing.

Excellent step by step process from this article:
https://www.niwa.nu/2013/05/math-behind-colorspace-conversions-rgb-hsl/

Interesting about color wheels:
https://bahamas10.github.io/ryb/about.html

Will have to figure out how to convert it to a RYB HSL colorspace since that's more inline with color theory complementary/adjacent teachings.  Ah.  Should just be able to bracket which angles correspond to which LEDs differently, no problem.

Also, it would have been smart to use an LED ring that's a multiple of 12 - 3 for displaying triads and even RGB/RYB splits, and 4 for tetrads.

Is it better to call a function 64 times in a row inside a for loop, or to call a function once and have it loop 64 times internally?

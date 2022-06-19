# The palLED
## Making Embedded Systems Final Project
## Orange Stars Cohort

For All The Details, see the final report.

Hardware and IDE Details:
* RP2040 on an Rpi Pico dev board
* Using VSCode with Platformio
* Platform is Wizio, baremetal (using Rpi Pico SDK)
* Debug tool is a Picoprobe

Thoughts:
I want to make this code easily extensible so more LED strips can be controlled.  I'm not sure how to do this without the use of C++ classes.  In that case, each LED strip could be a class and initialization could be handled upon declaration.  It seems like with just using structures, there's a lot of manual stuff that needs to be added when a new strip is added.  I've tried to make it so that palled.h is the only file that needs additions, along with intitial declaration in main.c.

Haha oh shit maths.  I really didn't think this whole color wheel aspect through very well, thinking I was going to be able to bracket colors easily with comparisons in order to place them on the color wheel.  Turns out that it's a lot more complicated to go from RGB to color wheel position.  I mean, I should have figured that it was more trig-happy with the whole wheel thing.

Excellent step by step process from this article:
https://www.niwa.nu/2013/05/math-behind-colorspace-conversions-rgb-hsl/

Will have to figure out how to convert it to a RYB HSL colorspace since that's more inline with color theory complementary/adjacent teachings.

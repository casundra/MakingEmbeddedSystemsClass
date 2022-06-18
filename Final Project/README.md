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



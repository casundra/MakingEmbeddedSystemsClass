// Modified by Carrie Sundra 2022
// MIT License
// Based on:

/*************************************************
** Command Line Interface
** This is from https://github.com/eleciawhite/reusable
** (MIT license)
**
** To use it in the simulator, press run 
**    It should print `Welcome to the Consolinator, your gateway to testing code and hardware`
** Type 'help' in the white box at the bottom and hit return.
** It lists the commands it supports.
**
** There are several files here:
** Console.c is a command parser. 
**    Call the init function during init and
**    then call the process function on every pass through a loop.
** You probably don't need to modify this file much.
**
** The interface is in consoleIo.c which currently
** uses the RPi Pico interface. You will need to modify this
** for your own hardware, connecting it to a UART in your embedded system.
**
** The command table and commands are implemented in consoleCommands.c.
** This is where you add commands, probably by copying one that is 
** already there. You need to modify mConsoleCommandTable 
** to add the command.
**************************************************/

// Console is the generic interface to the command line. 
// These functions should not need signficant modification, only 
// to be called from the normal loop. Note that adding commands should 
// be done in console commands. 

// can likely be included in palled.h but kind of nice to always know where
// the version string is and only modify one obvious file when you modify the version.

#ifndef VERSION_H
#define VERSION_H

#define VERSION_STRING "palLED 1.1"

#endif // VERSION_H
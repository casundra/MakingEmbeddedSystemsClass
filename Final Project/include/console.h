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
#ifndef CONSOLE_H
#define CONSOLE_H

#include <stdint.h>

// User configuration
#define CONSOLE_PROMPT			("> ")
#define PARAMETER_SEPARATER		(' ')
#define STR_ENDLINE 			"\r\n"

// The C library itoa is sometimes a complicated function and the library costs aren't worth it
// so this is implements the parts of the function needed for console.
#define CONSOLE_USE_BUILTIN_ITOA	1


// Salled from higher up areas of the code (main)
void ConsoleInit(void);
void ConsoleProcess(void); // call this in a loop

// called from lower down areas of the code (consoleCommands)
typedef enum { 
	COMMAND_SUCCESS = 0u, 
	COMMAND_PARAMETER_ERROR = 0x10u, 
	COMMAND_PARAMETER_END   = 0x11u,
	COMMAND_ERROR =0xFFu 
} eCommandResult_T;

// The in and output of the int16 parameter use C standard library functions
// atoi and itoa. These are nice functions, usually a lot smaller than scanf and printf
// but they can be memory hogs in their flexibility. 
// The HexUint16 functions implement the parsing themselves, eschewing atoi and itoa.
eCommandResult_T ConsoleReceiveParamInt16(const char * buffer, const uint8_t parameterNumber, int16_t* parameterInt16);
eCommandResult_T ConsoleReceiveParamUint8(const char * buffer, const uint8_t parameterNumber, uint8_t* parameterUint8);
eCommandResult_T ConsoleSendParamUint8(uint8_t parameterInt);
eCommandResult_T ConsoleSendParamUint16(uint16_t parameterInt);
eCommandResult_T ConsoleSendParamInt16(int16_t parameterInt);
eCommandResult_T ConsoleSendParamInt32(int32_t parameterInt);
eCommandResult_T ConsoleReceiveParamHexUint16(const char * buffer, const uint8_t parameterNumber, uint16_t* parameterUint16);
eCommandResult_T ConsoleSendParamHexUint16(uint16_t parameterUint16);
eCommandResult_T ConsoleSendParamHexUint8(uint8_t parameterUint8);
eCommandResult_T ConsoleSendString(const char *buffer); // must be null terminated
eCommandResult_T ConsoleSendLine(const char *buffer); // must be null terminated

#endif // CONSOLE_H
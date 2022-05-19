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
*************************************************/
// ConsoleCommands.c
// This is where you add commands:
//		1. Add a protoype
//			static eCommandResult_T ConsoleCommandVer(const char buffer[]);
//		2. Add the command to mConsoleCommandTable
//		    {"ver", &ConsoleCommandVer, HELP("Get the version string")},
//		3. Implement the function, using ConsoleReceiveParam<Type> to get the parameters from the buffer.

#include <string.h>
#include "consoleCommands.h"
#include "console.h"
#include "consoleIo.h"
#include "version.h"
#include "data.h"

#define IGNORE_UNUSED_VARIABLE(x)     if ( &x == &x ) {}

static eCommandResult_T ConsoleCommandComment(const char buffer[]);
static eCommandResult_T ConsoleCommandVer(const char buffer[]);
static eCommandResult_T ConsoleCommandHelp(const char buffer[]);
static eCommandResult_T ConsoleCommandParamExampleInt16(const char buffer[]);
static eCommandResult_T ConsoleCommandParamExampleUint8(const char buffer []);
static eCommandResult_T ConsoleCommandParamExampleHexUint16(const char buffer[]);
static eCommandResult_T ConsoleCommandData(const char buffer[]);

static const sConsoleCommandTable_T mConsoleCommandTable[] =
{
    {";", &ConsoleCommandComment, HELP("Comment! You do need a space after the semicolon. ")},
    {"help", &ConsoleCommandHelp, HELP("Lists the commands available")},
    {"ver", &ConsoleCommandVer, HELP("Get the version string")},
    {"int", &ConsoleCommandParamExampleInt16, HELP("How to get a signed int16 from params list: int -321")},
		{"uint8", &ConsoleCommandParamExampleUint8, HELP("How to get an unsigned uint8 from params list: uint8 123")},
    {"u16h", &ConsoleCommandParamExampleHexUint16, HELP("How to get a hex u16 from the params list: u16h aB12")},
		{"data", &ConsoleCommandData, HELP("Dumps some RGB data")},

	CONSOLE_COMMAND_TABLE_END // must be LAST
};

static eCommandResult_T ConsoleCommandComment(const char buffer[])
{
	// do nothing
	IGNORE_UNUSED_VARIABLE(buffer);
	return COMMAND_SUCCESS;
}

static eCommandResult_T ConsoleCommandHelp(const char buffer[])
{
	uint32_t i;
	uint32_t tableLength;
	eCommandResult_T result = COMMAND_SUCCESS;

    IGNORE_UNUSED_VARIABLE(buffer);

	tableLength = sizeof(mConsoleCommandTable) / sizeof(mConsoleCommandTable[0]);
	for ( i = 0u ; i < tableLength - 1u ; i++ )
	{
		ConsoleIoSendString(mConsoleCommandTable[i].name);
#if CONSOLE_COMMAND_MAX_HELP_LENGTH > 0
		ConsoleIoSendString(" : ");
		ConsoleIoSendString(mConsoleCommandTable[i].help);
#endif // CONSOLE_COMMAND_MAX_HELP_LENGTH > 0
		ConsoleIoSendString(STR_ENDLINE);
	}
	return result;
}

static eCommandResult_T ConsoleCommandParamExampleInt16(const char buffer[])
{
	int16_t parameterInt;
	eCommandResult_T result;
	result = ConsoleReceiveParamInt16(buffer, 1, &parameterInt);
	if ( COMMAND_SUCCESS == result )
	{
		ConsoleIoSendString("Parameter is ");
		ConsoleSendParamInt16(parameterInt);
		ConsoleIoSendString(" (0x");
		ConsoleSendParamHexUint16((uint16_t)parameterInt);
		ConsoleIoSendString(")");
		ConsoleIoSendString(STR_ENDLINE);
	}
	return result;
}

static eCommandResult_T ConsoleCommandParamExampleUint8(const char buffer[])
{
	uint8_t parameterUint;
	eCommandResult_T result;
	result = ConsoleReceiveParamUint8(buffer, 1, &parameterUint);
	if ( COMMAND_SUCCESS == result )
	{
		ConsoleIoSendString("Parameter is ");
		ConsoleSendParamUint8(parameterUint);
		ConsoleIoSendString(" (0x");
		ConsoleSendParamHexUint8((uint8_t) parameterUint);
		ConsoleIoSendString(")");
		ConsoleIoSendString(STR_ENDLINE);
	}
	return result;
}

static eCommandResult_T ConsoleCommandParamExampleHexUint16(const char buffer[])
{
	uint16_t parameterUint16;
	eCommandResult_T result;
	result = ConsoleReceiveParamHexUint16(buffer, 1, &parameterUint16);
	if ( COMMAND_SUCCESS == result )
	{
		ConsoleIoSendString("Parameter is 0x");
		ConsoleSendParamHexUint16(parameterUint16);
		ConsoleIoSendString(STR_ENDLINE);
	}
	return result;
}

static eCommandResult_T ConsoleCommandVer(const char buffer[])
{
	eCommandResult_T result = COMMAND_SUCCESS;

    IGNORE_UNUSED_VARIABLE(buffer);

	ConsoleIoSendString(VERSION_STRING);
	ConsoleIoSendString(STR_ENDLINE);
	return result;
}

static eCommandResult_T ConsoleCommandData(const char buffer[])
{
	eCommandResult_T result = COMMAND_SUCCESS;

	uint8_t dataRowLength = sizeof (rgbHeader) / sizeof (rgbHeader[0]);
	for (uint8_t i = 0; i < dataRowLength; i++) {
		ConsoleIoSendString(rgbHeader[i]);
		ConsoleIoSendString("\t");
	}
	ConsoleIoSendString(STR_ENDLINE);	

	uint8_t dataTableLength = sizeof (rgb) / sizeof (rgb[0]);
	for (uint8_t i = 0; i < dataTableLength; i++) {
		for (uint8_t j = 0; j < dataRowLength; j++){
			ConsoleSendParamUint8(rgb[i][j]);
			ConsoleIoSendString("\t");
		}
		ConsoleIoSendString(STR_ENDLINE);	
	}
	ConsoleIoSendString("...and that's all, folks!");
	ConsoleIoSendString(STR_ENDLINE);	

	return result;
}

const sConsoleCommandTable_T* ConsoleCommandsGetTable(void)
{
	return (mConsoleCommandTable);
}



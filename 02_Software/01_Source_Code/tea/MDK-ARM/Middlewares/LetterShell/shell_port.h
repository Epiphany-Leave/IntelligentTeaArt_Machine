#ifndef _SHELL_PORT_H
#define _SHELL_PORT_H

#include "shell.h"
#include "stdint.h"

extern Shell shell;
extern uint8_t shellByteBuff;
extern char shellBuffer[512];

void LetterShell_Init(void);

void ShellLog(Shell* shell, const char* fmt, ...);

#endif //_SHELL_PORT_H

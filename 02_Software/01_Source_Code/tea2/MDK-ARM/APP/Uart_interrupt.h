#ifndef _UART_INTERRUPT_H_
#define _UART_INTERRUPT_H_

#include "main.h"
#include "commond.h"

void WiFi_Sendtest(char *cmd);
void u2_printf(char *fmt, ...);
void u2_TxData(uint8_t *data);

#endif

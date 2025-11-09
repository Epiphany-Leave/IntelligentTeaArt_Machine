#ifndef __UART_H
#define __UART_H

#include "stdint.h"		// 变量类型定义

/* 缓冲区长度 */
#define UART_RX_MAX 1024

/* 存放缓冲区信息结构体 */
typedef struct{
	uint16_t in;				// 数据存放时要放置的位置
	uint16_t out;				// 数据输出时的开始的位置
	uint8_t  buf[UART_RX_MAX];	// 存放数据的缓存
}UART_S;

//extern UART_S uart;

void uart_init(void);
void uart_it_cb(void);
void debug_read(void);


#endif

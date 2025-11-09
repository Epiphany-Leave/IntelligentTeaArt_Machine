#ifndef __COMMOND_H__
#define __COMMOND_H__

#include "main.h"
#include "adc.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

#include "Uart_interrupt.h"

#include "lcd_bsp.h"
#include "pwm_bsp.h"

#include "beep_driver.h"
#include "key_driver.h"
#include "adc_driver.h"
#include "pwm_driver.h"
#include "lcd_driver.h"
#include "stp_driver.h"
#include "motor_driver.h"
#include "vofa.h"

#include "app.h"
#include "meun.h"
//#include "uart_ring_buffer.h"

#include "Tasklist.h"
#include "timepiece.h"

#include "wifi.h"
#include "mqtt.h"

#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#define CCMRAM  __attribute__((section("ccmram")))

#define USART2_RX_ENABLE     1
#define USART2_TXBUFF_SIZE   1024
#define USART2_RXBUFF_SIZE   1024

#define  PRODUCTKEY           ""                                        		//产品ID
#define  DEVICENAME           ""                                               	//设备名  
#define  DEVICESECRE          ""                   		//设备秘钥   
#define  P_TOPIC_NAME         ""    	//需要发布的主题，即设备发布到云端
#define  S_TOPIC_NAME         ""   	//需要订阅的主题，即云端发布到设备  

#define SSID   "YSX"              //路由器SSID名称   2.4G   
#define PASS   "Ysx200423"                 //路由器密码

#if USART2_RX_ENABLE
extern volatile uint8_t Usart2_RxCompleted;
extern uint16_t Usart2_RxCounter;
extern char rx_byte[1];
extern char Usart2_RxBuff[USART2_RXBUFF_SIZE];
#endif
extern volatile uint8_t DMA_flag;
//extern UART_S uart;


#endif /* __COMMOND_H__ */


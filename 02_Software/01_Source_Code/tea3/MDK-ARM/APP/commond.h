#ifndef __COMMOND_H__
#define __COMMOND_H__

#include "main.h"
#include "adc.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

#include "Uart_interrupt.h"

//#include "lcd_bsp.h"
#include "pwm_bsp.h"

#include "beep_driver.h"
#include "key_driver.h"
#include "adc_driver.h"
#include "pwm_driver.h"
//#include "lcd_driver.h"
#include "stp_driver.h"
#include "motor_driver.h"
#include "vofa.h"

#include "app.h"

#include "meun.h"
#include "HMI.h"

#include "Tasklist.h"
#include "timepiece.h"

#include "wifi.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <stdbool.h>
#include <math.h>

#define CCMRAM  __attribute__((section("ccmram")))


#define FRAMELENGTH 6

#define USART2_RX_ENABLE     1
#define USART2_TXBUFF_SIZE   1024
#define USART2_RXBUFF_SIZE   1024

#define WIRELESS_SEND_TIME 	3000	//上报数据时间间隔（单位：毫秒）

/* 
*	舵机1->底盘
*	舵机2->摇臂
*	舵机3->茶盖
*	舵机4->茶壶
*/
#define HOLDER_1_M	100		// 杯
#define HOLDER_1_T	175		// 茶
#define HOLDER_1_W	10		// 水

#define HOLDER_2_U	60
#define HOLDER_2_D	85
#define SHAKER_1_U	60
#define SHAKER_1_D	65

#define HOLDER_3_U	0
#define HOLDER_3_D	170

#define HOLDER_4_P	180
#define HOLDER_4_N	10

#define HOLDER_5_P	60
#define HOLDER_5_N	20


extern uint32_t pulse_buffer;

extern char rx1_byte[1];
extern uint8_t rx2_byte[1];

extern uint8_t wireless_send_flag;

extern unsigned char preheat_flag;
extern unsigned char clean_flag;
extern unsigned char maketea_flag;
extern unsigned char addtea_flag;

extern uint32_t clean_time;
extern uint32_t preheat_time;
extern uint32_t maketea_time;
extern uint32_t addtea_time;

#endif /* __COMMOND_H__ */


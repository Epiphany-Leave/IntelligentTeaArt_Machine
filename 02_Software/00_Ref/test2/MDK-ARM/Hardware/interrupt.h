#ifndef __INTERUPT_H
#define __INTERUPT_H

#include "stm32g4xx_hal.h"
#include "stdbool.h" 
#include "main.h"

#define SHORT_PRESS_TIME 40  // 400ms

typedef enum
{
	SW1,
	SW2,
	SW3,
	SW_SUM,
}KEY_NUM_TYPEDEF;

// 按键状态机
struct keys
{
	unsigned char judge_sta;
	bool key_sta;
	bool l_flag;
	bool s_flag;
	uint16_t key_time;
};

// 中断函数声明
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);

#endif // __INTERUPT_H

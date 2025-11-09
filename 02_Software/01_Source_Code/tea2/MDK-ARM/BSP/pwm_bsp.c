#include "pwm_bsp.h"
#include "tim.h"


/**
***********************************************************************
* @brief:      tim_bsp_init(void)
* @param:		   void
* @retval:     void
* @details:    定时器硬件使能
***********************************************************************
**/
void tim_bsp_init(void)
{
	
}

void pwm_start(void)
{
//	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);   
//	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);   
//	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_3);    
//	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_4);
//	
//	HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_1); 
//	HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_2);
//	HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_3);
	
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);	//MOS
	
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);	//水泵
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);
	
	HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_1);   //舵机
	HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_2);

	HAL_TIM_PWM_Start(&htim15, TIM_CHANNEL_1);//左	//电机
	HAL_TIM_PWM_Start(&htim15, TIM_CHANNEL_2);//右
	
	HAL_TIM_PWM_Start(&htim16, TIM_CHANNEL_1);	//蜂鸣器
}

void Water1_Speed(uint8_t speed)
{
	TIM3->CCR1 = speed * 10;
}

void Servo1_Angle(float Angle)
{
	TIM4->CCR1 = (Angle / 180 * 2000 + 500);
}
void Servo2_Angle(float Angle)
{
	TIM4->CCR2 = (Angle / 180 * 2000 + 500);
}

void tim4_pwm_ccr_set(Channel ch, uint16_t pwm_count)
{
	switch(ch)
	{
		case ch1:
			__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, pwm_count);
		break;
		
		case ch2:
			__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_2, pwm_count);
		break;
		
		case ch3:
			__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_3, pwm_count);
		break;
		
		case ch4:
			__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_4, pwm_count);
		break;
		
		default: break;
	}
}


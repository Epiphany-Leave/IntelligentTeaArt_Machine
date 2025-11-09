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


// 定义DMA传输缓冲区
uint32_t pulse_buffer = 0;  // 用于控制脉冲数量
void pwm_start(void)
{
//	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);   

//	HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_3);
	
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);	//DLP1
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);	//DLP2
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_3);	//DLP3
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_4);	//DLP4

	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);	//DLP5
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);	//DLP6
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3);	//DLP7
//	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_4);	//DLP8
	HAL_TIM_IC_Start_IT(&htim3, TIM_CHANNEL_4); //流量计
	
	HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_1);	//水泵1
	HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_2);	//水泵2
	
//	HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_1);	//步进电机1

	HAL_TIM_PWM_Start(&htim15, TIM_CHANNEL_1);	//PWMA
	HAL_TIM_PWM_Start(&htim15, TIM_CHANNEL_2);	//PWMB
	
	HAL_TIM_PWM_Start(&htim16, TIM_CHANNEL_1);	//蜂鸣器
	
    // 配置DMA传输
//    HAL_DMA_Start_IT(htim8.hdma[TIM_DMA_ID_UPDATE], (uint32_t)&pulse_buffer, (uint32_t)&htim8.Instance->CCR1, 1);
//    __HAL_TIM_ENABLE_DMA(&htim8, TIM_DMA_UPDATE);	
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


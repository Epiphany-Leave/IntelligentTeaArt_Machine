#include "motor_driver.h"
#include "pwm_bsp.h"

#include "tim.h"
#include <math.h>

int16_t dutyfactor[3] = {0};	//电机
uint16_t dutywater[3] = {0};	//水泵

/**
  * @brief  设置电机1速度
  * @param  v: 速度（占空比）
  * @retval 无
  */
void Set_motor1_speed(int16_t v)
{
    dutyfactor[1] = v;
	if(dutyfactor[1] > 0)
	{
		HAL_GPIO_WritePin(AIN1_GPIO_Port, AIN1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(AIN2_GPIO_Port, AIN2_Pin, GPIO_PIN_RESET);
		TIM15->CCR1 = (dutyfactor[1]); 
	}
	else if(dutyfactor[1] < 0)
	{
		HAL_GPIO_WritePin(AIN1_GPIO_Port, AIN1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(AIN2_GPIO_Port, AIN2_Pin, GPIO_PIN_SET);
		TIM15->CCR1 = (-(dutyfactor[1])); 
	}
	else if(dutyfactor[1] == 0)
	{
		HAL_GPIO_WritePin(AIN1_GPIO_Port, AIN1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(AIN2_GPIO_Port, AIN2_Pin, GPIO_PIN_RESET);
		TIM15->CCR1 = (dutyfactor[1]); 		
	}
}
/**
  * @brief  设置电机2速度
  * @param  v: 速度（占空比）
  * @retval 无
  */
void Set_motor2_speed(int16_t v)
{
    dutyfactor[1] = v;
	if(dutyfactor[1] > 0)
	{
		HAL_GPIO_WritePin(BIN1_GPIO_Port, BIN1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(BIN2_GPIO_Port, BIN2_Pin, GPIO_PIN_RESET);
		TIM15->CCR2 = (dutyfactor[1]); 
	}
	else if(dutyfactor[1] < 0)
	{
		HAL_GPIO_WritePin(BIN1_GPIO_Port, BIN1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(BIN2_GPIO_Port, BIN2_Pin, GPIO_PIN_SET);
		TIM15->CCR2 = (-(dutyfactor[1])); 
	}
	else if(dutyfactor[1] == 0)
	{
		HAL_GPIO_WritePin(BIN1_GPIO_Port, BIN1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(BIN2_GPIO_Port, BIN2_Pin, GPIO_PIN_RESET);
		TIM15->CCR2 = (dutyfactor[1]); 		
	}
}

void Motor_Control(uint8_t motor_id, uint16_t v)
{
	switch(motor_id)
	{
		case Motor_1:
			Set_motor1_speed(v);
		break;
		
		case Motor_2:
			Set_motor2_speed(v);
		break;
	}	
}


/**
  * @brief  设置水泵1速度
  * @param  v: 速度（占空比）
  * @retval 无
  */
void Set_water1_speed(uint8_t file)
{
	dutywater[1] = 200 * file;
	TIM4->CCR1 = (dutywater[1]);
}
/**
  * @brief  设置水泵2速度
  * @param  v: 速度（占空比）
  * @retval 无
  */
void Set_water2_speed(uint8_t file)
{
	dutywater[2] = 200 * file;
	TIM4->CCR2 = (dutywater[2]);
}
/**
  * @brief  设置水泵
  * @param  file：档次
  * @retval 无
  */
void WaterPump_Control(uint8_t pump_id, uint8_t file)
{
	switch(pump_id)
	{
		case PUMP_1:
			Set_water1_speed(file);
		break;
		
		case PUMP_2:
			Set_water2_speed(file);
		break;
	}
}



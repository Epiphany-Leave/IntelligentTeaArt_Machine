#include "motor_driver.h"
#include "pwm_bsp.h"

#include "tim.h"
#include <math.h>

uint16_t dutyfactor[3] = {0};

/**
  * @brief  设置电机1速度
  * @param  v: 速度（占空比）
  * @retval 无
  */
void Set_motor1_speed(uint16_t v)
{
  dutyfactor[1] = v;
  TIM15->CCR1 = (dutyfactor[1]);  
}

/**
  * @brief  设置电机1速度
  * @param  v: 速度（占空比）
  * @retval 无
  */
void Set_motor2_speed(uint16_t v)
{
  dutyfactor[2] = v;
  TIM15->CCR2 = (dutyfactor[2]);  
}


#include "pwm_driver.h"
#include "pwm_bsp.h"
#include "tim.h"

#include <math.h>

/**
***********************************************************************
* @brief:      adc_driver_init(void)
* @param:		   void
* @retval:     void
* @details:    
***********************************************************************
**/
void pwm_driver_init(void)
{
//	pwm_bsp_init();
	pwm_start();
}


// 舵机参数配置表（可扩展）
static const ServoConfig servo_config[] = {
    [SERVO1] = {SERVO_CH1, 500, 2500},  // SERVO1: 500us-2500us对应0-180度
    [SERVO2] = {SERVO_CH2, 500, 2500}   // SERVO2: 同上
};

/**
  * @brief  设置PWM占空比
  * @param  htim: 定时器句柄
  * @param  channel: PWM通道
  * @param  pulse_width: 脉冲宽度（单位：us）
  */
void PWM_SetPulseUs(TIM_HandleTypeDef *htim, ServoChannel channel, uint16_t pulse_width) {
    // 计算ARR对应的周期值（假设ARR=19999, PSC=83, 时钟84MHz时，PWM周期=20ms）
    uint32_t period_us = (htim->Instance->ARR + 1) * (htim->Instance->PSC + 1) / (SystemCoreClock / 1000000);
    __HAL_TIM_SET_COMPARE(htim, channel, (pulse_width * (htim->Instance->ARR + 1)) / period_us);
}

/**
  * @brief  设置舵机角度
  * @param  servo: 舵机编号（SERVO1/SERVO2）
  * @param  angle: 目标角度（0-180度）
  * @retval 成功返回0，失败返回-1
  */
int8_t Servo_SetAngle(SERVO servo, float angle) {
    // 参数合法性检查
    if (servo >= SERVO_SUM || angle < 0 || angle > 180) {
        return -1;  // 错误码
    }

    // 获取舵机配置参数
    const ServoConfig *config = &servo_config[servo];
    
    // 计算脉冲宽度（线性映射）
    float pulse_width = config->min_pulse + (angle / 180.0f) * (config->max_pulse - config->min_pulse);
    
    // 设置PWM
    PWM_SetPulseUs(&htim4, config->channel, (uint16_t)roundf(pulse_width));

    // 调试信息（条件编译控制）
#ifdef DEBUG_SERVO
    printf("[Servo%d] Angle: %.1f° -> Pulse: %uus\r\n", servo+1, angle, (uint16_t)pulse_width);
#endif

    return 0;
}



//void GPIO_OutputPulses(uint32_t pulse_count, uint32_t pulse_period_us)
//{
//    for (uint32_t i = 0; i < pulse_count; i++)
//    {
//        HAL_GPIO_WritePin(M_STP_GPIO_Port, M_STP_Pin, GPIO_PIN_SET); // 高电平
//        HAL_Delay(pulse_period_us / 2 / 1000);              // 延时，高电平持续时间

//        HAL_GPIO_WritePin(M_STP_GPIO_Port, M_STP_Pin, GPIO_PIN_RESET); // 低电平
//        HAL_Delay(pulse_period_us / 2 / 1000);                // 延时，低电平持续时间
//    }
//}


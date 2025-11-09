#include "motor.h"

void Motor_Init(void)// pwm波发送测试函数
{
    if (HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1) != HAL_OK)//开启TIM1的CH1通道产生PWM
    {
        Error_Handler();
    }
    if (HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_1) != HAL_OK)//开启TIM1的CH1N通道产生PWM
    {
        Error_Handler();
    }
}

void SetMotorSpeed(uint8_t dutyCycle)
{
    // 确保占空比在0到100之间
    if (dutyCycle > 100) {
        dutyCycle = 100;
    }

    // 计算CCR值
//    uint32_t ccrValue = (uint32_t)(((uint64_t)dutyCycle * (TIM1->ARR + 1)) / 100);
    uint32_t ccrValue = (uint32_t)(((uint64_t)dutyCycle * htim1.Init.Period) / 100);

    // 设置TIM1的CCR1值来改变占空比
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, ccrValue);
}

// 电机方向控制函数
void Motor_Direction(MOTOR_DIRECTION direction, uint8_t speed)
{
    switch (direction)
    {
        case STOP:
        {
            // 停止电机，设置占空比为0
            SetMotorSpeed(0);   // PA8 (CH1)
        } break;

        case FORWARD:
        {
            // 设置正转，占空比设置为输入速度
            SetMotorSpeed(speed);   // PA8 (CH1)
        } break;

        case REVERSE:
        {
            // 设置反转，依然通过设置互补PWM来实现反向旋转
            SetMotorSpeed(speed);  // PA8 (CH1)
            
            // 如果反转需要改变极性或者其他配置，可以在此调整
        } break;
    }
}



void Motor_test(void)
{
	// 测试电机正转，速度 50%
    Motor_Direction(FORWARD, 50);
    HAL_Delay(2000);  // 保持正转2秒

    // 测试电机反转，速度 50%
    Motor_Direction(REVERSE, 50);
    HAL_Delay(2000);  // 保持反转2秒

    // 停止电机
    Motor_Direction(STOP, 0);
    HAL_Delay(2000);  // 停止2秒

    // 测试电机正转，速度 80%
    Motor_Direction(FORWARD, 80);
    HAL_Delay(2000);  // 保持正转2秒

    // 测试电机反转，速度 80%
    Motor_Direction(REVERSE, 80);
    HAL_Delay(2000);  // 保持反转2秒

    // 停止电机
    Motor_Direction(STOP, 0);
    HAL_Delay(2000);  // 停止2秒
}



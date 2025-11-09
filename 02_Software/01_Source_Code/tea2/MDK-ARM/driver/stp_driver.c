#include "stp_driver.h"
#include "pwm_bsp.h"

#include "tim.h"

/**
***********************************************************************
* @brief:      Stp_Enable(void)
* @param:	   void
* @retval:     void
* @details:    
***********************************************************************
**/
void StepperMotor_Init(STP_TYPEDEFT* motor)
{
    // 状态初始化
    motor->target_steps = 0;
    motor->current_steps = 0;
    motor->is_moving = 0;

    // 初始化引脚状态
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, GPIO_PIN_RESET);	
};

uint8_t StepperMotor_IsMoving(STP_TYPEDEFT* motor)
{
    return motor->is_moving;
}

void StepperMotor_Stop(STP_TYPEDEFT* motor)
{
    // 停止定时器
    HAL_TIM_Base_Stop_IT(&htim7);
    
    // 失能电机
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_RESET);
    
    // 更新状态
    motor->is_moving = 0;
    motor->current_steps = motor->target_steps;
}

void StepperMotor_SetAngle(STP_TYPEDEFT* motor, float degrees)
{
    // 停止当前运动
    StepperMotor_Stop(motor);

    // 计算目标脉冲数
    int32_t target = (int32_t)((degrees / 360.0f) * (float)STEPS_PER_REV);

    // 设置方向
    if(degrees >= 0.0f) 
	{
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET); // 正转
		motor->is_direction = 1;
    } 
	else 
	{
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET); // 反转
		motor->is_direction = 0;
    }

    // 更新目标位置
    motor->target_steps = target;

    // 使能电机
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_SET);

    // 启动定时器
    motor->is_moving = 1;
    HAL_TIM_Base_Start_IT(&htim7);	
}


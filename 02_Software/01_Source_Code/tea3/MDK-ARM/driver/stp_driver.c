#include "stp_driver.h"
#include "tim.h"

STP_TYPEDEFT g_stepper1;
STP_TYPEDEFT g_stepper2;

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
    HAL_GPIO_WritePin(M_DIR1_GPIO_Port, M_DIR1_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(M_EN1_GPIO_Port, M_EN1_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(M_STP1_GPIO_Port, M_STP1_Pin, GPIO_PIN_RESET);	
	
	HAL_GPIO_WritePin(M_DIR2_GPIO_Port, M_DIR2_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(M_EN2_GPIO_Port, M_EN2_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(M_STP2_GPIO_Port, M_STP2_Pin, GPIO_PIN_RESET);
};

uint8_t StepperMotor_IsMoving(STP_TYPEDEFT* motor)
{
    return motor->is_moving;
}

void StepperMotor_SetSpeed(STP_TYPEDEFT* motor, uint16_t rpm) 
{
    if(motor == &g_stepper1)
    {
        __HAL_TIM_SET_AUTORELOAD(&htim7, (uint32_t)(10000000 / rpm));
    }
    else if (motor == &g_stepper2)
    {
        __HAL_TIM_SET_AUTORELOAD(&htim6, (uint32_t)(10000000 / rpm));
    }   
}

void StepperMotor_Stop(STP_TYPEDEFT* motor)
{
    // 停止定时器
    HAL_TIM_Base_Stop_IT(&htim7);
	HAL_TIM_Base_Stop_IT(&htim6);
//	HAL_TIM_PWM_Stop_DMA(&htim8, TIM_CHANNEL_1);
    
    // 失能电机
    HAL_GPIO_WritePin(M_EN1_GPIO_Port, M_EN1_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(M_EN2_GPIO_Port, M_EN2_Pin, GPIO_PIN_RESET);
    
    // 更新状态
    motor->is_moving = 0;
    motor->current_steps = motor->target_steps;
}

void StepperMotor_SetAngle(STP_TYPEDEFT* motor, float degrees) 
{
    // 停止当前运动
    StepperMotor_Stop(motor);

    // 计算目标脉冲数
    int32_t target = (int32_t)((degrees * (float)STEPS_PER_REV) / 360.0f + 0.5f);  //添加四舍五入
    motor->target_steps = target;

    // 判断是否需要移动
    if (motor->current_steps == target) 
    {
        return; // 当前位置即目标，直接返回
    }

    // 动态计算方向 --------------------------------------------------
    int32_t delta = target - motor->current_steps;
    if (delta > 0) 
    {
        // 目标在正方向
        if (motor == &g_stepper1)
            HAL_GPIO_WritePin(M_DIR1_GPIO_Port, M_DIR1_Pin, GPIO_PIN_SET);
        else if (motor == &g_stepper2)
            HAL_GPIO_WritePin(M_DIR2_GPIO_Port, M_DIR2_Pin, GPIO_PIN_SET);
        motor->is_direction = 1;
    } 
    else 
    {
        // 目标在负方向
        if (motor == &g_stepper1)
            HAL_GPIO_WritePin(M_DIR1_GPIO_Port, M_DIR1_Pin, GPIO_PIN_RESET);
        else if (motor == &g_stepper2)
            HAL_GPIO_WritePin(M_DIR2_GPIO_Port, M_DIR2_Pin, GPIO_PIN_RESET);
        motor->is_direction = 0;
    }

    // 使能电机
    if (motor == &g_stepper1)
        HAL_GPIO_WritePin(M_EN1_GPIO_Port, M_EN1_Pin, GPIO_PIN_SET);
    else if (motor == &g_stepper2)
        HAL_GPIO_WritePin(M_EN2_GPIO_Port, M_EN2_Pin, GPIO_PIN_SET);

    motor->total_steps = abs(delta);
    motor->accel_steps = motor->total_steps * 0.15;  // 加速段占30%
    motor->decel_steps = motor->total_steps * 0.15;  // 减速段占30%
    motor->current_speed = INITIAL_SPEED1;
    motor->accel_phase = 0;

    // 启动定时器
    motor->is_moving = 1;
    if (motor == &g_stepper1)
        HAL_TIM_Base_Start_IT(&htim7);
    else if (motor == &g_stepper2)
        HAL_TIM_Base_Start_IT(&htim6);
}



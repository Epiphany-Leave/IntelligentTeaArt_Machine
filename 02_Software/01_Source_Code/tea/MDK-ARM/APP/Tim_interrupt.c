#include "Tim_interrupt.h"
#include "Tasklist.h"
#include "commond.h"


CCMRAM void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
//	extern uint8_t uart1_receiveData_parse(void);
    /* Period: 3000ms */
	
    /* Period: 1ms */
    if(htim->Instance==TIM17)	//RTOS时钟
    {		
		TaskDicision();
    }
    
	if(htim->Instance==TIM7)	//步进电机1
	{
        STP_TYPEDEFT* m = &g_stepper1;
        if (m->is_moving) 
        {
            m->steps_remaining = abs(m->target_steps - m->current_steps);
            
            // 动态调整加速度
            if (m->accel_phase == 0 && m->current_speed < MAX_SPEED1) 
            {
                m->current_speed += (m->current_speed < (MAX_SPEED1/2)) ? 5 : 2;
            } 
            else if (m->accel_phase == 2 && m->current_speed > INITIAL_SPEED1) 
            {
                m->current_speed -= (m->current_speed > (INITIAL_SPEED1/2)) ? 5 : 2;
            }

            // 限制速度范围并更新ARR
            uint32_t clamped_speed = (m->current_speed < INITIAL_SPEED1) ? INITIAL_SPEED1 : ((m->current_speed > MAX_SPEED1) ? MAX_SPEED1 : m->current_speed);
            __HAL_TIM_SET_AUTORELOAD(htim, (TIMER_CLK / clamped_speed));

            // 生成脉冲并更新位置
            HAL_GPIO_TogglePin(M_STP1_GPIO_Port, M_STP1_Pin);
            m->current_steps += (m->is_direction) ? 1 : -1;

            // 状态切换逻辑
            if (m->steps_remaining <= m->decel_steps) 
            {
                m->accel_phase = 2; // 进入减速
            } else if (m->current_speed >= MAX_SPEED1) 
            {
                m->accel_phase = 1; // 进入匀速
            }

            if (m->steps_remaining == 0) StepperMotor_Stop(m);
        }
	}
	
	if(htim->Instance==TIM6)	//步进电机2
	{
        STP_TYPEDEFT* m = &g_stepper2;
        if (m->is_moving) 
        {
            m->steps_remaining = abs(m->target_steps - m->current_steps);
            
            // 动态调整加速度
            if (m->accel_phase == 0 && m->current_speed < MAX_SPEED2) 
            {
                m->current_speed += (m->current_speed < (MAX_SPEED2/2)) ? 5 : 2;
            } 
            else if (m->accel_phase == 2 && m->current_speed > INITIAL_SPEED2) 
            {
                m->current_speed -= (m->current_speed > (INITIAL_SPEED2/2)) ? 5 : 2;
            }

            // 限制速度范围并更新ARR
            uint32_t clamped_speed = (m->current_speed < INITIAL_SPEED2) ? INITIAL_SPEED2 : ((m->current_speed > MAX_SPEED2) ? MAX_SPEED2 : m->current_speed);
            __HAL_TIM_SET_AUTORELOAD(htim, (TIMER_CLK / clamped_speed));

            // 生成脉冲并更新位置
            HAL_GPIO_TogglePin(M_STP2_GPIO_Port, M_STP2_Pin);
            m->current_steps += (m->is_direction) ? 1 : -1;

            // 状态切换逻辑
            if (m->steps_remaining <= m->decel_steps) 
            {
                m->accel_phase = 2; // 进入减速
            } else if (m->current_speed >= MAX_SPEED2) 
            {
                m->accel_phase = 1; // 进入匀速
            }

            if (m->steps_remaining == 0) StepperMotor_Stop(m);
        }
	}
}

//void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim)
//{
//	if(htim->Instance == TIM8)
//	{
//        // 停止PWM输出
//        HAL_TIM_PWM_Stop_DMA(&htim8, TIM_CHANNEL_1);

//        // 运动完成后的操作
//        StepperMotor_Stop(&g_stepper);		
//	}
//}




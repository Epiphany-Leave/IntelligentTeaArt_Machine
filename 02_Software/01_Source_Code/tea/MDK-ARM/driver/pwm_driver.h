#ifndef __PWM_DRIVER_H__
#define __PWM_DRIVER_H__

#include "commond.h"

// 舵机缓动控制结构体
typedef struct {
    TIM_HandleTypeDef *htim;    // 定时器句柄
    uint32_t channel;           // PWM通道
    float current_angle;        // 当前角度
    float target_angle;         // 目标角度
    float step_per_tick;        // 每tick步长
    uint8_t is_moving;          // 运动状态标志
	uint8_t is_initialized;
} ServoControl;

#define MAX_SERVOS 5
extern ServoControl servoControls[MAX_SERVOS];  // 支持5个舵机



void pwm_driver_init(void);

uint16_t angle_to_ccr(float angle);
void Servo_SetAngle(TIM_HandleTypeDef *htim, uint32_t channel, float angle);
uint8_t Servo_Register(TIM_HandleTypeDef *htim, uint32_t channel);
void Servo_SetInstantAngle(TIM_HandleTypeDef *htim, uint32_t channel, float angle);
uint8_t Servo_StartSmoothMove(TIM_HandleTypeDef *htim, uint32_t channel, 
                             float target_angle, uint16_t duration_ms);
uint8_t Servo_IsMoving(TIM_HandleTypeDef *htim, uint32_t channel);

//void GPIO_OutputPulses(uint32_t pulse_count, uint32_t pulse_period_us);



#endif /* __PWM_DRIVER_H__ */



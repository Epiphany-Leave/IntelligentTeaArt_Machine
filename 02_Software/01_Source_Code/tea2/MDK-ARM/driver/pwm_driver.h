#ifndef __PWM_DRIVER_H__
#define __PWM_DRIVER_H__

#include "main.h"
#include <stdio.h>

typedef enum
{
	SERVO1,
	SERVO2,
	SERVO_SUM,
}SERVO;

// 定义PWM通道枚举（更直观的命名）
typedef enum {
    SERVO_CH1 = TIM_CHANNEL_1,
    SERVO_CH2 = TIM_CHANNEL_2,
    SERVO_CH3 = TIM_CHANNEL_3,
    SERVO_CH4 = TIM_CHANNEL_4
} ServoChannel;

// 定义舵机编号和参数结构体
typedef struct {
    ServoChannel channel;  // 关联的PWM通道
    uint16_t min_pulse;    // 最小脉冲宽度（0度对应值）
    uint16_t max_pulse;    // 最大脉冲宽度（180度对应值）
} ServoConfig;



void pwm_driver_init(void);

//void GPIO_OutputPulses(uint32_t pulse_count, uint32_t pulse_period_us);



#endif /* __PWM_DRIVER_H__ */



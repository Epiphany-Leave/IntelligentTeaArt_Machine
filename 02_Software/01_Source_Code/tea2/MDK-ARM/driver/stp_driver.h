#ifndef __STP_DRIVER_H__
#define __STP_DRIVER_H__

#include "main.h"
#include <stdbool.h>

#define STEPS_PER_REV	6400	// 每转脉冲数

typedef struct
{
    // 运行参数
    volatile int32_t target_steps;
    volatile int32_t current_steps;
    uint32_t steps_per_rev;
    uint8_t is_moving;
	uint8_t is_direction;
}STP_TYPEDEFT;

void StepperMotor_Init(STP_TYPEDEFT* motor);
uint8_t StepperMotor_IsMoving(STP_TYPEDEFT* motor);
void StepperMotor_Stop(STP_TYPEDEFT* motor);
void StepperMotor_SetAngle(STP_TYPEDEFT* motor, float degrees);


#endif /* __STP_DRIVER_H__ */



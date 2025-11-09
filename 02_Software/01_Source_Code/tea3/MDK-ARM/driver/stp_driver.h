#ifndef __STP_DRIVER_H
#define __STP_DRIVER_H

#include "commond.h"

#define STEPS_PER_REV	102400	// 每转脉冲数
#define INITIAL_SPEED1	5000		// 初始转速
#define MAX_SPEED1		80000	// 最大转速
#define INITIAL_SPEED2	5000		// 初始转速
#define MAX_SPEED2		120000	// 最大转速
#define ACCEL_STEP		1		// 加速度步长
#define TIMER_CLK		10000000    // 时钟频率

typedef struct
{
    // 运行参数
    volatile int32_t target_steps;
    volatile int32_t current_steps;
    uint32_t steps_per_rev;
    uint8_t is_moving;
	uint8_t is_direction;
    uint32_t current_speed;    // 当前速度（Hz）
    int32_t steps_remaining;   // 剩余步数（需持久化）
    uint32_t accel_steps;       // 加速阶段总步数
    uint32_t decel_steps;       // 减速阶段总步数
    uint32_t total_steps;       // 总运动步数
    uint8_t  accel_phase;       // 当前阶段：0-加速，1-匀速，2-减速
}STP_TYPEDEFT;

extern STP_TYPEDEFT g_stepper1;
extern STP_TYPEDEFT g_stepper2;

void StepperMotor_Init(STP_TYPEDEFT* motor);
uint8_t StepperMotor_IsMoving(STP_TYPEDEFT* motor);
void StepperMotor_StartPulse(uint32_t pulse_count);
void StepperMotor_Stop(STP_TYPEDEFT* motor);

void StepperMotor_SetSpeed(STP_TYPEDEFT* motor, uint16_t rpm) ;
void StepperMotor_SetAngle(STP_TYPEDEFT* motor, float degrees);


#endif /* __STP_DRIVER_H */



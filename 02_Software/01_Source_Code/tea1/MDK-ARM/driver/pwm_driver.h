#ifndef __PWM_DRIVER_H__
#define __PWM_DRIVER_H__

#include "main.h"
#include <stdio.h>

typedef enum
{
	servo1,
	servo2,
	servo_sum,
}SERVO;


void pwm_driver_init(void);
void Servo_SetAngle(SERVO servo, float Angle);
void GPIO_OutputPulses(uint32_t pulse_count, uint32_t pulse_period_us);



#endif /* __PWM_DRIVER_H__ */



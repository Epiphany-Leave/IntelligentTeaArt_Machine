#ifndef __MOTOR_H
#define __MOTOR_H

#include "main.h"
#include "tim.h"

typedef enum
{
	STOP,
	FORWARD,
	REVERSE,
}MOTOR_DIRECTION;

void Motor_Init(void);// pwm²¨·¢ËÍ²âÊÔº¯Êý
void SetMotorSpeed(uint8_t dutyCycle);
void Motor_Direction(MOTOR_DIRECTION direction, uint8_t speed);

void Motor_test(void);


#endif // __MOTOR_H

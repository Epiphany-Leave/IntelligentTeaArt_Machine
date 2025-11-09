#include "main.h"
#include "tim.h"
#include "servo.h"

void Servo1_SetAngle(float Angle)
{
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, Angle / 180 * 2000 + 500);	//设置占空比
												//将角度线性变换，对应到舵机要求的占空比范围上
}

void Servo2_SetAngle(float Angle)
{
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, Angle / 180 * 2000 + 500);	//设置占空比
												//将角度线性变换，对应到舵机要求的占空比范围上
}

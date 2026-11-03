#ifndef __MOTOR_DRIVER_H__
#define __MOTOR_DRIVER_H__

#include "main.h"
#include <stdbool.h>

#define Motor_1	0
#define Motor_2	1

#define PUMP_1	0
#define PUMP_2	1

void Set_motor1_speed(int16_t v);
void Set_motor2_speed(int16_t v);
void Motor_Control(uint8_t motor_id, uint16_t v);

void Set_water1_speed(uint8_t file);
void Set_water2_speed(uint8_t file);
void WaterPump_Control(uint8_t pump_id, uint8_t file);

#endif /* __STP_DRIVER_H__ */



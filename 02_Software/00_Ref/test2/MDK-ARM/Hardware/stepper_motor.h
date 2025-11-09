#ifndef __STEPPER_MOTOR_H
#define __STEPPER_MOTOR_H

#include "main.h"

#define error_x 0
#define error_y 0

#define location_x_zero 6500+error_x
#define location_y_zero 6500+error_y

#define location_turn   10300+error_x
#define location_plate1 5800+error_x
#define location_plate2 17180+error_x

#define STEP_ANGLE 1.8   // 步进电机的步距角，单位：度-----细分度

typedef struct
{
    uint8_t  down_flag;//若该标志位为1，下一周期为脉冲的下降沿
    uint8_t  finish_flag;//运动到目标位置后置1
    uint16_t location_target;//目标位置
    uint16_t location_now;//当前位置
    uint16_t target_last;
    uint16_t target_temp;
    int16_t  difference_value;
    int16_t  difference_middle;
    int16_t  speed;
    uint8_t  speed_en;//使能加减速
    //新加减速用
    uint16_t ARR_fast;
    uint16_t ARR_slow;
    uint16_t ARR_now;
    double speed_fast;
    double speed_slow;
    double speed_now;
    double acceler;
    uint32_t acceler_num;
}joint;

typedef struct
{
    uint8_t Res;
    int8_t rx_flag;
    uint8_t finish_flag;
    uint8_t receive[30];
//    uint8_t data[30];
    
}usart_data;

typedef struct
{
    uint16_t times;
    uint8_t  task_now;
    uint8_t  material[4];
    uint8_t  mat_num;
    uint8_t  num_now;
}task_sch;


extern usart_data usart1_data;
extern usart_data usart2_data;
extern usart_data usart3_data;
extern usart_data lpusart_data;
extern joint joints[2];
extern uint8_t operation_flag;
extern uint8_t claw_open;
extern task_sch task_all;
extern char text_tx[5];
extern uint8_t floor_flag;

/* 逻辑代码 */
void motor_init(void);
void motor_opera(void);
void StepMotorControl(joint* j, TIM_TypeDef* TIMx, GPIO_TypeDef* dirPort, uint16_t dirPin, GPIO_TypeDef* stpPort, uint16_t stpPin);

uint16_t calculate_steps(float angle);
void rotate_motor_to_angle(float angle);

#endif //__STEPPER_MOTOR_H

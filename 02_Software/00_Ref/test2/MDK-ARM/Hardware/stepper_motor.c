#include "stepper_motor.h"

//步进电机
joint joints[2]={0};
uint8_t operation_flag=0;

//串口
usart_data usart1_data={0};
usart_data usart2_data={0};
usart_data usart3_data={0};
usart_data lpusart_data={0};

uint8_t claw_open=0;

//任务管理
task_sch task_all={0};

char text_tx[5]={0};

uint8_t floor_flag=0;

// 初始化步进电机参数
void motor_init(void)
{
    joints[0].speed = 499;
    joints[1].speed = 499;
    
    joints[0].ARR_fast = 48;
    joints[0].ARR_slow = 1299;
    joints[0].acceler = 0.1;

    joints[1].ARR_fast = 48;
    joints[1].ARR_slow = 1299;
    joints[1].acceler = 0.07;
    
    joints[0].speed_en = 1;
    joints[1].speed_en = 1;
    
    joints[0].speed_slow = 10000.0 / joints[0].ARR_slow;
    joints[0].speed_fast = 10000.0 / joints[0].ARR_fast;
    joints[1].speed_slow = 10000.0 / joints[1].ARR_slow;
    joints[1].speed_fast = 10000.0 / joints[1].ARR_fast;
}

// 步进电机操作逻辑
void motor_opera(void)
{
    switch (operation_flag)
    {
        case 2: // 步进电机初始化
            HAL_GPIO_WritePin(M_EN_GPIO_Port, M_EN_Pin, GPIO_PIN_SET);
            joints[0].location_now = 5000;
            joints[0].target_temp = joints[0].location_now;
            joints[0].location_target = location_x_zero;
            joints[0].finish_flag = 0;
            
            joints[1].location_now = 5000;
            joints[1].target_temp = joints[1].location_now;
            joints[1].location_target = 6400;
            joints[1].finish_flag = 0;
            
            operation_flag = 200;
        break;

        case 6: // 检查步进电机位置
            if ((joints[1].location_now < (joints[1].location_target + 500)) &&
                joints[1].location_now > (joints[1].location_target - 500))
            {
                joints[0].location_target = location_turn;
                joints[0].finish_flag = 0;
                operation_flag = 7;
            }
        break;

        // 更多操作状态可以根据需求添加
    }
}

// 通用的加减速处理函数
void StepMotorControl(joint* j, TIM_TypeDef* TIMx, GPIO_TypeDef* dirPort, uint16_t dirPin, GPIO_TypeDef* stpPort, uint16_t stpPin)
{
    if (j->speed_en == 1) {
        if (j->location_target != j->target_temp) {
            j->difference_value = j->location_target - j->target_temp;
            j->difference_middle = j->difference_value / 2 + j->target_temp;
            j->target_last = j->target_temp;
            j->target_temp = j->location_target;
            j->ARR_now = j->ARR_slow;
            j->speed_now = j->speed_slow;
            j->acceler_num = 0;
        }

        if (j->target_last < j->location_target) {
            if (j->location_now < j->difference_middle) {
                // 加速
                j->speed_now += j->acceler;
                if (j->speed_now > j->speed_fast) {
                    j->acceler_num++;
                    j->speed_now = j->speed_fast;
                }
                j->ARR_now = (int)(10000.0 / j->speed_now);
                if (j->ARR_now > j->speed) {
                    j->ARR_now = j->speed;
                }
                TIMx->ARR = j->ARR_now;
            } else {
                // 减速
                if (j->acceler_num > 0) {
                    j->acceler_num--;
                } else {
                    j->speed_now -= j->acceler;
                    if (j->speed_now < j->speed_slow) {
                        j->speed_now = j->speed_slow;
                    }
                }
                j->ARR_now = (int)(10000.0 / j->speed_now);
                TIMx->ARR = j->ARR_now;
            }
        } else if (j->target_last > j->location_target) {
            if (j->location_now > j->difference_middle) {
                // 加速
                j->speed_now += j->acceler;
                if (j->speed_now > j->speed_fast) {
                    j->acceler_num++;
                    j->speed_now = j->speed_fast;
                }
                j->ARR_now = (int)(10000.0 / j->speed_now);
                if (j->ARR_now > j->speed) {
                    j->ARR_now = j->speed;
                }
                TIMx->ARR = j->ARR_now;
            } else {
                // 减速
                if (j->acceler_num > 0) {
                    j->acceler_num--;
                } else {
                    j->speed_now -= j->acceler;
                    if (j->speed_now < j->speed_slow) {
                        j->speed_now = j->speed_slow;
                    }
                }
                j->ARR_now = (int)(10000.0 / j->speed_now);
                TIMx->ARR = j->ARR_now;
            }
        }
    } else {
        TIMx->ARR = j->speed;
    }

    // 更新电机控制引脚
    if (j->down_flag == 1) {
        HAL_GPIO_WritePin(stpPort, stpPin, GPIO_PIN_RESET);
        j->down_flag = 0;
    } else if (j->location_now < j->location_target) {
        HAL_GPIO_WritePin(dirPort, dirPin, GPIO_PIN_RESET); // 设定正转
        HAL_GPIO_WritePin(stpPort, stpPin, GPIO_PIN_SET);
        j->location_now++;
        j->down_flag = 1;
    } else if (j->location_now > j->location_target) {
        HAL_GPIO_WritePin(dirPort, dirPin, GPIO_PIN_SET); // 设定反转
        HAL_GPIO_WritePin(stpPort, stpPin, GPIO_PIN_SET);
        j->location_now--;
        j->down_flag = 1;
    } else if (j->location_now == j->location_target) {
        j->finish_flag = 1; // 运动完成
    }
}

// 计算步数
uint16_t calculate_steps(float angle) 
{
    return (uint16_t)(angle / STEP_ANGLE);
}

// 设置目标角度并旋转
// 使用方法：rotate_motor_to_angle(角度)
void rotate_motor_to_angle(float angle) 
{
    uint16_t steps = calculate_steps(angle);  // 计算目标步数
    
    joints[0].location_target = joints[0].location_now + steps;  // 设置目标位置
    joints[0].finish_flag = 0;  // 清除完成标志
    operation_flag = 6;  // 设置步进电机操作状态
}





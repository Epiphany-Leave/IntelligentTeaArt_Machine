#include "interrupt.h"
#include "stepper_motor.h"

// 创建按键状态机
struct keys key[SW_SUM]={0};

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	
	// 定时器 16 终端任务 10ms 执行代码
	if(htim->Instance == TIM6){
		
		StepMotorControl(&joints[0], TIM16, M_DIR_GPIO_Port, M_DIR_Pin, M_STP_GPIO_Port, M_STP_Pin); 
	}
	
	unsigned char i;
	// 定时器 7 中断任务 10ms 按键
	if(htim->Instance == TIM7){
		
		key[1].key_sta = HAL_GPIO_ReadPin (KEY1_GPIO_Port ,KEY1_Pin );
		key[2].key_sta = HAL_GPIO_ReadPin (KEY2_GPIO_Port ,KEY2_Pin );
		key[3].key_sta = HAL_GPIO_ReadPin (KEY3_GPIO_Port ,KEY3_Pin );
		
		for(i=0;i<SW_SUM;i++)
		{
			switch (key[i].judge_sta )
			{
				case 0:
				{
					if(key[i].judge_sta==0) 
					{
						key[i].key_time =0;
						key[i].judge_sta =1;
					}
				}
				break;
				
				case 1:
				{
					if(key[i].key_sta == 0)
					{
						key[i].judge_sta =2;
					}
					else 
					{
						key[i].judge_sta =0;
					}
				}
				break;
				
				case 2:
				{
					if(key[i].key_sta == 1)
					{
						key[i].judge_sta =0;
						if(key[i].key_time < SHORT_PRESS_TIME) 
						{
							key[i].s_flag =1;	//触发短按
						}
						if(key[i].key_time > SHORT_PRESS_TIME) 
						{
							key[i].l_flag =1;	//触发长按
					
						}
					}
					else
					{
						key[i].key_time ++;
					}
				}
				break;
			}
		}
	}	
	
	
}

////步进电机
//void UpdateMotor(int joint_id)
//{
//    joint* joint = &joints[joint_id];

//    // 处理目标位置的变化
//    if (joint->location_target != joint->target_temp)
//    {
//        joint->difference_value = joint->location_target - joint->target_temp;
//        joint->difference_middle = joint->difference_value / 2 + joint->target_temp;
//        joint->target_last = joint->target_temp;
//        joint->target_temp = joint->location_target;
//        joint->ARR_now = joint->ARR_slow;
//        joint->speed_now = joint->speed_slow;
//        joint->acceler_num = 0;
//    }

//    // 处理加速和减速阶段
//    if (joint->target_last < joint->location_target) // 正向运动
//    {
//        HandleMotorAcceleration(joint, true);
//    }
//    else if (joint->target_last > joint->location_target) // 反向运动
//    {
//        HandleMotorAcceleration(joint, false);
//    }
//    else
//    {
//        TIM_SetARR(joint->ARR_now); // 保持当前位置
//    }

//    // 位置更新和方向控制
//    if (joint->down_flag == 1)
//    {
//        HAL_GPIO_WritePin(STP_GPIO_Port[joint_id], STP_Pin[joint_id], GPIO_PIN_RESET);
//        joint->down_flag = 0;
//    }
//    else
//    {
//        UpdateMotorPosition(joint_id);
//    }
//}



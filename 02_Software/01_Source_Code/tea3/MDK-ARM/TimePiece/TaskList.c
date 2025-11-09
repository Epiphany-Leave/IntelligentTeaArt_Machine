#include "TaskList.h"
#include "shell_port.h"
#include "string.h"
#include <math.h>

TASK_FLAG Task_Flag;
//extern union data lon[1024];
//extern union data lat[1024];
//extern pdata pLon;
//extern pdata pLat;

//static enum taskID taskName;

task_t taskList[TaskListNum] = {
//    INIT_TASK(TASKNAME_KeyScan, TaskHandlerDeclare(KeyScan), 30),
//    INIT_TASK(TASKNAME_DataSync, TaskHandlerDeclare(DataSync), 10),
//    INIT_TASK(TASKNAME_PIDController, TaskHandlerDeclare(PIDController), 10),
//    INIT_TASK(TASKNAME_Tick, TaskHandlerDeclare(Tick), 1),
//	INIT_TASK(TASKNAME_Meun, TaskHandlerDeclare(Meun), 10),
    INIT_TASK(TASKNAME_Beep, TaskHandlerDeclare(Beep), 100),
    INIT_TASK(TASKNAME_WIFI, TaskHandlerDeclare(WIFI), WIRELESS_SEND_TIME),
    INIT_TASK(TASKNAME_Servo, TaskHandlerDeclare(Servo), 1),
	INIT_TASK(TASKNAME_Clean, TaskHandlerDeclare(Clean), 10),
	INIT_TASK(TASKNAME_Preheat, TaskHandlerDeclare(Preheat), 10),
	INIT_TASK(TASKNAME_Maketea, TaskHandlerDeclare(Maketea), 10),
    INIT_TASK(TASKNAME_Addtea, TaskHandlerDeclare(Addtea), 10),
};

/**
 * @brief 清洗检测
 *
 */
uint32_t clean_time = 0;
void TaskHandlerDeclare(Clean)(void)
{
	if(clean_flag == 1)
	{
		clean_time++;
        if(clean_time == 1000)
        {
            beep_on(mode3);
        }
        if(clean_flag == 0)
        {
            clean_time = 0;
        }        
        Clean_Control();
	}
}

/**
 * @brief 预热检测
 *
 */
uint32_t preheat_time = 0;
void TaskHandlerDeclare(Preheat)(void)
{
	if(preheat_flag == 1)
    {
        preheat_time++;
        Preheat_Control();
    }
}

/**
 * @brief 煮茶检测
 *
 */
uint32_t maketea_time = 0;
void TaskHandlerDeclare(Maketea)(void)
{
	if(maketea_flag == 1)
    {
        maketea_time++;
        if(maketea_time == 3410)
        {
            beep_on(mode3);
        }
        if(maketea_flag == 0)
        {
            maketea_time = 0;
        }
		Maketea_Control();
    }
}

/**
 * @brief 添茶检测
 *
 */
uint32_t addtea_time = 0;
void TaskHandlerDeclare(Addtea)(void)
{
    if(addtea_flag == 1)
    {
        addtea_time++;
        if(addtea_time == 3070)
        {
            beep_on(mode3);
        }
        if(addtea_flag == 0)
        {
            addtea_time = 0;
        }
        Addtea_Control();
    }
}


/**
 * @brief 按键检测
 *
 */
//void TaskHandlerDeclare(KeyScan)(void)
//{
//	key_process();
//	KeyEventCallBack();
//}

/**
 * @brief 获取定时器运行时间供shell使用
 * 1ms
 */
uint32_t shellTick;
void TaskHandlerDeclare(Tick)(void)
{
    shellTick++;
}

/**
 * @brief 获取定时器运行时间供Beep使用
 * 100ms
 */
void TaskHandlerDeclare(Beep)(void)
{
    beep_run();
}


/**
 * @brief 获取系统运行时间供Meun使用
 * 10ms
 */
//void TaskHandlerDeclare(Meun)(void)
//{
//	Task_Flag.meun_count++;
//}

/**
 * @brief 获取3000ms运行时间供WIFI使用
 * 3000ms
 */
void TaskHandlerDeclare(WIFI)(void)
{
    wireless_send_flag = 1;
}

/**
 * @brief 获取1ms运行时间供Servo使用
 * 1ms
 */
uint32_t servoTick = 0;
volatile uint8_t current_servo = 0; // 当前处理舵机索引
void TaskHandlerDeclare(Servo)(void)
{
    for(uint8_t i=0; i<MAX_SERVOS; i++)
    {
        if(servoControls[i].is_moving) 
		{
            // 更新当前角度
            servoControls[i].current_angle += servoControls[i].step_per_tick;

            // 边界检查
            if((servoControls[i].step_per_tick > 0 &&
                    servoControls[i].current_angle >= servoControls[i].target_angle) ||
                    (servoControls[i].step_per_tick < 0 &&
                     servoControls[i].current_angle <= servoControls[i].target_angle))
			{
                servoControls[i].current_angle = servoControls[i].target_angle;
                servoControls[i].is_moving = 0;
            }

            // 更新PWM输出
            uint16_t ccr = angle_to_ccr(servoControls[i].current_angle);
            __HAL_TIM_SET_COMPARE(servoControls[i].htim,
                                  servoControls[i].channel,
                                  ccr);
        }
	}
}

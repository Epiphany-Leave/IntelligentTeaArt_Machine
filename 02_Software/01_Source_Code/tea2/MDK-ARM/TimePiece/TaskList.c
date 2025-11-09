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
    INIT_TASK(TASKNAME_KeyScan, TaskHandlerDeclare(KeyScan), 30),
//    INIT_TASK(TASKNAME_DataSync, TaskHandlerDeclare(DataSync), 10),
//    INIT_TASK(TASKNAME_PIDController, TaskHandlerDeclare(PIDController), 10),
//    INIT_TASK(TASKNAME_DataLogger, TaskHandlerDeclare(DataLogger), 50),
//    INIT_TASK(TASKNAME_Refresh, TaskHandlerDeclare(Refresh), 50),
    INIT_TASK(TASKNAME_Tick, TaskHandlerDeclare(Tick), 1),
	INIT_TASK(TASKNAME_Meun, TaskHandlerDeclare(Meun), 10),
	INIT_TASK(TASKNAME_Beep, TaskHandlerDeclare(Beep), 50),
};

/**
 * @brief 按键检测
 *
 */
void TaskHandlerDeclare(KeyScan)(void)
{
	key_process();
	KeyEventCallBack();
}

//static unsigned char beep_count = 0;
void TaskHandlerDeclare(Beep)(void)
{
	beep_run();
}

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
 * @brief 获取系统运行时间供shell使用
 * 10ms
 */
void TaskHandlerDeclare(Meun)(void)
{
	Task_Flag.meun_count++;
}

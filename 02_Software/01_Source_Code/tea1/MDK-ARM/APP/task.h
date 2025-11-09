#ifndef __TASK_H__
#define __TASK_H__

#include "main.h"

#include "commond.h"

typedef enum
{
    Task_0_Initial, //初始状态
    Task_1_Get_ADC_VALUE, //获取ADC值
    Task_2_Vin_detc,      //检测输入电压
    Task_3_Iout_detc,     //检测输出电压
    Task_4_Soft_start,     //开始缓启动
	Task_SUM,
} System_Task;

#endif /* __TASK_H__ */


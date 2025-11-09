#ifndef TEMPF401_TASKLIST_H
#define TEMPF401_TASKLIST_H

#include "main.h"

#include "timepiece.h"

#include "commond.h"


enum taskID {
	TASKNAME_KeyScan = 1,
//    TASKNAME_LED,
//    TASKNAME_DataSync,
//    TASKNAME_GetIMU,
//    TASKNAME_PIDController,
//    TASKNAME_DataLogger,
//    TASKNAME_Refresh,
//    TASKNAME_GPSDecode,
    TASKNAME_Tick,
	TASKNAME_Meun,
	TASKNAME_Beep
};

typedef struct
{
	uint32_t meun_count;
}TASK_FLAG;

extern TASK_FLAG Task_Flag;

//void TaskHandlerDeclare(LED)(void);
void TaskHandlerDeclare(KeyScan)(void);
//void TaskHandlerDeclare(DataSync)(void);
//void TaskHandlerDeclare(PIDController)(void);
//void TaskHandlerDeclare(DataLogger)(void);
//void TaskHandlerDeclare(Refresh)(void);
void TaskHandlerDeclare(Tick)(void);
void TaskHandlerDeclare(Meun)(void);
void TaskHandlerDeclare(Beep)(void);
#endif // TEMPF401_TASKLIST_H

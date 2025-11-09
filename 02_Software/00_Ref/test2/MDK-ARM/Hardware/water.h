#ifndef __WATER_H
#define __WATER_H

#include "main.h"

typedef enum
{
	Water1,
	Water2,
	Water_SUM,
}WATER_TYPEDEF;

typedef enum
{
	Water_STOP,
	Water_RUN,
}WATER_STA_TYPEDEF;

void Water_Status(WATER_TYPEDEF Water, WATER_STA_TYPEDEF sta);

#endif // __WATER_H

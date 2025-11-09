#include "water.h"

void Water_Status(WATER_TYPEDEF Water, WATER_STA_TYPEDEF sta)
{
	switch(Water)
	{
		case Water1:
			if(sta)
			{
				HAL_GPIO_WritePin(WATER1_GPIO_Port, WATER1_Pin, GPIO_PIN_SET);
			}
			else
			{
				HAL_GPIO_WritePin(WATER1_GPIO_Port, WATER1_Pin, GPIO_PIN_RESET);
			}
		break;
			
		case Water2:
			if(sta)
			{
				HAL_GPIO_WritePin(WATER2_GPIO_Port, WATER2_Pin, GPIO_PIN_SET);
			}
			else
			{
				HAL_GPIO_WritePin(WATER2_GPIO_Port, WATER2_Pin, GPIO_PIN_RESET);
			}
		break;
			
		default:
		break;			
	}
}

#include "Uart_interrupt.h"
#include "usart.h"

volatile uint8_t DMA_flag = 0;

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart->Instance == USART1)
	{
//		if(rx1_byte[0] == 'A')
//		{
//			printf("1!\r\n");
//		}
//		HAL_UART_Receive_IT(&huart1, (uint8_t *)rx1_byte, 1);		
	}
	if(huart->Instance == USART2)
	{
		wireless_receive_callback(rx2_byte[0]);
		HAL_UART_Receive_IT(&huart2, rx2_byte, 1);
	}
	if(huart->Instance == USART3)
	{
		writeRingBuff(RxBuff[0]);		
		HAL_UART_Receive_IT(&huart3, RxBuff, 1);
//		printf("received: 0x%02", RxBuff[0]);	
	}
	return;
}


void uart2_send_string(char *str) 
{
    uint16_t len = strlen(str);
    HAL_UART_Transmit(&huart2, (uint8_t *)str, len, HAL_MAX_DELAY);
}



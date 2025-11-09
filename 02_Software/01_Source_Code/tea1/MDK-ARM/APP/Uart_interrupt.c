#include "Uart_interrupt.h"


//void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
//{
//    if(huart->Instance==LPUART1)
//    {
//			uart2_read_data(rx_lpuart);
//        HAL_UART_Receive_IT(&hlpuart1,&rx_lpuart,1);
//    }
//    else if(huart->Instance==USART2)
//    {
//        HAL_UART_Receive_IT(&huart2,&rx_uart2,1);
//    }
//    
//}

//void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart)
//{
//	//UNUSED(huart);
//	if(huart->Instance==LPUART1)
//	{
//		__HAL_UNLOCK(&hlpuart1);
//		HAL_UART_Receive_IT(&hlpuart1,&rx_lpuart,1);
//		
//	}
//	
//}


#include "Uart_interrupt.h"
#include "usart.h"

volatile uint8_t DMA_flag = 0;

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart->Instance == USART1)
	{
		if(rx_byte[0] == 'A')
		{
			printf("1!\r\n");
		}
		HAL_UART_Receive_IT(&huart1, (uint8_t *)rx_byte, 1);		
	}
	if(huart->Instance == USART2)
	{
//		if (Connect_flag == 0) // 检查连接标志
//        {            
////            if (huart2.pRxBuffPtr[0]) // 确保数据非零
////            {
//                // 将数据存入缓冲区
//                Usart2_RxBuff[Usart2_RxCounter++] = rx_byte[0];
////				Usart2_RxCounter++;
//				printf("%s\r\n", Usart2_RxBuff);
//				HAL_UART_Receive_IT(&huart2, (uint8_t *)rx_byte, 1);
////            }
//			// 如果需要继续接收下一个字节，则重新启动接收
////			HAL_UART_Receive_IT(&huart2, &Usart2_RxBuff[Usart2_RxCounter], 1);
////			HAL_UART_Receive_IT(&huart2, Usart2_RxBuff, USART2_RXBUFF_SIZE);
//		}
		if(rx_byte[0] == 'A')
		{
			printf("%s\r\n", rx_byte);
		}
		HAL_UART_Receive_IT(&huart2, (uint8_t *)rx_byte, 1);
	}
	if(huart->Instance == USART3)
	{
		if(rx_byte[0] == 'A')
		{
			printf("1!\r\n");
		}
		HAL_UART_Receive_IT(&huart3, (uint8_t *)rx_byte, 1);		
	}
}


///* 覆盖HAL库中的弱声明回调函数 */
//void HAL_DMA_Tx_CpltCallback(DMA_HandleTypeDef *hdma)
//{
//    /* 检查是否为DMA1通道7 */
//    if (hdma->Instance == DMA1_Channel2)
//    {
//        /* 清除DMA标志位，表示空闲状态 */
//        DMA_flag = 0;

//        /* 停止DMA通道 */
//        HAL_DMA_Abort(hdma); // 使用HAL_DMA_Abort停止DMA传输 [ty-reference](22)

//        /* 如果需要进一步操作，例如重新配置或释放资源，可在此处添加 */
//    }
//}

void u2_printf(char *fmt, ...)
{
    static uint8_t usart2_tx_buffer[USART2_TXBUFF_SIZE];
    va_list args;
    uint16_t len;
    
    va_start(args, fmt);
    len = vsnprintf((char *)usart2_tx_buffer, USART2_TXBUFF_SIZE, fmt, args);
    va_end(args);
    
//    HAL_UART_Transmit_DMA(&huart2, usart2_tx_buffer, len);
	HAL_UART_Transmit(&huart2, usart2_tx_buffer, len, 1);
}

void u2_TxData(uint8_t *data)
{
    uint16_t length = data[0] << 8 | data[1];
    while(DMA_flag); // 等待DMA空闲
    DMA_flag = 1;
    HAL_UART_Transmit_DMA(&huart2, &data[2], length);
//	HAL_UART_Transmit(&huart2, &data[2], length, 1);
}

void WiFi_Sendtest(char *cmd)
{
	WiFi_RxCounter = 0;						  // WiFi接收数据量变量清零
	memset(WiFi_RX_BUF, 0, WiFi_RXBUFF_SIZE); //清空WiFi接收缓冲区
	WiFi_printf("%s\r\n", cmd);				  //发送指令
}

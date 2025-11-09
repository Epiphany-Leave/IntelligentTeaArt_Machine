#include "Tim_interrupt.h"

delay_time delay={0};

static void delay_count(void);


CCMRAM void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
//	extern uint8_t uart1_receiveData_parse(void);
    /* Period: 10ms */
    
    /* Period: 1ms */
    if(htim->Instance==TIM17)
    {
		
//		delay_count();
//        delay_handle();
    }
    

}


CCMRAM void delay_handle()
{
	extern uint8_t uart1_receiveData_parse(void);
    if(delay.ms_1==1)
    {
		
        delay.ms_1=0;
    }
    if(delay.ms_10==1)
    {
		key_process();
		KeyEventCallBack();
        delay.ms_10=0;
    }
    if(delay.ms_50==1)
    {
		VolatgeEventCallBack();
        delay.ms_50=0;
    }
}

static void delay_count(void) 
{
    delay.time++;
    delay.ms_1=1;
    if(delay.time%10==0)
    {
        delay.ms_10=1;
    }
    if(delay.time%50==0)
    {
        delay.ms_50=1;
    }
    if(delay.time>=10000)
    {
        delay.time=0;
    }
}



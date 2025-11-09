#include "task.h"

/**********************系统任务**************************************/
CCMRAM System_Task Current_State,Next_State;

CCMRAM void bcfsm(void)  //CCMRAM把函数放进CCRAM内存，加速执行速度
{
    Next_State=Current_State=Task_0_Initial;
    while(1)
    {
        Current_State=Next_State;
        switch(Current_State)
        {
			case Task_0_Initial:
			{
				// 开启ADC
				HAL_ADC_Start(&hadc1);
				// 开始轮询转换
				HAL_ADC_PollForConversion(&hadc1,100);  
			
				key_driver_init();
				adc_driver_init();
			
//  			beep_SetFreq(1000);
//  			beep_on(mode1);
			
				HAL_TIM_Base_Start_IT(&htim17); //1ms
//				printf("OK!\r\n");
				Next_State=Task_1_Get_ADC_VALUE;		 //下一状态：读取ADC值
			}
			break;
			case Task_1_Get_ADC_VALUE ://获取ADC电压
			{
//				if(Data_update_flag==START)	       //检测到ADC数据有更新
//				{
//					Iout=ADC2_RESULT[1];
//					Vin=ADC2_RESULT[2];
//					Next_State=Task_2_Vin_detc;
//					Data_update_flag=STOP;
//					if(ERROR_flag==START)Next_State=Task_0_Initial_state;
//				}
//				else  Next_State=Task_1_Get_ADC_VALUE;  //等待数据更新
			}
			break;
			case Task_2_Vin_detc://检测输入电压
			{
//				Vin_f=(float)((Vin*3300)>>12)*0.0175f;  //((Vin*3300)/4096)*17.5/1000 ，17.5代表电阻分压，1000转化为V
//				if(Vin_f>36.0f||Vin_f<12.0f)
//				{
//					Red_ON();
//					ERROR_flag=START;
//					Next_State=Task_0_Initial_state;    //下一状态：复位
//					break;
//				}
				Next_State=Task_3_Iout_detc;					 	//低压正常，开始检测输出
			}
			break;
			case Task_3_Iout_detc : //检测输入电流
			{
//				Iout_f=(float)((Iout*3300)>>12)*0.0019047f;//((Vin*3300)/4096)/17.5/30; 17.5代表放大倍数，30代表采样电阻值，A
//	
//				if(Iout_f>3.0f)
//				{
//					Red_ON();
//					ERROR_flag=START;
//					Next_State=Task_0_Initial_state;//输出电压大于14V，触发输出过压保护
//					break;
//				}
//				if(flag_start_cnt!=STOP)	
//					Next_State=Task_4_Soft_start ;
//				else 		
//					Next_State=Task_1_Get_ADC_VALUE;
			}
			break;
			case Task_4_Soft_start ://缓启动
			{
//				flag_start_cnt=STOP;
//				/*Add your code here!
//				*/
//				Green_ON();//系统指示
//				Next_State=Task_1_Get_ADC_VALUE;
			}
			break;
			default:
				break;
        }
    }
}



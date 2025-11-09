#include "beep_bsp.h"
#include "main.h"
#include "tim.h"

#define SYSTEM_FREQ  170
#define BEEP_TIM     htim4
#define BEEP_CHANNEL TIM_CHANNEL_1

beep_struct beep = {silent,0};

void beep_SetFreq(uint16_t freq)
{
    uint32_t Period =  1000000/ freq;
    uint16_t Pulse  = Period / 2;

    HAL_TIM_PWM_Start(&BEEP_TIM,BEEP_CHANNEL);// 启动定时器的PWM模式

    /*设置频率和占空比*/
    __HAL_TIM_SET_PRESCALER(&BEEP_TIM,SYSTEM_FREQ-1);

    __HAL_TIM_SET_AUTORELOAD(&BEEP_TIM, Period - 1);

    __HAL_TIM_SET_COMPARE(&BEEP_TIM,BEEP_CHANNEL,Pulse);
}

void beep_off(void)
{
    HAL_TIM_PWM_Stop(&BEEP_TIM,BEEP_CHANNEL);// 停止定时器的PWM输出
}

void beep_on(beep_mode mode)
{
    beep.mode=mode;
    beep.time=0;
    beep.num=0;
}

void beep_run(void)
{
    switch(beep.num)
    {
    case 0:
        if(beep.mode>0)
        {
            beep.num=beep.mode;
            beep.mode=silent;
        }
        break;

    case 1:
        switch(beep.time)
        {
        case 0:
            beep_SetFreq(3000);//蜂鸣器
            break;

        case 1:
            beep_off();
            break;

        case 2:
            beep_SetFreq(4000);
            break;

        case 3:
            beep_off();
            break;

        case 4:
            beep_SetFreq(5000);
            break;

        case 5:
            beep_off();
            break;
        }
        beep.time++;
        if(beep.time==6)
        {
            beep.time=0;
            beep.num=0;
        }
        break;

    case 2:
        switch(beep.time)
        {
        case 0:
            beep_SetFreq(2000);//蜂鸣器
            break;
        case 3:
            beep_off();
            break;
        }
        beep.time++;
        if(beep.time==4)
        {
            beep.time=0;
            beep.num=0;
        }
        break;

    case 3:
        switch(beep.time)
        {
        case 0:
            beep_SetFreq(5000);//蜂鸣器
            break;

        case 1:
            beep_off();
            break;

        case 2:
            beep_SetFreq(4000);
            break;

        case 3:
            beep_off();
            break;

        case 4:
            beep_SetFreq(3000);
            break;

        case 5:
            beep_off();
            break;
        }
		
        beep.time++;
		
        if(beep.time==6)
        {
            beep.time=0;
            beep.num=0;
        }
		
        break;

    }
}

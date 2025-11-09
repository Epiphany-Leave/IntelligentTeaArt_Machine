#include "app.h"

__IO uint16_t result[1] = {0};
CCMRAM __IO float Vout = 0;  //输入电压

void KeyEventCallBack(void)
{
    for (uint8_t i = 0; i < key_num; i++)
    {
        if (key_array[i].key_value != key_none)
        {
            switch (key_array[i].key_value)
            {
            case key_click_one:
//                printf("Key %d single click detected!\n", i);
                break;
            case key_click_double:
//                printf("Key %d double click detected!\n", i);
                break;
            case key_long_press:
//                printf("Key %d long press detected!\n", i);
                break;
            default:
                break;
            }

            // 清除按键值，防止重复处理
            key_array[i].key_value = key_none;
        }
    }
}

void VolatgeEventCallBack(void)
{
	static uint16_t Vn=0x00,Vn_1=0x00,Vn_2=0x00,Vn_3;
	
	// 查询ADC状态
	uint32_t state = HAL_ADC_GetState(&hadc1);
	if (( state & HAL_ADC_STATE_REG_EOC) == HAL_ADC_STATE_REG_EOC)
	{
		//滑动滤波
		result[0] = HAL_ADC_GetValue(&hadc1)/4096.0*3.3*11.0;
		Vn=(Vn_1+Vn_2+Vn_3+result[0])>>2;
        Vn_1=Vn_2;
        Vn_2=Vn_3;
        Vn_3=result[0];
		
		// 获取ADC转换结果
		Vout = (float)Vn/4096.0*3.3*11;
//		printf("voltage: %.2f \r\n", Vout);
	}
	else
	{
//		printf("adc state %d \r\n",state);
	}
}

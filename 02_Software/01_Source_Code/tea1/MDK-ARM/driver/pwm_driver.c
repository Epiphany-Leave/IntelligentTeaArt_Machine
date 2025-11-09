#include "pwm_driver.h"
#include "pwm_bsp.h"

/**
***********************************************************************
* @brief:      adc_driver_init(void)
* @param:		   void
* @retval:     void
* @details:    ADC硬件使能
***********************************************************************
**/
void pwm_driver_init(void)
{
//	pwm_bsp_init();
}

void Servo_SetAngle(SERVO servo, float Angle)
{
	uint16_t angle = Angle / 180 * 2000 + 500;
	switch(servo)
	{
		case servo1:
			tim4_pwm_ccr_set(ch1, angle);
		printf("Servo1 rotation Angle: %d\r\n", angle);
		break;
		
		case servo2:
			tim4_pwm_ccr_set(ch2, angle);
		printf("Servo2 rotation Angle: %d\r\n", angle);
		break;
		
		default: break;
	}
}


void GPIO_OutputPulses(uint32_t pulse_count, uint32_t pulse_period_us)
{
    for (uint32_t i = 0; i < pulse_count; i++)
    {
        HAL_GPIO_WritePin(M_STP_GPIO_Port, M_STP_Pin, GPIO_PIN_SET); // 高电平
        HAL_Delay(pulse_period_us / 2 / 1000);              // 延时，高电平持续时间

        HAL_GPIO_WritePin(M_STP_GPIO_Port, M_STP_Pin, GPIO_PIN_RESET); // 低电平
        HAL_Delay(pulse_period_us / 2 / 1000);                // 延时，低电平持续时间
    }
}


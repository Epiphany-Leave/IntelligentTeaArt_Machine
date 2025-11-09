/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */ 
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#include "app.h"
#include "commond.h"

//#include <stdio.h>

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */



/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

//void lv_example_led_1(void);

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

	float angle_val = 0;
	
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART1_UART_Init();
  MX_TIM17_Init();
  MX_USART2_UART_Init();
  MX_USART3_UART_Init();
  MX_ADC1_Init();
  MX_TIM4_Init();
  /* USER CODE BEGIN 2 */
	// ï¿½ï¿½ï¿½ï¿½ADC
//	HAL_ADC_Start(&hadc1);
//	// ï¿½ï¿½Ê¼ï¿½ï¿½Ñ¯×ªï¿½ï¿½
//	HAL_ADC_PollForConversion(&hadc1,100);  
//  
//	key_driver_init();
//	adc_driver_init();
//  
////  beep_SetFreq(1000);
////  beep_on(mode1);
//  
	HAL_TIM_Base_Start_IT(&htim17); //1ms
	printf("OK!\r\n");
	
	HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_1);   //¶æ»ú
	HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_2);

//	unsigned char i=0;
//	LCD_Init();
//	LCD_Fill(0,0,lcddev.width,lcddev.height,BLACK);
//	LCD_ShowString(18,30,"LuatOS",WHITE,BLUE,0);
//	lv_init();
//	lv_port_disp_init();
//	lv_example_led_1();

	
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  { 
//	  printf("1\r");
//	  lv_task_handler();
//	  beep_run();
//	  vofa_start();
	  
//		main_test(); 		//²âÊÔÖ÷½çÃæ
	  
//	  HAL_GPIO_WritePin(M_EN_GPIO_Port, M_EN_Pin, GPIO_PIN_SET);
//	  HAL_GPIO_WritePin(M_DIR_GPIO_Port, M_DIR_Pin, GPIO_PIN_SET);
//	  GPIO_OutputPulses(3200, 1000); //  (1kHz)
////	  printf("Forware\r\n");
//	  
//	  HAL_Delay(1000);
//	  
////	  HAL_GPIO_WritePin(M_EN_GPIO_Port, M_EN_Pin, GPIO_PIN_SET);
//	  HAL_GPIO_WritePin(M_DIR_GPIO_Port, M_DIR_Pin, GPIO_PIN_RESET);
//	  GPIO_OutputPulses(1600, 1000); //  (1kHz)
////	  printf("Hard\r\n");
//	  HAL_Delay(1000);
	  
	  Servo_SetAngle(servo1, angle_val);
	  Servo_SetAngle(servo2, angle_val);
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1_BOOST);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = RCC_PLLM_DIV5;
  RCC_OscInitStruct.PLL.PLLN = 68;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */


/**
 * LVGL×¨ÒµµãµÆDemo
 */
//void lv_example_led_1(void)
//{
//    /*Create a LED and switch it OFF*/
//    lv_obj_t * led1  = lv_led_create(lv_scr_act());
//    lv_obj_align(led1, LV_ALIGN_CENTER, -80, 0);
//    lv_led_off(led1);
// 
//    /*Copy the previous LED and set a brightness*/
//    lv_obj_t * led2  = lv_led_create(lv_scr_act());
//    lv_obj_align(led2, LV_ALIGN_CENTER, 0, 0);
//    lv_led_set_brightness(led2, 150);
//    lv_led_set_color(led2, lv_palette_main(LV_PALETTE_RED));
// 
//    /*Copy the previous LED and switch it ON*/
//    lv_obj_t * led3  = lv_led_create(lv_scr_act());
//    lv_obj_align(led3, LV_ALIGN_CENTER, 80, 0);
//    lv_led_on(led3);
//}

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

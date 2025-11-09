/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32g4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define MB1_Pin GPIO_PIN_13
#define MB1_GPIO_Port GPIOC
#define PWR_AD_Pin GPIO_PIN_0
#define PWR_AD_GPIO_Port GPIOA
#define KEY1_Pin GPIO_PIN_1
#define KEY1_GPIO_Port GPIOA
#define KEY2_Pin GPIO_PIN_2
#define KEY2_GPIO_Port GPIOA
#define KEY3_Pin GPIO_PIN_3
#define KEY3_GPIO_Port GPIOA
#define LCD_SCK_Pin GPIO_PIN_5
#define LCD_SCK_GPIO_Port GPIOA
#define LCD_SDA_Pin GPIO_PIN_7
#define LCD_SDA_GPIO_Port GPIOA
#define LCD_BLK_Pin GPIO_PIN_4
#define LCD_BLK_GPIO_Port GPIOC
#define LCD_RST_Pin GPIO_PIN_0
#define LCD_RST_GPIO_Port GPIOB
#define LCD_DC_Pin GPIO_PIN_1
#define LCD_DC_GPIO_Port GPIOB
#define LCD_CS_Pin GPIO_PIN_2
#define LCD_CS_GPIO_Port GPIOB
#define M_EN_Pin GPIO_PIN_11
#define M_EN_GPIO_Port GPIOB
#define M_STP_Pin GPIO_PIN_12
#define M_STP_GPIO_Port GPIOB
#define M_DIR_Pin GPIO_PIN_13
#define M_DIR_GPIO_Port GPIOB
#define WATER1_Pin GPIO_PIN_14
#define WATER1_GPIO_Port GPIOB
#define WATER2_Pin GPIO_PIN_15
#define WATER2_GPIO_Port GPIOB
#define OUT1_Pin GPIO_PIN_6
#define OUT1_GPIO_Port GPIOC
#define MA1_Pin GPIO_PIN_8
#define MA1_GPIO_Port GPIOA
#define servo1_Pin GPIO_PIN_11
#define servo1_GPIO_Port GPIOA
#define servo2_Pin GPIO_PIN_12
#define servo2_GPIO_Port GPIOA
#define BEEP_Pin GPIO_PIN_15
#define BEEP_GPIO_Port GPIOA
#define MB2_Pin GPIO_PIN_5
#define MB2_GPIO_Port GPIOB
#define OUT2_Pin GPIO_PIN_7
#define OUT2_GPIO_Port GPIOB
#define MA2_Pin GPIO_PIN_9
#define MA2_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

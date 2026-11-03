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

#include <stdio.h>

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

extern uint32_t shellTick;

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define M_DIR2_Pin GPIO_PIN_13
#define M_DIR2_GPIO_Port GPIOC
#define M_EN2_Pin GPIO_PIN_14
#define M_EN2_GPIO_Port GPIOC
#define DLP1_Pin GPIO_PIN_0
#define DLP1_GPIO_Port GPIOA
#define DLP2_Pin GPIO_PIN_1
#define DLP2_GPIO_Port GPIOA
#define DLP3_Pin GPIO_PIN_2
#define DLP3_GPIO_Port GPIOA
#define DLP4_Pin GPIO_PIN_3
#define DLP4_GPIO_Port GPIOA
#define TEMP_ADC_Pin GPIO_PIN_4
#define TEMP_ADC_GPIO_Port GPIOA
#define Hot_Pin GPIO_PIN_5
#define Hot_GPIO_Port GPIOA
#define DLP5_Pin GPIO_PIN_6
#define DLP5_GPIO_Port GPIOA
#define DLP6_Pin GPIO_PIN_7
#define DLP6_GPIO_Port GPIOA
#define DLP7_Pin GPIO_PIN_0
#define DLP7_GPIO_Port GPIOB
#define DLP8_Pin GPIO_PIN_1
#define DLP8_GPIO_Port GPIOB
#define AIN1_Pin GPIO_PIN_10
#define AIN1_GPIO_Port GPIOB
#define AIN2_Pin GPIO_PIN_11
#define AIN2_GPIO_Port GPIOB
#define M_DIR1_Pin GPIO_PIN_12
#define M_DIR1_GPIO_Port GPIOB
#define M_EN1_Pin GPIO_PIN_13
#define M_EN1_GPIO_Port GPIOB
#define PWMA_Pin GPIO_PIN_14
#define PWMA_GPIO_Port GPIOB
#define PWMB_Pin GPIO_PIN_15
#define PWMB_GPIO_Port GPIOB
#define M_STP1_Pin GPIO_PIN_6
#define M_STP1_GPIO_Port GPIOC
#define BIN1_Pin GPIO_PIN_8
#define BIN1_GPIO_Port GPIOA
#define BIN2_Pin GPIO_PIN_11
#define BIN2_GPIO_Port GPIOA
#define BEEP_Pin GPIO_PIN_12
#define BEEP_GPIO_Port GPIOA
#define LCD_TX_Pin GPIO_PIN_10
#define LCD_TX_GPIO_Port GPIOC
#define LCD_RX_Pin GPIO_PIN_11
#define LCD_RX_GPIO_Port GPIOC
#define ESP_TX_Pin GPIO_PIN_3
#define ESP_TX_GPIO_Port GPIOB
#define ESP_RX_Pin GPIO_PIN_4
#define ESP_RX_GPIO_Port GPIOB
#define W1_Pin GPIO_PIN_6
#define W1_GPIO_Port GPIOB
#define W2_Pin GPIO_PIN_7
#define W2_GPIO_Port GPIOB
#define M_STP2_Pin GPIO_PIN_9
#define M_STP2_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */
int fputc(int ch,FILE *f);
int fgetc(FILE *f);

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

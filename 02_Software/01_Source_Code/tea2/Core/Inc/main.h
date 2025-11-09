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
#define L_PH_Pin GPIO_PIN_13
#define L_PH_GPIO_Port GPIOC
#define R_PH_Pin GPIO_PIN_14
#define R_PH_GPIO_Port GPIOC
#define MOTOR_EN_Pin GPIO_PIN_15
#define MOTOR_EN_GPIO_Port GPIOC
#define KEY1_Pin GPIO_PIN_1
#define KEY1_GPIO_Port GPIOA
#define KEY2_Pin GPIO_PIN_2
#define KEY2_GPIO_Port GPIOA
#define KEY3_Pin GPIO_PIN_3
#define KEY3_GPIO_Port GPIOA
#define SCL_Pin GPIO_PIN_5
#define SCL_GPIO_Port GPIOA
#define SDA_Pin GPIO_PIN_7
#define SDA_GPIO_Port GPIOA
#define BLK_Pin GPIO_PIN_4
#define BLK_GPIO_Port GPIOC
#define RES_Pin GPIO_PIN_0
#define RES_GPIO_Port GPIOB
#define DC_Pin GPIO_PIN_1
#define DC_GPIO_Port GPIOB
#define CS_Pin GPIO_PIN_2
#define CS_GPIO_Port GPIOB
#define M_DIR_Pin GPIO_PIN_12
#define M_DIR_GPIO_Port GPIOB
#define M_EN_Pin GPIO_PIN_13
#define M_EN_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */
int fputc(int ch,FILE *f);
int fgetc(FILE *f);

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

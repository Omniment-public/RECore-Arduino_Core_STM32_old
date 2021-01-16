/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
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
#include "stm32f0xx_hal.h"

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

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define VBATIN_Pin GPIO_PIN_0
#define VBATIN_GPIO_Port GPIOA
#define IO6_Pin GPIO_PIN_1
#define IO6_GPIO_Port GPIOA
#define IO5_Pin GPIO_PIN_2
#define IO5_GPIO_Port GPIOA
#define IO4_Pin GPIO_PIN_3
#define IO4_GPIO_Port GPIOA
#define M_VREF_Pin GPIO_PIN_4
#define M_VREF_GPIO_Port GPIOA
#define IO3_Pin GPIO_PIN_5
#define IO3_GPIO_Port GPIOA
#define IO2_Pin GPIO_PIN_6
#define IO2_GPIO_Port GPIOA
#define IO1_Pin GPIO_PIN_7
#define IO1_GPIO_Port GPIOA
#define BIN1_2_Pin GPIO_PIN_0
#define BIN1_2_GPIO_Port GPIOB
#define BIN2_2_Pin GPIO_PIN_1
#define BIN2_2_GPIO_Port GPIOB
#define IO7_Pin GPIO_PIN_2
#define IO7_GPIO_Port GPIOB
#define BIN1_1_Pin GPIO_PIN_10
#define BIN1_1_GPIO_Port GPIOB
#define BIN2_1_Pin GPIO_PIN_11
#define BIN2_1_GPIO_Port GPIOB
#define IO0_Pin GPIO_PIN_8
#define IO0_GPIO_Port GPIOA
#define LED_Pin GPIO_PIN_11
#define LED_GPIO_Port GPIOA
#define SW_Pin GPIO_PIN_12
#define SW_GPIO_Port GPIOA
#define AIN1_1_Pin GPIO_PIN_15
#define AIN1_1_GPIO_Port GPIOA
#define AIN2_1_Pin GPIO_PIN_3
#define AIN2_1_GPIO_Port GPIOB
#define AIN1_2_Pin GPIO_PIN_4
#define AIN1_2_GPIO_Port GPIOB
#define AIN2_2_Pin GPIO_PIN_5
#define AIN2_2_GPIO_Port GPIOB
#define M_FAULT_Pin GPIO_PIN_6
#define M_FAULT_GPIO_Port GPIOB
#define M_SLEEP_Pin GPIO_PIN_7
#define M_SLEEP_GPIO_Port GPIOB
#define IO8_Pin GPIO_PIN_8
#define IO8_GPIO_Port GPIOB
#define IO9_Pin GPIO_PIN_9
#define IO9_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
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
#define CS_V1_Pin GPIO_PIN_14
#define CS_V1_GPIO_Port GPIOC
#define EN_V1_Pin GPIO_PIN_15
#define EN_V1_GPIO_Port GPIOC
#define B3_V1_Pin GPIO_PIN_0
#define B3_V1_GPIO_Port GPIOC
#define B2_V1_Pin GPIO_PIN_1
#define B2_V1_GPIO_Port GPIOC
#define B1_V1_Pin GPIO_PIN_2
#define B1_V1_GPIO_Port GPIOC
#define B0_V1_Pin GPIO_PIN_3
#define B0_V1_GPIO_Port GPIOC
#define A3_V1_Pin GPIO_PIN_0
#define A3_V1_GPIO_Port GPIOA
#define A2_V1_Pin GPIO_PIN_1
#define A2_V1_GPIO_Port GPIOA
#define A1_V1_Pin GPIO_PIN_2
#define A1_V1_GPIO_Port GPIOA
#define A0_V1_Pin GPIO_PIN_3
#define A0_V1_GPIO_Port GPIOA
#define TRG_I1_Pin GPIO_PIN_0
#define TRG_I1_GPIO_Port GPIOB
#define RST_I1_Pin GPIO_PIN_1
#define RST_I1_GPIO_Port GPIOB
#define CS_I1_Pin GPIO_PIN_2
#define CS_I1_GPIO_Port GPIOB
#define EN_I1_Pin GPIO_PIN_7
#define EN_I1_GPIO_Port GPIOE
#define B3_I1_Pin GPIO_PIN_8
#define B3_I1_GPIO_Port GPIOE
#define B2_I1_Pin GPIO_PIN_9
#define B2_I1_GPIO_Port GPIOE
#define B1_I1_Pin GPIO_PIN_10
#define B1_I1_GPIO_Port GPIOE
#define B0_I1_Pin GPIO_PIN_11
#define B0_I1_GPIO_Port GPIOE
#define A3_I1_Pin GPIO_PIN_12
#define A3_I1_GPIO_Port GPIOE
#define A2_I1_Pin GPIO_PIN_13
#define A2_I1_GPIO_Port GPIOE
#define A1_I1_Pin GPIO_PIN_14
#define A1_I1_GPIO_Port GPIOE
#define A0_I1_Pin GPIO_PIN_15
#define A0_I1_GPIO_Port GPIOE

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

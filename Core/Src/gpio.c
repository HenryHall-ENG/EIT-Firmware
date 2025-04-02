/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    gpio.c
  * @brief   This file provides code for the configuration
  *          of all used GPIO pins.
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

/* Includes ------------------------------------------------------------------*/
#include "gpio.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/*----------------------------------------------------------------------------*/
/* Configure GPIO                                                             */
/*----------------------------------------------------------------------------*/
/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/** Configure pins as
        * Analog
        * Input
        * Output
        * EVENT_OUT
        * EXTI
*/
void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOE_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, CS_V1_Pin|GPIO_PIN_8|GPIO_PIN_9, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, EN_V1_Pin|B3_V1_Pin|B2_V1_Pin|B1_V1_Pin
                          |B0_V1_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, A3_V1_Pin|A2_V1_Pin|A1_V1_Pin|A0_V1_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, TRG_I1_Pin|RST_I1_Pin|CS_I1_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOE, EN_I1_Pin|B3_I1_Pin|B2_I1_Pin|B1_I1_Pin
                          |B0_I1_Pin|A3_I1_Pin|A2_I1_Pin|A1_I1_Pin
                          |A0_I1_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : CS_V1_Pin PC8 PC9 */
  GPIO_InitStruct.Pin = CS_V1_Pin|GPIO_PIN_8|GPIO_PIN_9;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : EN_V1_Pin B3_V1_Pin B2_V1_Pin B1_V1_Pin
                           B0_V1_Pin */
  GPIO_InitStruct.Pin = EN_V1_Pin|B3_V1_Pin|B2_V1_Pin|B1_V1_Pin
                          |B0_V1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : A3_V1_Pin A2_V1_Pin A1_V1_Pin A0_V1_Pin */
  GPIO_InitStruct.Pin = A3_V1_Pin|A2_V1_Pin|A1_V1_Pin|A0_V1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : TRG_I1_Pin RST_I1_Pin CS_I1_Pin */
  GPIO_InitStruct.Pin = TRG_I1_Pin|RST_I1_Pin|CS_I1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : EN_I1_Pin B3_I1_Pin B2_I1_Pin B1_I1_Pin
                           B0_I1_Pin A3_I1_Pin A2_I1_Pin A1_I1_Pin
                           A0_I1_Pin */
  GPIO_InitStruct.Pin = EN_I1_Pin|B3_I1_Pin|B2_I1_Pin|B1_I1_Pin
                          |B0_I1_Pin|A3_I1_Pin|A2_I1_Pin|A1_I1_Pin
                          |A0_I1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

}

/* USER CODE BEGIN 2 */

/* USER CODE END 2 */

/*
 * Sense.c
 *
 *  Created on: Feb 28, 2025
 *      Author: hwh40
 */
#include "Sense.h"
#include "tim.h"
#include "dma.h"
#include "usb_device.h"
#include "usbd_cdc_if.h"


uint16_t ADS7057_Read(void) {
	uint16_t rx_buff[2] = {0};


	while (SPI1->SR & SPI_SR_RXNE) {
	    (void)SPI1->DR; // Dummy read
	}


	GPIOC->BSRR = (uint32_t)(CS_V1_Pin << 16);

	SPI1->DR = 0;
	SPI1->DR = 0;

	while (!(SPI1->SR & SPI_SR_RXNE));

	rx_buff[0] = SPI1->DR;
	rx_buff[1] = SPI1->DR;

	GPIOC->BSRR = (uint32_t)CS_V1_Pin;
	uint16_t result = (rx_buff[0] << 7) | (rx_buff[1] >> 2);

	return result;
}

float get_Mag(const uint16_t *samples, uint32_t freq){
	int k = (int)roundf(freq * BUFFER_SIZE / FS);

	float w = (2.0 * 3.14159 * k) / BUFFER_SIZE;
	float cw = cos(w);
	float sw = sin(w);
	float c = 2 * cw;

	float z1 = 0, z2 = 0;
    float z0;

    // Goertzel filter loop
    for (size_t i = 0; i < BUFFER_SIZE; i++) {
        z0 = (float)(samples[i] << 1) + c * z1 - z2;
        z2 = z1;
        z1 = z0;
    }
    // Compute magnitude
    float I = cw*z1 - z2;
	float Q = sw*z1;
	float magnitude = sqrt(I*I +Q*Q);
    return magnitude / (BUFFER_SIZE);
}

void collect_Buffer(uint16_t *rx) {
	  uint16_t zero[BUFFER_SIZE] = {0};
	  uint32_t high[BUFFER_SIZE] = {0};
	  uint32_t low[BUFFER_SIZE] = {0};
	  for (size_t i = 0; i<BUFFER_SIZE; i++) {
		  high[i] = CS_V1_Pin;
		  low[i] = CS_V1_Pin << 16;
	  }

	  __HAL_RCC_SPI1_CLK_ENABLE();
	  SPI1->CR1 |= SPI_CR1_SPE;

	  htim2.Instance->CCR1 = 80; //CS High
	  htim2.Instance->CCR2 = 100; //CS Low
	  htim2.Instance->CCR3 = 110; //Read RX
	  htim2.Instance->ARR = (uint32_t)((HAL_RCC_GetSysClockFreq() / FS)); // 160

//	  GPIOC->BSRR = (uint32_t)(CS_V1_Pin << 16);

	  HAL_DMA_Start(htim2.hdma[TIM_DMA_ID_UPDATE], (uint32_t)&zero[0], (uint32_t)&SPI1->DR, BUFFER_SIZE);
	  HAL_DMA_Start(htim2.hdma[TIM_DMA_ID_CC1], (uint32_t)&high[0], (uint32_t)&GPIOC->BSRR, BUFFER_SIZE);
	  HAL_DMA_Start(htim2.hdma[TIM_DMA_ID_CC2], (uint32_t)&low[0], (uint32_t)&GPIOC->BSRR, BUFFER_SIZE);
	  HAL_DMA_Start(htim2.hdma[TIM_DMA_ID_CC3], (uint32_t)&SPI1->DR, (uint32_t)&rx[0], BUFFER_SIZE);

	  __HAL_TIM_ENABLE_DMA(&htim2, TIM_DMA_UPDATE);
	  __HAL_TIM_ENABLE_DMA(&htim2, TIM_DMA_CC1);
	  __HAL_TIM_ENABLE_DMA(&htim2, TIM_DMA_CC2);
	  __HAL_TIM_ENABLE_DMA(&htim2, TIM_DMA_CC3);

	  HAL_TIM_Base_Start(&htim2);

	  while(__HAL_DMA_GET_FLAG(htim2.hdma[TIM_DMA_ID_CC3], DMA_FLAG_TC3) == RESET);


	  HAL_TIM_Base_Stop(&htim2);

	  HAL_DMA_Abort(htim2.hdma[TIM_DMA_ID_UPDATE]);
	  HAL_DMA_Abort(htim2.hdma[TIM_DMA_ID_CC1]);
	  HAL_DMA_Abort(htim2.hdma[TIM_DMA_ID_CC2]);
	  HAL_DMA_Abort(htim2.hdma[TIM_DMA_ID_CC3]);

	  GPIOC->BSRR = (uint32_t)(CS_V1_Pin);
}




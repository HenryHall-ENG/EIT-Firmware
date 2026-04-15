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

float get_Mag(const int16_t *samples, uint32_t freq){
	int k = (int)roundf(freq * (BUFFER_SIZE-IGNORE) / FS);

	float w = (2.0 * 3.14159 * k) / (BUFFER_SIZE-IGNORE);
	float cw = cos(w);
	float sw = sin(w);
	float c = 2 * cw;

	float z1 = 0, z2 = 0;
    float z0;

    // Goertzel filter loop
    for (size_t i = IGNORE; i < BUFFER_SIZE; i++) {
        z0 = (float)(samples[i] << 1) + c * z1 - z2;
        z2 = z1;
        z1 = z0;
    }
    // Compute magnitude
    float I = cw*z1 - z2;
	float Q = sw*z1;
	float magnitude = sqrt(I*I +Q*Q);
    return magnitude / (BUFFER_SIZE-IGNORE);
}

void difference(const int16_t * samples, int32_t * diff) {

	for (size_t i = 0; i < BUFFER_SIZE - 1; i ++) {
		diff[i] = samples[i+1] - samples[i];
	}

}

int16_t sortMedian(int16_t * window) {
	for (size_t j = 1; j < 5; ++j) {
		int16_t key = window[j];
		size_t k = j;
		while (k > 0 && window[k - 1] > key) {
			window[k] = window[k - 1];
			--k;
		}
		window[k] = key;
	}

	return window[2];
}

void median(const int16_t * samples, int16_t * median) {

	for (size_t i = 2; i < BUFFER_SIZE - 2; i ++) {
		int16_t window[5] = { samples[i - 2], samples[i - 1], samples[i], samples[i + 1], samples[i + 2] };
		median[i] = sortMedian(window);
	}


	int16_t windowInitial1[5] = {samples[3],samples[2],samples[1],samples[0],samples[0]};
	int16_t windowInitial2[5] = {samples[2],samples[1],samples[0],samples[0],samples[1]};


	int16_t windowFinal1[5] = {samples[BUFFER_SIZE - 2],samples[BUFFER_SIZE - 1],samples[BUFFER_SIZE - 1],samples[BUFFER_SIZE - 2],samples[BUFFER_SIZE - 3]};
	int16_t windowFinal2[5] = {samples[BUFFER_SIZE - 1],samples[BUFFER_SIZE - 1],samples[BUFFER_SIZE - 2],samples[BUFFER_SIZE - 3],samples[BUFFER_SIZE - 4]};

	median[0] = sortMedian(windowInitial1);
	median[1] = sortMedian(windowInitial2);
	median[BUFFER_SIZE - 2] = sortMedian(windowFinal1);
	median[BUFFER_SIZE - 1] = sortMedian(windowFinal2);
}

float get_MagBin(const int16_t * samples, uint8_t idx) {
	int32_t diffOriginal[BUFFER_SIZE - 1] = {0};
	int32_t diffMedian[BUFFER_SIZE - 1] = {0};
	int16_t medianFilter[BUFFER_SIZE] = {0};

	difference(samples, diffOriginal);
	median(samples, medianFilter);
	difference(medianFilter, diffMedian);

	int32_t min = 9999;
	int32_t min2 = 9999;
	int32_t min_idx = 0;
	int32_t min2_idx = 0;

	for (size_t i = 0; i < BUFFER_SIZE - 1; i++) {
		if (diffMedian[i] < min) {
			min = diffMedian[i];
			min_idx = i;
		}
		if (diffMedian[i] > min && diffMedian[i] < min2) {
			min2 = diffMedian[i];
			min_idx = i;
		}
	}

	int32_t magnitude = -1.0 * diffOriginal[min_idx+idx];
	if (magnitude < 0) {
		magnitude = 0;
	}
	return magnitude;
}

void collect_Buffer(int16_t *rx, AD9102_t* ad9102) {
	  uint16_t zero[BUFFER_SIZE] = {0};
	  uint32_t high[BUFFER_SIZE] = {0};
	  uint32_t low[BUFFER_SIZE] = {0};
	  for (size_t i = 0; i<BUFFER_SIZE; i++) {
		  high[i] = CS_V1_Pin;
		  low[i] = CS_V1_Pin << 16;
	  }

	  __HAL_RCC_SPI1_CLK_ENABLE();
	  SPI1->CR1 |= SPI_CR1_SPE;

	  htim2.Instance->CCR1 = 36; //CS High
	  htim2.Instance->CCR2 = 48; //CS Low
	  htim2.Instance->CCR3 = 48; //Read RX
	  htim2.Instance->ARR = (uint32_t)((HAL_RCC_GetSysClockFreq() / FS));

	  GPIOC->BSRR = (uint32_t)(CS_V1_Pin << 16);

	  HAL_DMA_Start(htim2.hdma[TIM_DMA_ID_UPDATE], (uint32_t)&zero[0], (uint32_t)&SPI1->DR, BUFFER_SIZE);
	  HAL_DMA_Start(htim2.hdma[TIM_DMA_ID_CC1], (uint32_t)&high[0], (uint32_t)&GPIOC->BSRR, BUFFER_SIZE);
	  HAL_DMA_Start(htim2.hdma[TIM_DMA_ID_CC2], (uint32_t)&low[0], (uint32_t)&GPIOC->BSRR, BUFFER_SIZE);
	  HAL_DMA_Start(htim2.hdma[TIM_DMA_ID_CC3], (uint32_t)&SPI1->DR, (uint32_t)&rx[0], BUFFER_SIZE);

	  __HAL_TIM_ENABLE_DMA(&htim2, TIM_DMA_UPDATE);
	  __HAL_TIM_ENABLE_DMA(&htim2, TIM_DMA_CC1);
	  __HAL_TIM_ENABLE_DMA(&htim2, TIM_DMA_CC2);
	  __HAL_TIM_ENABLE_DMA(&htim2, TIM_DMA_CC3);




	  HAL_TIM_Base_Start(&htim2);
}

void waitBuffer(void) {
	  while(__HAL_DMA_GET_FLAG(htim2.hdma[TIM_DMA_ID_CC3], DMA_FLAG_TC3) == RESET);


	  HAL_TIM_Base_Stop(&htim2);



	  HAL_DMA_Abort(htim2.hdma[TIM_DMA_ID_UPDATE]);
	  HAL_DMA_Abort(htim2.hdma[TIM_DMA_ID_CC1]);
	  HAL_DMA_Abort(htim2.hdma[TIM_DMA_ID_CC2]);
	  HAL_DMA_Abort(htim2.hdma[TIM_DMA_ID_CC3]);

	  GPIOC->BSRR = (uint32_t)(CS_V1_Pin);
}




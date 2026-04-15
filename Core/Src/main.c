/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
#include "main.h"
#include "dma.h"
#include "spi.h"
#include "tim.h"
#include "usb_device.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "usbd_cdc_if.h"
#include "Mux.h"
#include "Sense.h"
#include "AD9102.h"
#include "stm32g4xx_hal_spi.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define AD9102_CLK 50e6
#define F_TARG 50e3
#define F_BIN 100e3

#define N_EL 16


/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
mux_t sense_V1;
mux_t stim_I1;
AD9102_t AD9102;
uint32_t gl_ticks = 0;
int16_t lut[4000] = {0};

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

void test_stim(void);
void get_frameSS(void);
void get_frameTR(void);
void test_bin(void);
void sendBuffer(uint8_t *adcBuffer, uint8_t packetType, uint16_t dataLength);
void getXframes(uint32_t Xframes);
void getXframesTdelay(uint32_t Xframes, uint32_t Tdelay);
void get_frameAlternate(bool is_even);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */



/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

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
  MX_DMA_Init();
  MX_SPI1_Init();
  MX_TIM2_Init();
  MX_USB_Device_Init();
  /* USER CODE BEGIN 2 */

  initAD9102(&AD9102, GPIOB, TRG_I1_Pin, RST_I1_Pin, CS_I1_Pin, AD9102_CLK);

  mux_Init(&sense_V1,GPIOA, A0_V1_Pin, A1_V1_Pin, A2_V1_Pin, A3_V1_Pin,
			GPIOC, B0_V1_Pin, B1_V1_Pin, B2_V1_Pin, B3_V1_Pin,
			GPIOC, EN_V1_Pin);
  mux_Init(&stim_I1 ,GPIOE, A0_I1_Pin, A1_I1_Pin, A2_I1_Pin, A3_I1_Pin,
  			GPIOE, B0_I1_Pin, B1_I1_Pin, B2_I1_Pin, B3_I1_Pin,
  			GPIOE, EN_I1_Pin);


  HAL_Delay(1000);

  if (SS == 1) {
	  init_DDS(&AD9102, F_TARG);

  } else {
	  init_Chirp(&AD9102, 10e3,100e3,1e3);
  }


//
  int16_t maxVal = 4000;
//
//  uint32_t freqStep = AD9102_CLK/16;
//  uint32_t N = round(freqStep / F_BIN);
//  uint8_t binaryWord = 0b10; // MSB first
//  uint8_t numBits = 2;
//  uint32_t delay = 2000;
//
//
//
//  for (uint8_t bit = 0; bit < numBits; bit++) {
//      // Extract each bit from MSB to LSB
//      uint8_t value = (binaryWord >> (numBits - bit - 1)) & 0x1;
//
//      for (uint32_t i = 0; i < N; i++) {
//          uint32_t index = bit * N + i + delay;
//          if (value) {
//              lut[index] = maxVal;
//          } else {
//        	  lut[index] = -1 * maxVal;
//          }
//      }
//  }


  uint32_t N = 4000;

  for (int i = 0; i < N; i++) {
      // Generate full-scale 14-bit signed noise: -8191 to +8191
	  lut[i] = (rand() % 16383);
  }

//  init_SRAM(&AD9102, lut, N);

  HAL_Delay(5000);

  uint32_t idx = 0;
  char buffer[32];  // enough for 5 digits + null terminator


  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
//	  test_stim();
	  if (SS == 1) {
		  get_frameSS();
//		  getXframesTdelay(250,60);

//		  get_frameTR();
//		  HAL_Delay(1000);
//		  test_stim();
//		  getXframesTdelay(10, 10);
	  } else {
		  get_frameTR();
	  }


//	  if (idx % 2 == 0) {
//		  get_frameAlternate(true);
//
//	  } else {
//		  get_frameAlternate(false);
//
//	  }
//	  idx++;

//	  test_bin();
//	  getXframesTdelay(10, 10);
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
  HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_HSI48;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.HSI48State = RCC_HSI48_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = RCC_PLLM_DIV1;
  RCC_OscInitStruct.PLL.PLLN = 15;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV4;
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

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */



void test_stim(void) {
	mux_SetMuxPos(&stim_I1,1);
	mux_SetMuxNeg(&stim_I1,2);
	mux_Enable(&stim_I1);

	mux_SetMuxPos(&sense_V1, 3);
	mux_SetMuxNeg(&sense_V1, 4);
	mux_Enable(&sense_V1);

	enableOut(&AD9102);
	HAL_Delay(10);
	disableOut(&AD9102);

	mux_Disable(&stim_I1);
	mux_Disable(&sense_V1);
	HAL_Delay(10);
}


void test_bin(void) {
	const uint32_t num_Meas = N_EL * N_EL - N_EL * 3;
	float measurements[num_Meas];
	uint32_t idx = 0;

	for (size_t i = 1; i < (N_EL + 1); i++) {
		//	uint8_t stim1 = 1;
		//	uint8_t stim2 = 2;
		uint8_t stim1 = i;
		uint8_t stim2 = (i < 16) ? (i + 1) : 1;

		mux_SetMuxPos(&stim_I1, stim1);
		mux_SetMuxNeg(&stim_I1, stim2);
		mux_Enable(&stim_I1);

		for (size_t j = 1; j < (N_EL + 1); j++) {
	//	size_t j = 5;
			uint8_t sense1 = j;
			uint8_t sense2 = (j < 16) ? (j + 1) : 1;

			if (stim1 != sense1 && stim1 != sense2 && stim2 != sense1) {
				int16_t adcBuffer[BUFFER_SIZE] = {0};


				mux_SetMuxPos(&sense_V1, sense1);
				mux_SetMuxNeg(&sense_V1, sense2);
				mux_Enable(&sense_V1);
				HAL_Delay(1);

				enableOut(&AD9102);

	//			HAL_Delay(1);

				collect_Buffer(adcBuffer,&AD9102);

				disableOut(&AD9102);

				mux_Disable(&sense_V1);

				float mag = get_MagBin(adcBuffer, 0);
				measurements[idx] = mag;
				idx++;
				sendBuffer((uint8_t*)adcBuffer, 0x01, BUFFER_SIZE);
			}
		}
		mux_Disable(&stim_I1);
	}


//	sendBuffer((uint8_t*)measurements, 0x02, 208);
//	HAL_Delay(1000);
}

void get_frameTR(void) {
	int16_t adcBuffer[BUFFER_SIZE] = {0};
	size_t i = 1;
	size_t j = 3;
//	for (size_t i = 1; i < (N_EL + 1); i++) {
		uint8_t stim1 = i;
		uint8_t stim2 = (i < 16) ? (i + 1) : 1;

		mux_SetMuxPos(&stim_I1, stim1);
		mux_SetMuxNeg(&stim_I1, stim2);
		mux_Enable(&stim_I1);

//		for (size_t j = 1; j < (N_EL + 1); j++) {
			uint8_t sense1 = j;
			uint8_t sense2 = (j < 16) ? (j + 1) : 1;

			if (stim1 != sense1 && stim1 != sense2 && stim2 != sense1) {
				mux_SetMuxPos(&sense_V1, sense1);
				mux_SetMuxNeg(&sense_V1, sense2);
				mux_Enable(&sense_V1);

				collect_Buffer(adcBuffer,&AD9102);

				enableOut(&AD9102);

				waitBuffer();

				disableOut(&AD9102);

				sendBuffer((uint8_t*)adcBuffer, 0x01, BUFFER_SIZE);

				mux_Disable(&sense_V1);
			}
//		}
		mux_Disable(&stim_I1);
//	}
}

void get_frameSS(void) {
	const uint32_t num_Meas = N_EL * N_EL - N_EL * 3;
	float measurements[num_Meas];
	uint32_t idx = 0;

	int16_t adcBuffer1[BUFFER_SIZE] = {0};
	int16_t adcBuffer2[BUFFER_SIZE] = {0};
	int16_t isFirst = 1;
	int16_t activeBuff = 0;

	for (size_t i = 1; i < (N_EL + 1); i++) {
		uint8_t stim1 = i;
		uint8_t stim2 = (i < 16) ? (i + 1) : 1;

		mux_SetMuxPos(&stim_I1, stim1);
		mux_SetMuxNeg(&stim_I1, stim2);
		mux_Enable(&stim_I1);
		enableOut(&AD9102);


		for (size_t j = 1; j < (N_EL + 1); j++) {
			uint8_t sense1 = j;
			uint8_t sense2 = (j < 16) ? (j + 1) : 1;
			if (stim1 != sense1 && stim1 != sense2 && stim2 != sense1 && stim2 != sense2) {
				mux_SetMuxPos(&sense_V1, sense1);
				mux_SetMuxNeg(&sense_V1, sense2);

				mux_Enable(&sense_V1);


				if (activeBuff == 0) {
					collect_Buffer(adcBuffer1,&AD9102);

					if (!isFirst) {
						float mag = get_Mag(adcBuffer2, F_TARG);
						measurements[idx] = mag;
						idx++;
					} else {
						isFirst = 0;
					}

					activeBuff = 1;
					waitBuffer();

					sendBuffer((uint8_t*)adcBuffer1, 0x01, BUFFER_SIZE);
				} else {
					collect_Buffer(adcBuffer2,&AD9102);
					float mag = get_Mag(adcBuffer1, F_TARG);
					measurements[idx] = mag;
					idx++;
					activeBuff = 0;
					waitBuffer();

					sendBuffer((uint8_t*)adcBuffer2, 0x01, BUFFER_SIZE);
				}




				mux_Disable(&sense_V1);

//				HAL_Delay(100);

//				float mag = get_Mag(adcBuffer, F_TARG);

			}
		}
		disableOut(&AD9102);
		mux_Disable(&stim_I1);
	}

	if (activeBuff == 0) {
		collect_Buffer(adcBuffer1,&AD9102);
		float mag = get_Mag(adcBuffer2, F_TARG);
		measurements[idx] = mag;
		idx++;
		activeBuff = 1;
		waitBuffer();
		sendBuffer((uint8_t*)adcBuffer1, 0x01, BUFFER_SIZE);
	} else {
		collect_Buffer(adcBuffer2,&AD9102);
		float mag = get_Mag(adcBuffer1, F_TARG);
		measurements[idx] = mag;
		idx++;
		waitBuffer();
		sendBuffer((uint8_t*)adcBuffer2, 0x01, BUFFER_SIZE);
		activeBuff = 0;
	}

//	sendBuffer((uint8_t*)measurements, 0x02, num_Meas);
}

void get_frameAlternate(bool is_even) {

	const uint32_t num_Meas = N_EL * N_EL - N_EL * 3;
	float measurements[num_Meas];
	uint32_t count = 0;

	int16_t adcBuffer1[BUFFER_SIZE] = {0};
	int16_t adcBuffer2[BUFFER_SIZE] = {0};
	int16_t isFirst = 1;
	int16_t activeBuff = 0;

	uint8_t stim1 = 1;
	uint8_t stim2 = 2;
	uint8_t sense1 = 3;
	uint8_t sense2 = 4;
	uint32_t idx = 1;
	uint32_t jdx = 1;



	for (size_t i = 1; i < (N_EL + 1); i++) {
		if (is_even){
			idx = 2 * i;
			stim1 = idx;
			stim2 = (idx < 16) ? (idx + 2) : 2;
		} else {
			idx = 2 * i - 1;
			stim1 = idx;
			stim2 = (idx < 15) ? (idx + 2) : 1;
		}

		mux_SetMuxPos(&stim_I1, stim1);
		mux_SetMuxNeg(&stim_I1, stim2);
		mux_Enable(&stim_I1);

		for (size_t j = 1; j < (N_EL + 1); j++) {
			if (is_even){
				jdx = 2 * j;
				sense1 = jdx;
				sense2 = (jdx < 16) ? (jdx + 2) : 2;
			} else {
				jdx = 2 * j - 1;
				sense1 = jdx;
				sense2 = (jdx < 15) ? (jdx + 2) : 1;
			}


			if (stim1 != sense1 && stim1 != sense2 && stim2 != sense1) {
//				HAL_Delay(1000);
				mux_SetMuxPos(&sense_V1, sense1);
				mux_SetMuxNeg(&sense_V1, sense2);

				mux_Enable(&sense_V1);

				enableOut(&AD9102);

				if (activeBuff == 0) {
					collect_Buffer(adcBuffer1,&AD9102);

					if (!isFirst) {
						float mag = get_Mag(adcBuffer2, F_TARG);
						measurements[count] = mag;
						count++;
					} else {
						isFirst = 0;
					}

					activeBuff = 1;
					waitBuffer();

//					sendBuffer((uint8_t*)adcBuffer1, 0x01, BUFFER_SIZE);
				} else {
					collect_Buffer(adcBuffer2,&AD9102);
					float mag = get_Mag(adcBuffer1, F_TARG);
					measurements[count] = mag;
					count++;
					activeBuff = 0;
					waitBuffer();

//					sendBuffer((uint8_t*)adcBuffer2, 0x01, BUFFER_SIZE);
				}


				disableOut(&AD9102);

				mux_Disable(&sense_V1);

//				HAL_Delay(100);

//				float mag = get_Mag(adcBuffer, F_TARG);

			}
		}
		mux_Disable(&stim_I1);
	}

	if (activeBuff == 0) {
		collect_Buffer(adcBuffer1,&AD9102);
		float mag = get_Mag(adcBuffer2, F_TARG);
		measurements[count] = mag;
		count++;
		activeBuff = 1;
		waitBuffer();
//		sendBuffer((uint8_t*)adcBuffer1, 0x01, BUFFER_SIZE);
	} else {
		collect_Buffer(adcBuffer2,&AD9102);
		float mag = get_Mag(adcBuffer1, F_TARG);
		measurements[count] = mag;
		count++;
		waitBuffer();
//		sendBuffer((uint8_t*)adcBuffer2, 0x01, BUFFER_SIZE);
		activeBuff = 0;
	}

	sendBuffer((uint8_t*)measurements, 0x02, num_Meas);

}



void sendBuffer(uint8_t *data, uint8_t packetType, uint16_t dataLength) {
	//packetType 0x01 == uint16_t 0x02 == float
	uint8_t dataLengthMSB = (dataLength >> 8) & 0xFF;  // Extract MSB
	uint8_t dataLengthLSB = dataLength & 0xFF;         // Extract LSB

    uint8_t header[5] = {0xAA, 0x55, packetType, dataLengthMSB, dataLengthLSB};
    uint8_t footer[2] = {0x55, 0xAA};

//    uint8_t *data = (uint8_t*)adcBuffer;  // Cast buffer to bytes

    // Send header
    while (CDC_Transmit_FS(header, sizeof(header)) == USBD_BUSY);
    HAL_Delay(1);

    size_t dataSize = (packetType == 0x01) ? (dataLength * 2) : (dataLength * 4);
//     Send data in 64-byte chunks
    for (size_t i = 0; i < dataSize; i += 64) {
		while (CDC_Transmit_FS(&data[i], (dataSize - i > 64) ? 64 : dataSize - i) == USBD_BUSY);
	}

    // Send footer
    while (CDC_Transmit_FS(footer, sizeof(footer))== USBD_BUSY);
}

void getXframes(uint32_t Xframes) {
	for (size_t i = 0; i < Xframes; i++) {
		get_frameSS();
	}
}

void getXframesTdelay(uint32_t Xframes, uint32_t Tdelay) {
	getXframes(Xframes);
	for (size_t i = 0; i < Tdelay; i++) {
		HAL_Delay(1000);
	}
}

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

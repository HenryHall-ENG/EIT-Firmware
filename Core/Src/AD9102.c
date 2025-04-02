/*
 * AD9102.c
 *
 *  Created on: Feb 26, 2025
 *      Author: hwh40
 */
#include "AD9102.h"

void initAD9102(AD9102_t* ad9102, GPIO_TypeDef* port, uint16_t pinTRG, uint16_t pinRST, uint16_t pinCS, uint32_t fCLK) {
	ad9102->port = port;

	ad9102->pinTRG = pinTRG;
	ad9102->pinRST = pinRST;
	ad9102->pinCS = pinCS;

	ad9102->fCLK = fCLK;
}

void WriteRegister(AD9102_t* ad9102, uint16_t address, uint16_t value) {
	__HAL_RCC_SPI1_CLK_ENABLE();

	SPI1->CR1 |= SPI_CR1_SPE;

	uint16_t rx_buff[2] = {0};

	while (SPI1->SR & SPI_SR_RXNE) {
	    (void)SPI1->DR; // Dummy read
	}

	ad9102->port->BSRR = (uint32_t)(ad9102->pinCS << 16);

	SPI1->DR = address;

	SPI1->DR = value;

	while (!(SPI1->SR & SPI_SR_RXNE)) {
		continue;
	}
	rx_buff[0] = SPI1->DR;
	rx_buff[1] = SPI1->DR;

	while (SPI1->SR & SPI_SR_BSY) {
		continue;
	}

	ad9102->port->BSRR = (uint32_t)(ad9102->pinCS);
}

uint16_t ReadRegister(AD9102_t* ad9102, uint16_t address) {
	uint16_t rx_buff[2] = {0};

	while (SPI1->SR & SPI_SR_RXNE) {
		(void)SPI1->DR; // Dummy read
	}

	ad9102->port->BSRR = (uint32_t)(ad9102->pinCS << 16);

	SPI1->DR = address | 0x8000;

	while (!(SPI1->SR & SPI_SR_RXNE)) {
		continue;
	}
	rx_buff[0] = SPI1->DR;

	SPI1->DR = 0;
	while (!(SPI1->SR & SPI_SR_RXNE)) {
		continue;
	}
	rx_buff[1] = SPI1->DR;

	while (SPI1->SR & SPI_SR_BSY) {
		continue;
	}

	ad9102->port->BSRR = (uint32_t)(ad9102->pinCS);

	return rx_buff[1];
}

uint16_t waveConfig(uint8_t PRESTORE_SEL, uint8_t WAVE_SEL) {
	//BIT 5-4: Prestored Waveform selection. 00->DC, 01->Sawtooth, 10-> Noise, 11-> DDS
	//BIT 1-0: Waveform selection. 00-> RAM, 01->Prestored, 10->prestored with start delay and pattern period, 11-> prestored with SRAM Modulation

	uint16_t wav_config_value=0x0300; //equals to 0000001100000000
	wav_config_value = wav_config_value + (PRESTORE_SEL << 4) + WAVE_SEL;
	return wav_config_value;
}

void init_DDS(AD9102_t* ad9102, uint32_t frequency) {
	HAL_GPIO_WritePin(ad9102->port, ad9102->pinRST, GPIO_PIN_RESET);
	HAL_Delay(1);
	HAL_GPIO_WritePin(ad9102->port, ad9102->pinRST, GPIO_PIN_SET);


	uint32_t tuning_word = ((uint64_t)frequency * (1 << 24)) / ad9102->fCLK;
	uint16_t MSB = (tuning_word >> 8) & 0xFFFF;  // Extract upper 16 bits
	uint16_t LSB = (tuning_word & 0x00FF) << 8;           // Extract lower 8 bits

	WriteRegister(ad9102, 0x003E, MSB);
	WriteRegister(ad9102, 0x003F, LSB);


	WriteRegister(ad9102, 0x0027, waveConfig(3,1)); //Set waveform to DDS mode no pattern

	WriteRegister(ad9102, 0x0035, 0x4000); //Set DAC Gain

    WriteRegister(ad9102, 0x001E, 0x0001); //Set Run bit
    WriteRegister(ad9102, 0x001D, 0x0001); //Set RAM update bit
}

void enableOut(AD9102_t* ad9102) {
	HAL_GPIO_WritePin(ad9102->port, ad9102->pinTRG, GPIO_PIN_RESET);
}

void disableOut(AD9102_t* ad9102) {
	HAL_GPIO_WritePin(ad9102->port, ad9102->pinTRG, GPIO_PIN_SET);
}



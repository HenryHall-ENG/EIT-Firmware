/*
 * AD9102.c
 *
 *  Created on: Feb 26, 2025
 *      Author: hwh40
 */
#include "AD9102.h"
#include "usbd_cdc_if.h"

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

//	uint16_t wav_config_value=0x0300; //equals to 0000001100000000
//	wav_config_value = wav_config_value + (PRESTORE_SEL << 4) + WAVE_SEL;
	uint16_t wav_config_value = (1<<8) + (PRESTORE_SEL << 4) + WAVE_SEL;
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

//void init_SRAM(AD9102_t* ad9102, int16_t* lut, uint32_t size) {
//	HAL_GPIO_WritePin(ad9102->port, ad9102->pinRST, GPIO_PIN_RESET);
//	HAL_Delay(1);
//	HAL_GPIO_WritePin(ad9102->port, ad9102->pinRST, GPIO_PIN_SET);
//
//	WriteRegister(ad9102, 0x001E, 0x0004); //Pat Status
//
//
//	uint16_t address = 0x6000;
//	for (size_t i = 0; i < size; i ++) {
//		WriteRegister(ad9102, address, lut[i]<<2);
//		address += 1;
//		if (address > 0x6fff) {
//			break;
//		}
//	}
//
//	WriteRegister(ad9102, 0x001E, 0x0000);
//
//
//	WriteRegister(ad9102, 0x0028, 0x0011); //CLK pre scaler by 16
//	WriteRegister(ad9102, 0x0029, (size*16));
//
//	uint16_t startAddress = 0x0000;
//	uint16_t stopAddress = address-1;
//
//	WriteRegister(ad9102, 0x005D, startAddress <<=4); //Start Address
//	WriteRegister(ad9102, 0x005E, stopAddress <<=4); //Stop Address
//
//	WriteRegister(ad9102, 0x001F, 0x0001); //Limited number of pattern periods
//	WriteRegister(ad9102, 0x002B, 0x0101); //Repeat only once
//
//	WriteRegister(ad9102, 0x0020, 0x000E);
//
//
//	WriteRegister(ad9102, 0x0027, waveConfig(0,0));
//
//
//	WriteRegister(ad9102, 0x0035, 0x4000); //Set DAC Gain
//
//    WriteRegister(ad9102, 0x001E, 0x0001); //Set Run bit
//    WriteRegister(ad9102, 0x001D, 0x0001); //Set RAM update bit
//}
//
//void init_Chirp(AD9102_t* ad9102, uint32_t f0, uint32_t f1, uint32_t df) {
//	HAL_GPIO_WritePin(ad9102->port, ad9102->pinRST, GPIO_PIN_RESET);
//	HAL_Delay(1);
//	HAL_GPIO_WritePin(ad9102->port, ad9102->pinRST, GPIO_PIN_SET);
//
//	WriteRegister(ad9102, 0x001E, 0x0004);
//
//	//write to SRAM
//	uint32_t N = (f1-f0)/df+1;
//
//	uint16_t address = 0x6000;
//	for (size_t i = 0; i < N; i++) {
//		uint32_t frequency = f0 + i*df;
//		uint32_t tuning_word = ((uint64_t)frequency * (1 << 24)) / ad9102->fCLK;
//
//		uint16_t MSB = (tuning_word >> 10) & 0x3FFF;
//
//		WriteRegister(ad9102, address, MSB<<2);
//		address += 1;
//		if (address > 0x6fff) {
//			break;
//		}
//
//	}
//
//
//	WriteRegister(ad9102, 0x001E, 0x0000);
//
//
//	uint16_t startAddress = 0x0000;
//	uint16_t stopAddress = address-1;
//
//	WriteRegister(ad9102, 0x005D, startAddress <<=4); //Start Address
//	WriteRegister(ad9102, 0x005E, stopAddress <<=4); //Stop Address
//
//
//	WriteRegister(ad9102, 0x0045, 0x0005);
////	WriteRegister(ad9102, 0x0045, 0x0001);
//	WriteRegister(ad9102, 0x0047, 0x0000);
//
//
//	WriteRegister(ad9102, 0x001F, 0x0001); //Limited number of pattern periods
//	WriteRegister(ad9102, 0x002B, 0x0101); //Repeat only once
//	WriteRegister(ad9102, 0x0028, 0x0101);
//
//	uint32_t period = 0x8000;
//	uint32_t delay = 32768;
//	WriteRegister(ad9102, 0x0029, period);//Set Pattern period
//	WriteRegister(ad9102, 0x0020, delay);//Set Delay
//
//
//	WriteRegister(ad9102, 0x0027, waveConfig(3,2));
//
//	WriteRegister(ad9102, 0x0035, 0x4000); //Set DAC Gain
//
//    WriteRegister(ad9102, 0x001E, 0x0001); //Set Run bit
//    WriteRegister(ad9102, 0x001D, 0x0001); //Set RAM update bit
//}
//
//void init_PRBS(AD9102_t* ad9102) {
//	HAL_GPIO_WritePin(ad9102->port, ad9102->pinRST, GPIO_PIN_RESET);
//	HAL_Delay(1);
//	HAL_GPIO_WritePin(ad9102->port, ad9102->pinRST, GPIO_PIN_SET);
//
//
//	WriteRegister(ad9102, 0x0027,0x0322);
//
////	WriteRegister(ad9102, 0x1F, 0x0000);
//
//	uint32_t period = 0x000F;
//	WriteRegister(ad9102, 0x0028, 0x0000);
//	WriteRegister(ad9102, 0x0029, period);//Set Pattern period
//
//	uint32_t delay = 14;
//	WriteRegister(ad9102, 0x0020, delay);//Set Delay
//
//	WriteRegister(ad9102, 0x0035, 0x7FF0); //Set DAC Gain
//
//	WriteRegister(ad9102, 0x001E, 0x0001); //Set Run bit
//    WriteRegister(ad9102, 0x001D, 0x0001); //Set RAM update bit
//
////    uint16_t err = ReadRegister(ad9102,0x0060);
////    char buffer[32];  // enough for 5 digits + null terminator
////
////    sprintf(buffer, "ERR: %u\r\n", err);
////    CDC_Transmit_FS((uint8_t*)buffer, strlen(buffer));
//
//}

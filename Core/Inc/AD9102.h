/*
 * AD9102.h
 *
 *  Created on: Feb 26, 2025
 *      Author: hwh40
 */

#ifndef INC_AD9102_H_
#define INC_AD9102_H_

#include "stm32g4xx_hal.h"
#include "spi.h"
#include "usb_device.h"
#include "usbd_cdc_if.h"
#include <stdint.h>
#include <string.h>


typedef struct {
    GPIO_TypeDef* port;

    uint16_t pinTRG;
    uint16_t pinRST;
    uint16_t pinCS;
    uint32_t fCLK;

} AD9102_t;

void initAD9102(AD9102_t* ad9102, GPIO_TypeDef* port, uint16_t pinTRG, uint16_t pinRST, uint16_t pinCS, uint32_t fCLK);
void WriteRegister(AD9102_t* ad9102, uint16_t address, uint16_t value);
uint16_t ReadRegister(AD9102_t* ad9102, uint16_t address);
void init_DDS(AD9102_t* ad9102, uint32_t frequency);
uint16_t waveConfig(uint8_t PRESTORE_SEL, uint8_t WAVE_SEL);
void enableOut(AD9102_t* ad9102);
void disableOut(AD9102_t* ad9102);

#endif /* INC_AD9102_H_ */

/*
 * Mux.c
 *
 *  Created on: Feb 26, 2025
 *      Author: hwh40
 */


#include "mux.h"

/* Initialize the Mux struct */
void mux_Init(mux_t* mux, GPIO_TypeDef* portA, uint16_t pinA0, uint16_t pinA1, uint16_t pinA2, uint16_t pinA3,
              GPIO_TypeDef* portB, uint16_t pinB0, uint16_t pinB1, uint16_t pinB2, uint16_t pinB3,
              GPIO_TypeDef* portEN, uint16_t pinEN) {
    mux->portA = portA;
    mux->portB = portB;
    mux->portEN = portEN;

    mux->pinA0 = pinA0;
    mux->pinA1 = pinA1;
    mux->pinA2 = pinA2;
    mux->pinA3 = pinA3;

    mux->pinB0 = pinB0;
    mux->pinB1 = pinB1;
    mux->pinB2 = pinB2;
    mux->pinB3 = pinB3;

    mux->pinEN = pinEN;
}

/* Enable the Mux */
void mux_Enable(mux_t* mux) {
    HAL_GPIO_WritePin(mux->portEN, mux->pinEN, GPIO_PIN_SET);
}

/* Disable the Mux */
void mux_Disable(mux_t* mux) {
    HAL_GPIO_WritePin(mux->portEN, mux->pinEN, GPIO_PIN_RESET);
}

/* Set the Mux negative channel */
void mux_SetMuxNeg(mux_t* mux, uint8_t electrode) {
	uint8_t channel = 0;
	if (electrode < 9) {
		channel = electrode + 7;
	} else {
		channel = 16 - electrode;

	}

    HAL_GPIO_WritePin(mux->portB, mux->pinB0, (GPIO_PinState)(channel & 0x01));
    HAL_GPIO_WritePin(mux->portB, mux->pinB1, (GPIO_PinState)((channel >> 1) & 0x01));
    HAL_GPIO_WritePin(mux->portB, mux->pinB2, (GPIO_PinState)((channel >> 2) & 0x01));
    HAL_GPIO_WritePin(mux->portB, mux->pinB3, (GPIO_PinState)((channel >> 3) & 0x01));
}

/* Set the Mux positive channel */
void mux_SetMuxPos(mux_t* mux, uint8_t electrode) {
	uint8_t channel = 0;
	if (electrode < 9) {
		channel = electrode - 1;
	} else {
		channel = 24 - electrode;
	}
    HAL_GPIO_WritePin(mux->portA, mux->pinA0, (GPIO_PinState)(channel & 0x01));
    HAL_GPIO_WritePin(mux->portA, mux->pinA1, (GPIO_PinState)((channel >> 1) & 0x01));
    HAL_GPIO_WritePin(mux->portA, mux->pinA2, (GPIO_PinState)((channel >> 2) & 0x01));
    HAL_GPIO_WritePin(mux->portA, mux->pinA3, (GPIO_PinState)((channel >> 3) & 0x01));
}




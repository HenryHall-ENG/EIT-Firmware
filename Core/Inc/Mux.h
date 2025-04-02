/*
 * Mux.h
 *
 *  Created on: Feb 26, 2025
 *      Author: hwh40
 */

#ifndef INC_MUX_H_
#define INC_MUX_H_

#include "stm32g4xx_hal.h"
#include <stdint.h>

typedef struct {
    GPIO_TypeDef* portA;
    GPIO_TypeDef* portB;
    GPIO_TypeDef* portEN;

    uint16_t pinA0;
    uint16_t pinA1;
    uint16_t pinA2;
    uint16_t pinA3;

    uint16_t pinB0;
    uint16_t pinB1;
    uint16_t pinB2;
    uint16_t pinB3;

    uint16_t pinEN;
} mux_t;

/* Function prototypes */
void mux_Init(mux_t* mux, GPIO_TypeDef* portA, uint16_t pinA0, uint16_t pinA1, uint16_t pinA2, uint16_t pinA3,
              GPIO_TypeDef* portB, uint16_t pinB0, uint16_t pinB1, uint16_t pinB2, uint16_t pinB3,
              GPIO_TypeDef* portEN, uint16_t pinEN);

void mux_Enable(mux_t* mux);
void mux_Disable(mux_t* mux);
void mux_SetMuxPos(mux_t* mux, uint8_t electrode);
void mux_SetMuxNeg(mux_t* mux, uint8_t electrode);


#endif /* INC_MUX_H_ */

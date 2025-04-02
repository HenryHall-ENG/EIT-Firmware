/*
 * Sense.h
 *
 *  Created on: Feb 28, 2025
 *      Author: hwh40
 */

#ifndef INC_SENSE_H_
#define INC_SENSE_H_

#include "stm32g4xx_hal.h"
#include "spi.h"
#include <math.h>
#include <stdint.h>
//#include "arm_math.h"

#define BUFFER_SIZE 128
#define FS 128000


//arm_cfft_instance_f32 FFT;

uint16_t ADS7057_Read(void);
float get_Mag(const uint16_t *samples, uint32_t freq);
void collect_Buffer(uint16_t *rx);



#endif /* INC_SENSE_H_ */

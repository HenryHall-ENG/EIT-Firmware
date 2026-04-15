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
#include "AD9102.h"
#include <math.h>
#include <stdint.h>
//#include "arm_math.h"

//#define BUFFER_SIZE 512
//#define FS 2000000
#define SS 1

//#define IGNORE 100
//
//#if SS
//    #define BUFFER_SIZE 228
//    #define FS 1024000
//#else
//    #define BUFFER_SIZE 1024
//    #define FS 256000
//#endif

#define IGNORE 200

#if SS
    #define BUFFER_SIZE 512+200
    #define FS 1024000
#else
    #define BUFFER_SIZE 1024
    #define FS 256000
#endif
//arm_cfft_instance_f32 FFT;

uint16_t ADS7057_Read(void);
float get_Mag(const int16_t *samples, uint32_t freq);
void collect_Buffer(int16_t *rx, AD9102_t* ad9102);
float get_MagBin(const int16_t * samples, uint8_t idx);
void waitBuffer(void);



#endif /* INC_SENSE_H_ */

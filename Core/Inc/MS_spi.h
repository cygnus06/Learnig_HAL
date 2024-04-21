/*
 * MS_spi.h
 *
 *  Created on: Apr 8, 2024
 *      Author: Jahnavi
 */

#ifndef INC_MS_SPI_H_
#define INC_MS_SPI_H_
#include "stm32f4xx_hal.h"

// commands
#define RESET_COMMAND 0x1E
#define CS_Pin 0
#define CONVERT_D1_COMMAND  0x40
#define READ_ADC_COMMAND 0x00
#define OSR_256 0
#define PROM_READ(address)            (0xA0 | ((address) << 1))

typedef enum MS5607States{
  MS5607_STATE_FAILED,
  MS5607_STATE_READY
}MS5607StateTypeDef;

/* MS5607 PROM Data Structure */
struct promData{
  uint16_t reserved;
  uint16_t sens;
  uint16_t off;
  uint16_t tcs;
  uint16_t tco;
  uint16_t tref;
  uint16_t tempsens;
  uint16_t crc;
};

static uint8_t Pressure_OSR =  OSR_256;
static struct promData promData;
// functions

//initialize MS
MS5607StateTypeDef MS5607_init1(SPI_HandleTypeDef *hspix, uint16_t GPIO_Pin);


void MS5607PromRead1(struct promData *,SPI_HandleTypeDef *hspix);


//reading uncompensated values
uint8_t* MS5607_Readunc(SPI_HandleTypeDef *hspix);

//enable CS
void enableCS(); //GPIOB, PB0

//disable CS
void disableCS();



#endif /* INC_MS_SPI_H_ */

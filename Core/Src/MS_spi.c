/*
 * MS_spi.c
 *
 *  Created on: Apr 8, 2024
 *      Author: Jahnavi
 */


#include "MS_spi.h"
//uint8_t *reply;
#include "stdlib.h"
static uint8_t SPITransmitData;

void enableCS(){
	HAL_GPIO_WritePin(GPIOB, CS_Pin, GPIO_PIN_RESET); //active low
}

void disableCS(){
	HAL_GPIO_WritePin(GPIOB, CS_Pin, GPIO_PIN_SET); //active low
}

MS5607StateTypeDef MS5607_init1(SPI_HandleTypeDef *hspix, uint16_t GPIO_Pin){
	 enableCS();
	 SPITransmitData = RESET_COMMAND;
	 HAL_SPI_Transmit(hspix, &SPITransmitData, 1, 10);
	 HAL_Delay(10);
	 disableCS();
	 MS5607PromRead(&promData);
	 if (promData.reserved == 0x00 || promData.reserved == 0xff)
	     return MS5607_STATE_FAILED;
	   else
	     return MS5607_STATE_READY;

	 //prom operations unclear
}
void MS5607PromRead1(struct promData *prom,SPI_HandleTypeDef *hspix){
  uint8_t   address;
  uint16_t  *structPointer;

  /* As the PROM is made of 8 16bit addresses I used a pointer for acessing the data structure */
  structPointer = (uint16_t *) prom;

  for (address = 0; address < 8; address++) {
    SPITransmitData = PROM_READ(address);
    enableCS();
    HAL_SPI_Transmit(hspix, &SPITransmitData, 1, 10);
    /* Receive two bytes at once and stores it directly at the structure */
    HAL_SPI_Receive(hspix, structPointer, 2, 10);
    disableCS();
    structPointer++;
  }
}
  uint8_t* MS5607_Readunc(SPI_HandleTypeDef *hspix) {
      uint8_t *reply = (uint8_t *)malloc(3 * sizeof(uint8_t));
      enableCS();
      SPITransmitData = CONVERT_D1_COMMAND | Pressure_OSR;
      HAL_SPI_Transmit(hspix, &SPITransmitData, 1, 10);
      HAL_Delay(1);
      disableCS();

      enableCS();
      SPITransmitData = READ_ADC_COMMAND;
      HAL_SPI_Transmit(hspix, &SPITransmitData, 1, 10);
      HAL_SPI_Receive(hspix, reply, 3, 10);
      disableCS();

      return reply;
  }

/*uint8_t* MS5607_Readunc(SPI_HandleTypeDef *hspix){
	uint8_t *reply;
	 //uint8_t *txBuff;
	reply = (uint8_t *)malloc(3*sizeof(uint8_t));
	  enableCS();
	  SPITransmitData = CONVERT_D1_COMMAND | Pressure_OSR;
	  HAL_SPI_Transmit(hspix, &SPITransmitData, 1, 10);
	  HAL_Delay(1);
	  disableCS();

	  enableCS();
	  SPITransmitData = READ_ADC_COMMAND;
	  HAL_SPI_Transmit(hspix, &SPITransmitData, 1, 10);
	  HAL_SPI_Receive(hspix, reply, 3, 10);
	  //uint32_t abc = ((uint32_t) reply[0] << 16) | ((uint32_t) reply[1] << 8) | (uint32_t) reply[2];
	  disableCS();
	  return reply;
}*/


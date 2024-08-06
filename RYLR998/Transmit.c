#include "Transmit.h"

void Transmit(UART_HandleTypeDef *huart,uint8_t size, uint8_t *data ){
	char uartTxBuff[240] = {0};
    char numStr[5];
	strcat(uartTxBuff,SendString);
	snprintf(numStr, sizeof(numStr), "%d", size);
	strcat(uartTxBuff,numStr);
	strcat(uartTxBuff,Comma);
	strcat(uartTxBuff,data);
	strcat(uartTxBuff,Terminator);
	HAL_UART_Transmit(huart,(uint8_t*) uartTxBuff, strlen(uartTxBuff), 200);
}

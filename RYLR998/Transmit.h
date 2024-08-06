#include "string.h"
#include "stm32f4xx_hal_uart.h"

#define SendString "AT+SEND=0," //change 0 to receiver address, else it will just broadcast
#define Comma ","
#define Terminator "\r\n"

void Transmit(UART_HandleTypeDef *huart,uint8_t size, uint8_t *data );

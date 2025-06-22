/*
 * printf.c
 *
 *  Created on: Jun 22, 2025
 *      Author: ACER
 */
#include "printf.h"

UART_HandleTypeDef huart1;

char buff[40];

void mprintf(const char* format,...){
	va_list args;
	va_start(args,format);
	vsnprintf(buff,sizeof(buff), format,args);
	va_end(args);

	HAL_UART_Transmit(&huart1, (uint8_t*)buff, 40, 1000);
}

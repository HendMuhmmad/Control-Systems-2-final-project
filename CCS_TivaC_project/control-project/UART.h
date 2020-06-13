/*
 * UART.h
 *
 *  Created on: May 28, 2020
 *      Author: hend
 */

#ifndef __UART_H__
#define __UART_H__
#include <stdbool.h>
#include <stdint.h>
#include "..\inc\tm4c123gh6pm.h"
#include "..\driverlib\sysctl.h"


#define ui32ClockFreq 16000000
#define CYCLES_FROM_TIME_US(ui32ClockFreq, ui32Time_uS)                       \
    (((ui32Time_uS) == 0) ? 0 :                                               \
    (((ui32ClockFreq) / 1000000) * ((((ui32Time_uS) * 1000) - 1) / 1000)) + 1)

void UART_init(void);
void UART_sendNumber(int32_t num);
uint8_t UART_RecieveNumber(void);
void UART_sendString(uint8_t*  str);
void UART_recieveString(uint8_t* str);
uint8_t UART_RecieveNumber_Polling(void);
void UART_sendByte(int8_t data);
void UART_sendFloatNumber(float x);
#endif

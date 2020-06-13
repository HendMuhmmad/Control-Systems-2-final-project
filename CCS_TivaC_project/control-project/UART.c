/*
 * UART.c
 *
 *  Created on: May 28, 2020
 *      Author: hend
 */
#include "UART.h"

//simple UART  0 initialize
void UART_init(void)
{
    //clock initialize for uart0 and port A
    SYSCTL_RCGCUART_R |= 1;
    SYSCTL_RCGCGPIO_R |= 1;
    //uart0 initialization
    //disable uart0
    UART0_CTL_R = 0x00;
    //baud rate 9600
    UART0_IBRD_R = 104;
    UART0_FBRD_R = 11;
    //use system clock
    UART0_CC_R = 0x00;
    //disable FIFO,8-bit,1 stop bit ,no parity
    UART0_LCRH_R = 0x60;
    //enable UART ,TX and RX
    UART0_CTL_R = 0x301;
    //digital enable for PA0 and PA1
    GPIO_PORTA_DEN_R = 0x03;
    //set PA0 and PA1 for alternate function
    GPIO_PORTA_AFSEL_R = 0x03;
    //set PA0 and PA1 as UART TX and RX
    GPIO_PORTA_PCTL_R = 0x11;

    //delay
    SysCtlDelay(CYCLES_FROM_TIME_US(ui32ClockFreq, 1000) / 3);
}

void UART_sendNumber(int32_t input)
{

    uint32_t num=1;
        /*inverted number */
        if(input==0)
        {
            UART_sendByte('0');
        }
        if(input<0)
        {
            UART_sendByte('-');
            input = -1*input;
        }
        while(input!=0)
        {
            num=num*10+input%10;
            input/=10;
        }
        /*display number */
        while(num!=1)
        {
            UART_sendByte(num%10+'0');
            num/=10;
        }


    /* while ((UART0_FR_R & 0x20) != 0)
        ;
    UART0_DR_R = (uint32_t) data;*/
}
void UART_sendByte(int8_t data){
    while ((UART0_FR_R & 0x20) != 0)
            ;
        UART0_DR_R = (uint32_t) data;
}
uint8_t UART_RecieveNumber(void)
{
    uint8_t data;
    while ((UART0_FR_R & 0x10) != 0)
        ;
    data = (uint8_t) UART0_DR_R;
    return data;
}
void UART_sendString(uint8_t* str)
{
    uint8_t i = 0;
    while (str[i] != '\0')
    {
        UART_sendByte(str[i]);
        i++;
    }
}
void UART_recieveString(uint8_t* str)
{
    int8_t i = -1;
    do
    {
        i++;
        str[i] = UART_RecieveNumber();

    }
    while (str[i] != '\0');
}
uint8_t UART_RecieveNumber_Polling(void)
{
    uint8_t data = 0;
    if ((UART0_FR_R & 0x10) == 0)
    {
        data = (uint8_t) UART0_DR_R;
    }
    return data;

}

void UART_sendFloatNumber(float x){
    float floatpart;
    uint8_t i = 0;
    uint32_t rev_number = 0;
    if(x<0)
    {
        floatpart =-( x - (int32_t)x);
    }
    else
    {
        floatpart = x - (int32_t)x;
    }

    UART_sendNumber((int32_t)x);
    if(floatpart > 0.00009)
    {
        i = 0;
        while(i<4)
        {
            floatpart = floatpart*10;
            i++;
        }
        /*we reverse the number by i times*/
        while(i != 0)
        {
            rev_number = rev_number*10 +((int32_t)floatpart)%10;
            floatpart =  ((int32_t)floatpart)/10;
            i--;
        }
        UART_sendByte('.');
        while(rev_number != 0)
        {
            UART_sendByte((rev_number % 10)+48); /*reverse%10 + '0'*/
            rev_number = rev_number/10;
        }
    }

}

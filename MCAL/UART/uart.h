/*
 * uart.h
 *
 * Created: 8/22/2023 5:02:18 PM
 *  Author: pc
 */

#include "../../Utilities/definitions.h"

#ifndef UART_H_
#define UART_H_





typedef enum{
	 doubleSpeed =1 , Normal,
	} txSpeed; 

void USART_Init(uint16_t baud , txSpeed speed);

void USART_Transmit(uint8_t data);

void USART_Transmit_string(uint8_t* data);

uint8_t USART_Receive(void );

uint8_t USART_Receive_available();

void USART_Receive_string(uint8_t* data, uint8_t size );

void USART_Flush( void );

#endif /* UART_H_ */
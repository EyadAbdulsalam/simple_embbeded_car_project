/*
 * uart.c
 *
 * Created: 8/22/2023 5:02:03 PM
 *  Author: pc
 */ 



#include "uart.h"

// UBRR = fosc/16/BAUD - 1   where U2X = 0
	
// UBRR = fosc/8/BAUD - 1    where U2X = 1



void USART_Init( uint16_t baud , txSpeed speed )
{

	/* Set baud rate */
	
	baud = 51 ;                      //hard code baud rate equal 9600  
	
	
	UBRRH = (uint8_t)(baud>>8);
	UBRRL = (uint8_t)(baud);
	/* Enable receiver and transmitter */
	UCSRB = (1<<RXEN)|(1<<TXEN);
	/* Set frame format: 8data, 1stop bit */
	UCSRC = (1<<URSEL)|(3<<UCSZ0);
}



void USART_Transmit( uint8_t data )
{
	/* Wait for empty transmit buffer */
	while ( !( UCSRA & (1<<UDRE)) )	;
	/* Put data into buffer, sends the data */
	UDR = data;
}



void USART_Transmit_string(uint8_t data[])
{
	
	for (uint8_t i=0 ; data[i]!='\0'; i++)
	{
		USART_Transmit(data[i]);
	}
}

uint8_t USART_Receive_available()
{
	return (UCSRA & (1<<RXC)); //this flag is set if there is unread data (data recieve complete)
}

uint8_t USART_Receive( void )
{
	/* Wait for data to be received */
	while ( !(UCSRA & (1<<RXC)) ) ;
	
	/* Get and return received data from buffer */
	return UDR;
}

void USART_Receive_string(uint8_t* data, uint8_t size ){
	
	for (int i =0 ; i<size ; i++)
	{
		data[i]=USART_Receive();
	}
}

void USART_Flush( void )
{
	unsigned char dummy;
	while ( UCSRA & (1<<RXC) ) dummy = UDR;
}
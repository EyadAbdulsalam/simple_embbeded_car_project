/*
 * eco_racing_task.c
 *
 * Created: 8/22/2023 3:50:37 PM
 * Author : pc
 */ 

#include "Utilities/definitions.h"
#include "MCAL/UART/uart.h"
#include "ECUAL/LCD_16x2 Driver/LCD_16x2.h"
#include "Application/application.h"
#include "MCAL/DIO Driver/DIO.h"
#include "MCAL/INTERRUPTS/interrupts.h"



int main(void)
{	
	appStart();
}

ISR(TIMER1_COMPA_vect)
{
	secounds++;
}

ISR(USART_RXC_vect)
{
	if (i == 9) i=0;
	data[i]=USART_Receive();
	i++;
	
}

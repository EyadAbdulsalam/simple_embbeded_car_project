/*
 * DIO.c
 *
 *  Author: Eyad Hossam
 */ 

#include "DIO.h"

void DIO_init(uint8_t portnum,uint8_t pinnum,uint8_t direction)                           //initialize specific pin as INPUT or OUTPUT pin 
{
	switch (portnum)                                               //1.choose PORT
	{
		case PORT_A:                  
		if (direction==OUT)                                        //2. choose MODE
		{
			DDRA |= (1<<pinnum);       //3.set the bit which correspond to that pin in the digital direction register 
		}
		else if(direction==IN)
		{
			DDRA &= ~(1<<pinnum);      //3.clear the bit which correspond to that pin in the digital direction register 
		}
		else
		{
			//ERROR handling
		}	   
		break;
	
		case PORT_B:                                               //same as above
		if (direction==OUT)
		{
			DDRB |= (1<<pinnum);
		}
		else if(direction==IN)
		{
			DDRB &= ~(1<<pinnum);
		}
		else
		{
			//ERROR handling
		}
		break;

		case PORT_C:                                               //same as above
		if (direction==OUT)
		{
			DDRC |= (1<<pinnum);
		}
		else if(direction==IN)
		{
			DDRC &= ~(1<<pinnum);
		}
		else
		{
			//ERROR handling
		}
		break;
	
		case PORT_D:                                              //same as above
		if (direction==OUT)
		{
			DDRD |= (1<<pinnum);
		}
		else if(direction==IN)
		{
			DDRD &= ~(1<<pinnum);
		}
		else
		{
			//ERROR handling
		}
		break;
	}
}

void DIO_write(uint8_t portnum,uint8_t pinnum,uint8_t value)                              //write high/low on specific pin
{
	switch (portnum)                                  //1.choose PORT
	{
		case PORT_A:
		if (value==HIGH)                              //2.high/low flow
		{
			PORTA |= (1<<pinnum);         //3.set bit what would indicate high output acc. to datasheet
		}
		else if(value==LOW)
		{
			PORTA &= ~(1<<pinnum);        //3.clear bit what would indicate LOW output acc. to datasheet
		}
		else
		{
			//ERROR handling
		}
		break;
		
		
		case PORT_B:                      //same as above
		if (value==HIGH)
		{
			PORTB |= (1<<pinnum);
		}
		else if(value==LOW)
		{
			PORTB &= ~(1<<pinnum);
		}
		else
		{
			//ERROR handling
		}
		break;
		
		
		case PORT_C:                      //same as above
		if (value==HIGH)
		{
			PORTC |= (1<<pinnum);
		}
		else if(value==LOW)
		{
			PORTC &= ~(1<<pinnum);
		}
		else
		{
			//ERROR handling
		}
		break;
		
		case PORT_D:                      //same as above
		if (value==HIGH)
		{
			PORTD |= (1<<pinnum);
		}
		else if(value==LOW)
		{
			PORTD &= ~(1<<pinnum);
		}
		else
		{
			//ERROR handling
		}
		break;
	}
}

void DIO_toggle(uint8_t portnum,uint8_t pinnum)                                           //Toggle specific pin
{                                          
	switch (portnum)                      //1.choose PORT
	{
		case PORT_A:
			PORTA ^= (1<<pinnum);         //2.Toggle bit in corresponding register to that pin 
		break;
		case PORT_B:
			PORTB ^= (1<<pinnum);
		break;
		case PORT_C:
			PORTC ^= (1<<pinnum);
		break;
		case PORT_D:
		PORTD ^= (1<<pinnum);
		break;
	}
}

//void DIO_read(uint8_t portnum,uint8_t pinnum,uint8_t* value)                              //Read specific pin 
//{
	//switch (portnum)                                     //1.choose PORT
	//{
		//case PORT_A:
		//*value=(PINA & (1<<pinnum))>>pinnum;             //2.read desired bit then shift it into first bit to give (0 or 1) only
		//break;
		//
		//case PORT_B:
		//*value=(PINB & (1<<pinnum))>>pinnum;
		//break;
		//
		//case PORT_C:
		//*value=(PINC & (1<<pinnum))>>pinnum;
		//break;
		//
		//case PORT_D:
		//*value=(PIND & (1<<pinnum))>>pinnum;
		//break;
	//}
//}
uint8_t DIO_read(uint8_t portnum,uint8_t pinnum)                              //Read specific pin
{
	switch (portnum)                                     //1.choose PORT
	{
		case PORT_A:
		return (PINA & (1<<pinnum))>>pinnum;             //2.read desired bit then shift it into first bit to give (0 or 1) only
		break;
		
		case PORT_B:
		return (PINB & (1<<pinnum))>>pinnum;
		break;
		
		case PORT_C:
		return (PINC & (1<<pinnum))>>pinnum;
		break;
		
		case PORT_D:
		return (PIND & (1<<pinnum))>>pinnum;
		break;
	}
	return 0;
}

/*
 * interrupts.c
 *
 *  Author: Eyad Hossam
 */ 


#include "interrupts.h"


void enable_extint(int INT_n){

	switch(INT_n){
		case INT0:
		GICR|=(1<<6);
		break;
		
		case INT1:
		GICR|=(1<<7);
		break;
		
		case INT2:
		GICR|=(1<<5);
		break;
		default:
		//error handler
		break;
	}	
}

void INT0_Sense(Sense sense)
{
	switch(sense){
		case LOWlvl:
		MCUCR &=~(3<<0);
		break;
		
		case logical_change:
		MCUCR |=(1<<0);
		MCUCR &=~(1<<1);
		break;
		
		case falling_Edge:
		MCUCR |=(1<<1);
		MCUCR &=~(1<<0);
		break;
		
		case rising_Edge:
		MCUCR |=(3<<0);
		break;
		default:
		//error handler
		break;
	}
}

void INT1_Sense(Sense sense)
{
	switch(sense){
		case LOWlvl:
		MCUCR &=~(3<<2);
		break;
		
		case logical_change:
		MCUCR |=(1<<2);
		MCUCR &=~(1<<3);
		break;
		
		case falling_Edge:
		MCUCR |=(1<<3);
		MCUCR &=~(1<<2);
		break;
		
		case rising_Edge:
		MCUCR |=(3<<2);
		break;
		default:
		//error handler
		break;
	}
}


void INT2_Sense(Sense sense)
{
	switch(sense){
		case falling_Edge:
		MCUCSR &=~(1<<6);
		break;
		
		case rising_Edge:
		MCUCSR |=(1<<6);
		break;
		default:
		//error handler
		break;
	}
}
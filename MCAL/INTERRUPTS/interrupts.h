/*
 * interrupts.h
 *
 *  Author: Eyad Hossam
 */ 


#ifndef INTERRUPTS_H_
#define INTERRUPTS_H_

#include "../../Utilities/definitions.h"


#define sei()  __asm__ __volatile__ ("sei" ::: "memory")                //Enables INTURRUPTS 
#define cli()  __asm__ __volatile__ ("cli" ::: "memory")                //Disables INTURRUPTS

typedef enum Sense{
	LOWlvl,logical_change,rising_Edge,falling_Edge
	}Sense;
	
//#define INT0 1
//#define INT1 2
//#define INT2 3


#define INT0vect  __vector_1
#define INT1vect  __vector_2
#define INT2vect  __vector_3


void enable_extint(int INT_n);
void INT0_Sense(Sense sense);
void INT1_Sense(Sense sense);
void INT2_Sense(Sense sense);

#define ISR(INT_n) void INT_n(void) __attribute__ ((signal,used)); \
void INT_n(void)

#endif /* INTERRUPTS_H_ */
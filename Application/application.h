/*
 * application.h
 *
 * Created: 8/23/2023 2:53:24 PM
 *  Author: pc
 */ 

#include "../Utilities/definitions.h"
#include "../ECUAL/LCD_16x2 Driver/LCD_16x2.h"
#include "../MCAL/UART/uart.h"
#include "../MCAL/DIO Driver/DIO.h"
#include "../MCAL/INTERRUPTS/interrupts.h"

#ifndef APPLICATION_H_
#define APPLICATION_H_

#define  Forward 1
#define  Backward 0

typedef struct{
	uint8_t speed;
	uint8_t dir;
	int8_t angle;
	uint8_t dir2;
	uint8_t frameEnd;
}parameters;


extern uint8_t secounds;
extern uint8_t i;
extern uint8_t data[10];
extern parameters car1;

void appStart();

void update_lcd();

void update_time_lcd();

void control_motors();

void extract_parameters(parameters* dataStruct ,uint8_t dataArr[] );

char check_frame(uint8_t data[]);



#endif /* APPLICATION_H_ */
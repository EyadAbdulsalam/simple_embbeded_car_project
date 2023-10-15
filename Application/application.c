/*
 * application.c
 *
 * Created: 8/23/2023 2:53:44 PM
 *  Author: pc
 */ 

#include "application.h"
#include <stdio.h>

#define RESET 0
#define H_F 1
#define CW_CCW 2
#define STEP 3
#define HOME 4

parameters car1={};
uint8_t str[15]={};
uint8_t secounds=0;
uint8_t minutes=0;
uint8_t hours=0;
uint8_t i=0;
uint8_t data[10]={ '0','0','0','F','0','0','R','E','\n','\0' };  //8 chars + 1 return char + 1 null terminating

void appStart()
{	
	sei();                                //enable global interrupts
	USART_Init(9600,doubleSpeed);
	LCD_8bit_init();
		
	uint8_t x=0;                         // var for error handling purpose
	
	/* setting up PWM for controlling DC-MOTOR speed */
	DDRB  |= (1 << DDD3);
		
	TCCR0 = ((1<<WGM01) | (1<<WGM00) | (1 << COM01)) & ~(1 << COM00) ;     //fast non-inverting PWM
	TCCR0 |= (1<<CS00)  | (1<<CS02) ;                                      //pre-scaling 1024
	TCCR0 &= ~(1<<CS01);	
	OCR0 = 0 ;                                                             //speed initially approx. equal zero
		
	/* Forward/Backward direction pin */
	DIO_init(PORT_B, 2 , OUT);
	
	/* Stepper Motor pins and initialization */
	DIO_init(PORT_C, RESET , OUT);
	DIO_init(PORT_C, H_F , OUT);
	DIO_init(PORT_C, CW_CCW , OUT);
	DIO_init(PORT_C, STEP , OUT);
	DIO_init(PORT_C, HOME , IN);
	
	DIO_write(PORT_C, RESET , HIGH);
	DIO_write(PORT_C, H_F , HIGH);
	_delay_us(5);
	DIO_write(PORT_C, CW_CCW ,LOW);
	_delay_us(5);
	
	DIO_write(PORT_C, STEP ,HIGH);
	DIO_write(PORT_C, H_F ,LOW);
	_delay_us(5);

	// enable timer_1 compA interrupt
	TCCR1A = 0;
	TCCR1B = 0x0C;               // CTC mode , prescaler =256
	OCR1AH = 0x7A;               // setting compare match to value equivalent to one second
	OCR1AL = 0x12;
	TIMSK  |= (1<<OCIE1A);       // enable compA interrupt 
	
	//enable reception interrupt
	UCSRB |= (1<<RXCIE);
	
	//display time
	update_time_lcd();	
	while (1)
	{
		extract_parameters(&car1,data);
		x = check_frame(data);
		
		if (x == 0)
		{
			update_lcd();						
			control_motors();
		}
		
		update_time_lcd();
	}
}



void update_lcd()
{
	LCD_8bit_sendcommand(Return_home);
	LCD_8bit_sendstr((uint8_t*)"SPD:");
	tostring(str,car1.speed);
	LCD_8bit_sendstr(str);
	LCD_8bit_sendchar('%');
	LCD_8bit_sendchar(' ');
	LCD_8bit_sendcommand(cursor_1stline_10);
	LCD_8bit_sendstr((uint8_t*)" Dir:");
	if(car1.dir2 == 'L') 
	{
		sprintf(str,"%d",car1.angle);
	}
	else 
	{
		LCD_8bit_sendchar(' ');
		tostring(str,car1.angle);
	}
	LCD_8bit_sendstr(str);
}

void update_time_lcd()
{
	LCD_8bit_sendcommand(cursor_2ndline);
	LCD_8bit_sendstr((uint8_t*)"Time:");

	if (hours==23 && minutes == 59 && secounds == 60)               //Clear timer when reach max
	{
		hours=0;
		minutes=0;
		secounds=0;
	}
	if (secounds==60)                            //update minutes
	{
		minutes++;
		secounds=0;
	}
	if (minutes==60)                             //update hours
	{
		hours++;
		minutes=0;
	}

	if (hours>9)
	{
		tostring(str,hours);
		LCD_8bit_sendstr(str);
		LCD_8bit_sendstr((uint8_t*)":");
	}
	else
	{
		tostring(str,hours);
		LCD_8bit_sendchar('0');
		LCD_8bit_sendstr(str);
		LCD_8bit_sendstr((uint8_t*)":");
	}
		
	if (minutes>9)                              
	{
		tostring(str,minutes);
		LCD_8bit_sendstr(str);
		LCD_8bit_sendstr((uint8_t*)":");
	}
	else
	{
		tostring(str,minutes);
		LCD_8bit_sendchar('0');
		LCD_8bit_sendstr(str);
		LCD_8bit_sendstr((uint8_t*)":");
	}
	
	if (secounds>9)                            
	{
		tostring(str,secounds);
		LCD_8bit_sendstr(str);
		LCD_8bit_sendstr((uint8_t*)" ");
	}
	else
	{
		tostring(str,secounds);
		LCD_8bit_sendchar('0');
		LCD_8bit_sendstr(str);
		LCD_8bit_sendstr((uint8_t*)" ");		
	}
	
	if (hours>=12)
	{
		LCD_8bit_sendstr((uint8_t*)"PM");
	}
	else
	{
		LCD_8bit_sendstr((uint8_t*)"AM");		
	}
	
}


void extract_parameters(parameters* dataStruct ,uint8_t dataArr[] )
{
	dataStruct->speed = (dataArr[0]-'0')*100 +(dataArr[1]-'0')*10 + dataArr[2]-'0' ;
	dataStruct->dir = dataArr[3];
	dataStruct->angle = (dataArr[4]-'0')*10 + dataArr[5]-'0' ;
	dataStruct->dir2 = dataArr[6];
	dataStruct->frameEnd = dataArr[7];
	
	if (dataStruct->dir2 == 'L') dataStruct->angle = dataStruct->angle * -1;
	
}


void control_motors(){
	
	/* DC Motor */
	OCR0 = car1.speed*2.55;
	if (car1.dir == 'F') DIO_write(PORT_B,2,Forward);
	else DIO_write(PORT_B,2,Backward);
	
	/* Stepper Motor */
	static uint8_t currentangle=0;
	if (currentangle != car1.angle)
	{
		uint8_t j=0;
		int8_t angles_toMove = car1.angle - currentangle; 
		if ( angles_toMove > 0)
		{
			DIO_write(PORT_C,CW_CCW,HIGH);
			_delay_us(5);
			while(j< angles_toMove)
			{
				DIO_write(PORT_C, STEP , LOW);
				_delay_ms(20);                             // depends on maximum motor RPM
				DIO_write(PORT_C, STEP , HIGH);
				j++;
			}
			currentangle += j;                             // update current angle
		}
		else
		{
			DIO_write(PORT_C,CW_CCW,LOW);
			_delay_us(5);
			while(j< (angles_toMove*-1))
			{
				DIO_write(PORT_C, STEP , LOW);
				_delay_ms(20);                              // depends on maximum motor RPM
				DIO_write(PORT_C, STEP , HIGH);
				j++;
			}
			currentangle -=j;                               // update current angle
		}
	}

}


char check_frame(uint8_t data[])
{
	if ( (data[0]-'0')*100 +(data[1]-'0')*10 + data[2]-'0' > 100 || (data[0]-'0')*100 +(data[1]-'0')*10 + data[2]-'0' < 0 )  // if speed percentage is smaller than 0 or bigger than 100
	{
		i=0;
		return 1;
	}
	if ( data[3] != 'F' && data[3] != 'B') 
	{
		i=0;
		return 1;
	}
	if ( (data[4]-'0')*10 + data[5]-'0' > 45 || (data[4]-'0')*10 + data[5]-'0' < 0 )
	{
		i=0;
		return 1;
	}
	if (data[6] != 'R' && data[6] != 'L')
	{
		i=0;
		return 1;
	}
	if(data[7]!='E' )
	{
		i=0;
		return 1;
	}
	
	return 0;
}


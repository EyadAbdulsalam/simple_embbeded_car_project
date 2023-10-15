/*
 * LCD_16x2_Driver.c
 *
 * Created: 11/10/2022 9:16:06 PM
 *  Author: pc
 */ 


#include "LCD_16x2.h"



void LCD_8bit_init(void)
{
	LCD_cmd_Dir = 0x03;		 
	LCD_data_Dir =0xFF;
	//Start_timer_milli(20);		
	_delay_ms(20);
	
	LCD_8bit_sendcommand(0x38);    // initialize 8-bit mode (2-lines, 5x8 dots) 
	//Start_timer_micro(37);
	_delay_us(37);
	
	LCD_8bit_sendcommand(0x0C);	   // display on, cursor off, blink off 
	//Start_timer_micro(37);
	_delay_us(37);
	
	LCD_8bit_sendcommand(0x01);	   //  Clear screen
	//Start_timer_milli(2);
	_delay_ms(2);
	
	LCD_8bit_sendcommand(0x06);	   // increment ,shift off
}


void LCD_8bit_sendcommand(uint16_t cmd){
	
	LCD_data = cmd;
	LCD_cmd &= ~ (1<<RS);		/* RS=0, command reg. */
	LCD_cmd |= (1<<EN);		    /* Enable pulse */
	//Start_timer_micro(1);
	_delay_us(1);
	
	LCD_cmd &= ~ (1<<EN);
	//Start_timer_milli(3);
	_delay_ms(3);
}


void LCD_8bit_sendchar(uint8_t chr){
	LCD_data =chr;
	
	LCD_cmd |= (1<<RS);		/* RS=1, data reg. */
	LCD_cmd |= (1<<EN);		    /* Enable pulse */
	//Start_timer_micro(1);
	_delay_us(1);
	
	LCD_cmd &= ~ (1<<EN);
	//Start_timer_milli(1);
	_delay_ms(1);
}


void LCD_8bit_sendstr(uint8_t str[]){
	
	for(uint16_t i=0; str[i]!=0 ; i++){
		LCD_8bit_sendchar(str[i]);
	}
}
	

void tostring(uint8_t *str, uint16_t num)
{
	int i, rem, len = 0, n;
	
	n = num;
	if (n == 0)len++;
	while (n != 0)
	{
		len++;
		n /= 10;
	}
	for (i = 0; i < len; i++)
	{
		rem = num % 10;
		num = num / 10;
		str[len - (i + 1)] = rem + '0';
	}
	str[len] = '\0';
}

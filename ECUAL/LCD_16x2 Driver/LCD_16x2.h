/*
 * LCD_16x2_Driver.h
 *
 * Created: 11/10/2022 9:16:28 PM
 *  Author: pc
 */ 


#ifndef LCD_16X2_H_
#define LCD_16X2_H_

#include "../../Utilities/definitions.h"

#define LCD_cmd_Dir   DDRB
#define LCD_cmd       PORTB

#define LCD_data_Dir  DDRA
#define LCD_data      PORTA
#define  RS  0
#define  EN  1 

#define Clear 0x01
#define Return_home 0x02
#define cursor_2ndline 0xC0
#define move_left 0x10

#define cursor_1stline_10 0x88
#define cursor_1stline_8 0x87   

void LCD_8bit_init(void);
void LCD_8bit_sendcommand(uint16_t);
void LCD_8bit_sendchar(uint8_t);
void LCD_8bit_sendstr(uint8_t str[]);
void tostring(uint8_t *str, uint16_t num);


#endif /* LCD_16X2 DRIVER_H_ */
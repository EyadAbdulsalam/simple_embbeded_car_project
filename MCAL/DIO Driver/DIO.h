/*
* DIO.h
*
*  Author: Eyad Hossam
*/


#ifndef DIO_H_
#define DIO_H_

#include "../../Utilities/definitions.h"

/************************************************************************/
/*                            I/O PORTS                                 */
/************************************************************************/
#define PORT_A 'A'
#define PORT_B 'B'
#define PORT_C 'C'
#define PORT_D 'D'

#define IN 0
#define OUT 1

#define HIGH 1
#define LOW  0

void DIO_init(uint8_t portnum,uint8_t pinnum,uint8_t direction);
void DIO_write(uint8_t portnum,uint8_t pinnum,uint8_t value);
void DIO_toggle(uint8_t portnum,uint8_t pinnum);
uint8_t DIO_read(uint8_t portnum,uint8_t pinnum);


#endif /* DIO_H_ */
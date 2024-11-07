/*
 * HelloWorld.c
 *
 * Created: 11/9/2023 10:43:27 AM
 * Author : Alin
 */ 
/*

*/


#include <stdio.h>
#include <stdlib.h>

#include <avr/io.h>
#include <util/delay.h>

/* I2C coms */
#include "i2cmaster.h"
/* LCD */ 
#include "lcd.h"
/* Temp sens */
/*
#include "lm75.c"
#include "lm75.h"
*/

//#include "twimaster.c"
#include "usart.h"

/* PORTA*/
#define GPA0 A0
#define GPA1 A1
#define GPA2 A2
#define GPA3 A3
#define GPA4 A4
#define GPA5 A5
#define GPA6 A6
#define GPA7 A7
/* PORTB */
#define GPB0 B0
#define GPB1 B1
#define GPB2 B2
#define GPB3 B3
#define GPB4 B4
#define GPB5 B5
#define GPB6 B6
#define GPB7 B7
/* PORTC */
#define GPC0 C0
#define GPC1 C1
#define GPC2 C2
#define GPC3 C3
#define GPC4 C4
#define GPC5 C5
#define GPC6 C6
#define GPC7 C7
/* PORTD*/
#define GPD0 D0
#define GPD1 D1
#define GPD2 D2
#define GPD3 D3
#define GPD4 D4
#define GPD5 D5
#define GPD6 D6
#define GPD7 D7

int main(void) {   
  /*  
  uart_init(); // open the communication to the microcontroller
  io_redirect(); // redirect input and output to the communication  
  */
  
  DDRC = 0xF0;
  DDRD = 0xFF;
  
  PORTC = 0x3F;

  i2c_init(); 
  LCD_init();
    
  while(1) {
    PORTC = 0x3F;
    LCD_set_cursor(2,1);

		if(PINC == 0b00111110){
      do{
        PORTD = 0x10;
        printf("DI_0 ");
      }while(PINC == 0b00111110);
      PORTD = 0x00;
    }
    else if(PINC == 0b00111101){
      do{
        PORTD = 0x20;
        printf("DI_1 ");
      }while(PINC == 0b00111101);
      PORTD = 0x00;
    }
    else if(PINC == 0b00111011){
      do{
        PORTD = 0x40;
        printf("DI_2 ");
      }while(PINC == 0b00111011);
      PORTD = 0x00;
    }
    else if(PINC == 0b00110111){
      do{
        PORTD = 0x80;
        printf("DI_3 ");
      }while(PINC == 0b00110111);
      PORTD = 0x00;
    }

  }
  
  return 0;
}

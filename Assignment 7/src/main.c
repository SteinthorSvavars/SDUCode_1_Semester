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
#include <htc.h>
#include <xc.h>

#include <avr/io.h>
#include <util/delay.h>

/* I2C coms */
#include "i2cmaster.h"
/* LCD */
#include "lcd.c"
#include "lcd.h"
/* Temp sens */
#include "lm75.c"
#include "lm75.h"

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

  int input;  
  /*  
  uart_init(); // open the communication to the microcontroller
  io_redirect(); // redirect input and output to the communication  
  */
  
  DDRC = 0xF0;
  DDRD = 0xFF;

  PORTC = 0x0F;
  PORTD = 0x00;
  
    
  while(1) {
		if(C0 == 1){
      do{
        D4 = 1;
      }while(C0 == 1);
      D4 = 0;
    }
    else if(C1 == 1){
      do{
        D5 = 1;
      }while(C1 == 1);
      D5 = 0;
    }
    else if(C2 == 1){
      do{
        D6 = 1;
      }while(C2 == 1);
      D6 = 0;
    }
    else if(C3 == 1){
      do{
        D7 = 1;
      }while(C3 == 1);
      D7 = 0;
    }

  }
  
  return 0;
}

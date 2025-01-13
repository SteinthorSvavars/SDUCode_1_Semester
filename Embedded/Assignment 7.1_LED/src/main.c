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
		if(PINC == 0b00111110){
      do{
        PORTD = 0x10;
        LCD_set_cursor(0,0);
        printf("DI_0");
      }while(PINC == 0b00111110);
      PORTD = 0x00;
    }
    else if(PINC == 0b00111101){
      do{
        PORTD = 0x20;
        LCD_set_cursor(0,0);
        printf("DI_1");
      }while(PINC == 0b00111101);
      PORTD = 0x00;
    }
    else if(PINC == 0b00111011){
      do{
        PORTD = 0x40;
        LCD_set_cursor(0,0);
        printf("DI_2");
      }while(PINC == 0b00111011);
      PORTD = 0x00;
    }
    else if(PINC == 0b00110111){
      do{
        PORTD = 0x80;
        LCD_set_cursor(0,0);
        printf("DI_3");
      }while(PINC == 0b00110111);
      PORTD = 0x00;
    }

  }
  
  return 0;
}

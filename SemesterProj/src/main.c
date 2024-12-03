/*
 * HelloWorld.c
 *
 * Created: 11/9/2023 10:43:27 AM
 * Author : Alin
 */ 



#include <stdio.h>
#include <stdlib.h>

#include <avr/io.h>
#include <util/delay.h>

/* I2C coms */
/*
#include "i2cmaster.h"
*/
/* LCD */ 
/*
#include "lcd.h"
*/
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

 /* i2c_init(); 
  LCD_init(); */
    
  while(1) {
    PORTC = 0x3F;
   // LCD_set_cursor(2,1);
   PORTD = 0x10;
   _delay_ms(250);
   PORTD = 0x00;
   _delay_ms(250);
  }
  return 0;
}

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

int KeyPad(void) // tekur inn input frá 4x4 keypad
{
    int tala = -1;
    int input;
    int press = 0;
    _delay_ms(10);
    input = PINC;  // segir a? input s? sama og hva?a takki s? ?tt ? ? PORTD
    if(input == 0b00111110 || input == 0b00111101 || input == 0b00111011 || input == 0b00110111){
        switch(input){
            case 0b00111110: tala = 1; press++; break;     // RD4    
            case 0b00111101: tala = 2; press++; break;     // RD5
            case 0b00111011: tala = 3; press++; break;     // RD6
            case 0b00110111: tala = 4; press++; break;    // RD7
        }
    }
    _delay_ms(10);
    if((press == 0) && (tala == -1)){
        return tala;
    }
    return tala;
}
int x = 0;
int y = 0;

int main(void) {   
   
  uart_init(); // open the communication to the microcontroller
  io_redirect(); // redirect input and output to the communication  
  
  
  DDRC = 0xF0;
  DDRD = 0xFF;
  
  PORTC = 0x3F;

  i2c_init(); 
  LCD_init();
    
  while(1) {
    PORTC = 0x3F;
    LCD_set_cursor(2,1);
      x = KeyPad();
      if(x == -1){
        y = y;
      }
      else{
        y = x;
      }
        PORTD = 0b00010000;
        //_delay_ms(500);
        for (int i = 0; i <= 3; i++)
        {
          for (int i = 0; i < y; i++)
          {
            _delay_ms(250);
          }
          PORTD = PORTD << 1;
          x = KeyPad();
          if(x == -1){
            y = y;
          }
          else{
            y = x;
          }
        }    
    }

  }
  
 // return 0;


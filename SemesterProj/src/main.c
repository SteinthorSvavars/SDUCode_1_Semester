/*
 * HelloWorld.c
 *
 * Created: 11/9/2023 10:43:27 AM
 * Author : Alin
 * 
 * DHT library https://tinusaur.wordpress.com/projects/tinudht/
 * 
 */ 



#include <stdio.h>
#include <stdlib.h>

#include <avr/io.h>
#include <util/delay.h>



/* I2C coms */

#include "i2cmaster.h"

/* LCD */ 
/*
#include "lcd.h"
*/
/* Temp sens */
/*
#include "tinudht.h"
#include "tinudht.c"
*/

#include "twimaster.c"
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

int x; 
int y;
int LED1;
int LED2;
int LEDALL;

int main(void) {   
  /*  
  uart_init(); // open the communication to the microcontroller
  io_redirect(); // redirect input and output to the communication  
  */
  
  DDRC = 0xF0;
  DDRD = 0xFF;
  
  PORTC = 0x3F;
  PORTD = 0x00;

  i2c_init(); 
 // LCD_init(); 
    
  while(1) {
    PORTC = 0x3F;
    /*
    x = KeyPad();
    if(x == -1){
      y = y;
    }
    else{
      y = x;
      _delay_ms(100);
    }
    */
    if(PINC == 0x3E){
      _delay_ms(150);
      if(LED1 == 0x00){
      LED1 = 0x10;
      _delay_ms(15);
      }
      else if(LED1 == 0x10){
        LED1 = 0x00;
        _delay_ms(15);
      }
    }
    else if(PINC == 0x3D){
      _delay_ms(150);
      if(LED2 == 0x00){
        LED2 = 0x20;
        _delay_ms(15);
      }
      else if(LED2 == 0x20){
        LED2 = 0x00;
        _delay_ms(15);
      }
    }
    LEDALL = LED1 ^ LED2;
    PORTD = LEDALL;
  }
  return 0;
}

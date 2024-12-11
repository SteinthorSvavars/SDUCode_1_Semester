/*
 * HelloWorld.c
 *
 * Created: 11/9/2023 10:43:27 AM
 * Author : Alin
 */ 



#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>

#include "usart.h"

int LED1 = 0;
int LED2 = 0;

int main(void) {

  DDRC = 0xF0;
  //DDRD = 0xFF;
  DDRD |= _BV(DDD4);
  
  PORTC = 0x3F;  

  

  while(1){
    PORTC = 0x3F; 
    if(PINC == 0b00111110){
      _delay_ms(150);
      if(LED1 == 0){
        PORTD |= _BV(PORTD4);
      }
      else if(LED1 == 1){
        PORTD &= ~_BV(PORTD4);
      }
      if(LED1 == 0){
        LED1 = 1;
      }
      else if(LED1 == 1){
        LED1 = 0;
      }
  }
  if ((PINC & (1 << 5)) == 0){
      _delay_ms(150);
      if(LED2 == 0){
        LED2 = 1;
      }
      else if(LED2 == 1){
        LED2 = 0;
      }
      if(LED2 == 0){
        PORTD |= _BV(PORTD4);
      }
      else if(LED2 == 1){
        PORTD &= ~_BV(PORTD4);
      }
  }
  }
  return 0;
}

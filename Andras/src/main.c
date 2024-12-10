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

int LED_0 = 0b00000000;
int LED_1 = 0b00000000;
int LED_2 = 0b00000000;
int LED_3 = 0b00000000;
int LED_X = 0b00000000;


int main(void) {  

  DDRC = 0xF0;
  DDRD = 0xFF;
  
  PORTC = 0x3F;

while(1) {

if (PINC == 0b00111110) {
    _delay_ms(150);
    if(LED_0 == 0b00000000){
    LED_0 = 0b00010000;
    _delay_ms(15);
    }else if(LED_0 == 0b00010000){
      LED_0 = 0b00000000;
    _delay_ms(15);
    }
    _delay_ms(150);
    if(LED_1 == 0b00000000){
    LED_1 = 0b00100000;
    _delay_ms(15);
    }else if(LED_1 == 0b00100000){
      LED_1 = 0b00000000;
    _delay_ms(15);
    }
    _delay_ms(150);
    if(LED_2 == 0b00000000){
    LED_2 = 0b01000000;
    _delay_ms(15);
    }else if(LED_2 == 0b01000000){
      LED_2 = 0b00000000;
    _delay_ms(15);
    }
    _delay_ms(150);
    if(LED_3 == 0b00000000){
    LED_3 = 0b10000000;
    _delay_ms(15);
    }else if(LED_3 == 0b10000000){
      LED_3 = 0b00000000;
    _delay_ms(15);
    }
  }
else if (PINC == 0b00111101){
    _delay_ms(150);
    if(LED_0 == 0b00000000){
    LED_0 = 0b00010000;
    _delay_ms(15);
    }else if(LED_0 == 0b00010000){
      LED_0 = 0b00000000;
    _delay_ms(15);
    }
    _delay_ms(150);
    if(LED_1 == 0b00000000){
    LED_1 = 0b00100000;
    _delay_ms(15);
    }else if(LED_1 == 0b00100000){
      LED_1 = 0b00000000;
    _delay_ms(15);
    }
    _delay_ms(150);
    if(LED_2 == 0b00000000){
    LED_2 = 0b01000000;
    _delay_ms(15);
    }else if(LED_2 == 0b01000000){
      LED_2 = 0b00000000;
    _delay_ms(15);
    }
    _delay_ms(150);
    if(LED_3 == 0b00000000){
    LED_3 = 0b10000000;
    _delay_ms(15);
    }else if(LED_3 == 0b10000000){
      LED_3 = 0b00000000;
    _delay_ms(15);
    }
  }
else if (PINC == 0b00111011){
    _delay_ms(150);
    if(LED_0 == 0b00000000){
    LED_0 = 0b00010000;
    _delay_ms(15);
    }else if(LED_0 == 0b00010000){
      LED_0 = 0b00000000;
    _delay_ms(15);
    }
    _delay_ms(150);
    if(LED_1 == 0b00000000){
    LED_1 = 0b00100000;
    _delay_ms(15);
    }else if(LED_1 == 0b00100000){
      LED_1 = 0b00000000;
    _delay_ms(15);
    }
    _delay_ms(150);
    if(LED_2 == 0b00000000){
    LED_2 = 0b01000000;
    _delay_ms(15);
    }else if(LED_2 == 0b01000000){
      LED_2 = 0b00000000;
    _delay_ms(15);
    }
    _delay_ms(150);
    if(LED_3 == 0b00000000){
    LED_3 = 0b10000000;
    _delay_ms(15);
    }else if(LED_3 == 0b10000000){
      LED_3 = 0b00000000;
    _delay_ms(15);
    }
  }
  
  LED_X = LED_0^LED_1^LED_2^LED_3;
  PORTD=LED_X;
  }
}
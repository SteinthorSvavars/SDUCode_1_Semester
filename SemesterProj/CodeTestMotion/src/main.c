/*
 * HelloWorld.c
 *
 * Created: 11/9/2023 10:43:27 AM
 * Author : Alin
 */ 
#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include <Arduino.h>

#include "usart.h"

int LED1 = 0;
int LED2 = 0;
int motion = 0;

int main(void) {
/*
  DDRC = 0xF0;
  DDRD = 0xFF;
  
  PORTC = 0x3F;  

  DDRD |= _BV(DDD4);
*/

  pinMode(19, INPUT);
  pinMode(16, INPUT);
  pinMode(15, INPUT);
  pinMode(14, INPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  digitalWrite(19, LOW);
  digitalWrite(16, HIGH);
  digitalWrite(14, HIGH);
  digitalWrite(15, HIGH);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);

  while(1){
    if(digitalRead(14) == LOW){
      _delay_ms(150);
      if(LED1 == 0){
        LED1 = 1;
      }
      else if(LED1 == 1){
        LED1 = 0;
      }
      if(LED1 == 0){
        digitalWrite(4, HIGH);
      }
      else if(LED1 == 1){
        digitalWrite(4, LOW);
      }
  }
  if(digitalRead(15) == LOW){
      _delay_ms(150);
      if(LED2 == 0){
        LED2 = 1;
      }
      else if(LED2 == 1){
        LED2 = 0;
      }
      if(LED2 == 0){
        digitalWrite(5, HIGH);
      }
      else if(LED2 == 1){
        digitalWrite(5, LOW);
      }
  }
  /*
    if(digitalRead(16) == LOW){
      motion = HIGH;
    }
    if(motion == HIGH){
      if(digitalRead(12)== HIGH){
        digitalWrite(4, HIGH);
      }
      else if(digitalRead(12) == LOW){
        digitalWrite(4, LOW);
      }
      _delay_ms(100);
    }
    */
  }
  return 0;
}

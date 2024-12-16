/*
 * HelloWorld.c
 *
 */ 

#include <stdio.h>
#include <Arduino.h>
#include <util/delay.h>
#include <avr/io.h>
#include "usart.h"
#include "adcpwm.h"

int LED1 = 0;
int LED2 = 0;

int main(void)
{ 
  
  uart_init(); 
  io_redirect();
  adc_init(); // initialize the ADC module
  
  DDRC = 0x0C; // configure pins PC0 to PC3 as inputs
  /*
  DDRD = 0xFF;
  DDRB = 0xF0;
  PORTD = 0x00;
  PORTB = 0x00;
  */
  PORTC = 0x00; // configure pins PC0 to PC3 to not use pullups for the ADC


  DDRC |= _BV(DDC2);
  DDRC |= _BV(DDC3);

  unsigned int adc_value;

  while(1) {
    adc_value = adc_read(6); // Value 0-1023 representing analog voltage on pin PC0
    printf("\n%d", adc_value);
    _delay_ms(100);
    if(adc_value >= 570){
      _delay_ms(150);
      if(LED1 == 0){
        PORTC |= _BV(PORTC2);
      }
      else if(LED1 == 1){
        PORTC &= ~_BV(PORTC2);
      }
      if(LED1 == 0){
        LED1 = 1;
      }
      else if(LED1 == 1){
        LED1 = 0;
      }
    }
    else if(adc_value < 569 && adc_value > 200){
      _delay_ms(150);
      if(LED2 == 0){
        LED2 = 1;
      }
      else if(LED2 == 1){
        LED2 = 0;
      }
      if(LED2 == 0){
        PORTC |= _BV(PORTC3);
      }
      else if(LED2 == 1){
        PORTC &= ~_BV(PORTC3);
      }
    }
  }  
  return 0;
}


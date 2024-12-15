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


int main(void)
{ 
  
  uart_init(); 
  io_redirect();
  adc_init(); // initialize the ADC module

  DDRC = 0xF0; // configure pins PC0 to PC3 as inputs
  DDRD = 0xFF;
  DDRB = 0xF0;
  PORTD = 0x00;
  PORTC = 0xF0; // configure pins PC0 to PC3 to not use pullups for the ADC
  PORTB = 0x00;
 
  DDRD |= _BV(DDD4);
  DDRD |= _BV(DDD5);

  unsigned int adc_value;

  while(1) {
    adc_value = adc_read(0); // Value 0-1023 representing analog voltage on pin PC0
    printf("\n%d", adc_value);
    _delay_ms(100);
    if(adc_value >= 570){
       PORTD |= _BV(PORTD4);
    }
    else if(adc_value < 569 && adc_value > 200){
      PORTD |= _BV(PORTD5);
    }
    else{
      PORTD &=~_BV(PORTD4);
      PORTD &=~_BV(PORTD5);
    }
  }  
  return 0;
}


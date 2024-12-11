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
  //pwm1_init(); // initialize PWM signal at pin PB1, frequency of 4 kHz
  //pwm3_init(); // initialize PWM signal at pin PB0, PB1, PB2 with frequency of 150 Hz
  adc_init(); // initialize the ADC module

  DDRC = 0xF0; // configure pins PC0 to PC3 as inputs
  DDRD = 0xFF;
  DDRB = 0xF0;
  pinMode(12, INPUT); //MotionSensor
  PORTD = 0x00;
  PORTC = 0xF0; // configure pins PC0 to PC3 to not use pullups for the ADC
  PORTB = 0x00;
 
  DDRD |= _BV(DDD4);

  unsigned int adc_value;
  int LED2 = 0;

  while(1)
  {
    if ((PINC & (1 << 5)) == 0){
      _delay_ms(150);
      if(LED2 == 0){
        LED2 = 1;
        PORTB |= _BV(PORTB5);
      }
      else if(LED2 == 1){
        LED2 = 0;
        PORTB &=~_BV(PORTB5);
      }
      if(LED2 == 0){
        PORTD |= _BV(PORTD4);
      }
      else if(LED2 == 1){
        PORTD &= ~_BV(PORTD4);
      }
  }
  if (PINB & (1 << 5)){
    adc_value = adc_read(0); // Value 0-1023 representing analog voltage on pin PC0
  printf("\n%d", adc_value);
    if(adc_value < 650 && digitalRead(12) == HIGH){
      PORTD |= _BV(PORTD4);
    }
    else{
      PORTD &= ~_BV(PORTD4);
    }
    _delay_ms(100);
  }
  }  

  return 0;
}


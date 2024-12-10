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

  DDRC = 0b11110000; // configure pins PC0 to PC3 as inputs
  DDRD = 0xF0;
  DDRB = 0xF0;
  pinMode(17, INPUT); //MotionSensor
  digitalWrite(17, LOW);
  PORTC = 0b00110000; // configure pins PC0 to PC3 to not use pullups for the ADC
  PORTD = 0x00;
  PORTB = 0x00;
 

  unsigned int adc_value;

  while(1)
  {
    adc_value = adc_read(0); // Value 0-1023 representing analog voltage on pin PC0
    if(adc_value < 700 && digitalRead(17) == HIGH){
      PORTB |= _BV(PORTB5);
    }
    else{
      PORTB &=~_BV(PORTB5);
    }
    _delay_ms(100);
  }  

  return 0;
}


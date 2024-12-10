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

  //DDRC = 0b11110000; // configure pins PC0 to PC3 as inputs
  DDRD = 0xF0;
  DDRB = 0xF0;
  pinMode(17, INPUT);
  digitalWrite(17, LOW);

  //PORTC = 0b00110000; // configure pins PC0 to PC3 to not use pullups for the ADC
  PORTD = 0x00;
  PORTB = 0x00;
 

  unsigned int adc_value;

  while(1)
  {
    adc_value = adc_read(0); // Value 0-1023 representing analog voltage on pin PC0
    printf("Result of the ADC conversion : %u\n", adc_value);
    if(adc_value < 700 && digitalRead(17) == HIGH){
      PORTB |= _BV(PORTB5);
    }
    else{
      PORTB &=~_BV(PORTB5);
    }
    /*
    if(digitalRead(17)== HIGH){
      digitalWrite(4, HIGH);
    }
    else{
      //printf("Zero");
      digitalWrite(4, LOW);
    }
    */
    _delay_ms(100);
  }
    
    /*
    if(digitalRead(17) == HIGH){
      PORTD |= _BV(PORTD4);
    }
    else{
      PORTD &=~_BV(PORTD4);
    }
    */
  
    //for (int i = 1; i < 100; i++){
    //pwm3_set_duty(i, i, i); //duty cycles in percent at PB0, PB1, PB2, from 0 - 100
    //pwm1_set_duty(adc_value/10); //duty cycle in percent at PB1, from 0 - 100
   // }
    

  return 0;
}


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
#include "adcpwm.h"
#include "i2cmaster.h"
#include "lcd.h"

/*** Entrance ***/
int LEDENT; int LEDOUT; unsigned int Buttons; unsigned int LDR;

void ENT(Void){
  Buttons = adc_read(6);  // Value 0-1023 representing analog voltage on pin PC6
    _delay_ms(100);
    if(Buttons >= 570){ // When adc read is over 569 entrance light turns on or off
      _delay_ms(150);
      if(LEDENT == 0){  // Turn on
        PORTC |= _BV(PORTC2);
      }
      else if(LEDENT == 1){ //Turn off
        PORTC &= ~_BV(PORTC2);
      }
      if(LEDENT == 0){
        LEDENT = 1;
      }
      else if(LEDENT == 1){
        LEDENT = 0;
      }
    }
    else if(Buttons < 569 && Buttons > 200){  // If adc read under 569 and over 200 outside light turns on or off
      _delay_ms(150);
      if(LEDOUT == 0){
        LEDOUT = 1;
        PORTB |= _BV(PORTB5); // If outside light turned off portb 5 turns on to actiate motion sensor and LDR
      }
      else if(LEDOUT == 1){
        LEDOUT = 0;
        PORTB &=~_BV(PORTB5); // If outside light turned on portb 5 is turned off and deactivates motion and LDR
      }
      if(LEDOUT == 0){
        PORTC |= _BV(PORTC3);
      }
      else if(LEDOUT == 1){
        PORTC &= ~_BV(PORTC3);
      }
    }
    if (PINB & (1 << 5)){
      LDR = adc_read(7); // Value 0-1023 representing analog voltage on pin PC0
      if(LDR < 200 && PINB & (1 << 4)){
        PORTC |= _BV(PORTC3);
      }
      else{
        PORTC &= ~_BV(PORTC3);
      }
      _delay_ms(100);
    } 
}

int main(void) { 

  uart_init(); // open the communication to the microcontroller
  io_redirect(); // redirect input and output to the communication  
  adc_init(); // initialize the ADC module 

  DDRC = 0x0C;  //Pins 0-1 4-7 output / Pins 2&3 input
  
  PORTC = 0x00; //Pins 4-7 Pullup / Pins 0-3 floating

  DDRB |= _BV(DDB5);
  DDRC |= _BV(DDC2);
  DDRC |= _BV(DDC3);
  DDRB &=~_BV(DDB4);

  int input;  

  uart_init(); // open the communication to the microcontroller
  io_redirect(); // redirect input and output to the communication

    
  while(1) {
		
  }
  
  return 0;
}

/*
 * HelloWorld.c
 *
 * Created: 11/9/2023 10:43:27 AM
 * Author : Alin
 * 
 * 
 * 
 */ 

#include <stdio.h>
#include <stdlib.h>
#include <avr/io.h>
#include <util/delay.h>

/* I2C coms */
/*
#include "i2cmaster.h"
*/
/* LCD */ 
/*
#include "lcd.h"
*/
/* Temp sens */
/*

*/

// #include "twimaster.c"
#include "usart.h"
/* ADC */
#include "adcpwmSES.h"

int LED1;
int LED2;

int main(void) {   
    
  uart_init(); // open the communication to the microcontroller
  io_redirect(); // redirect input and output to the communication  
  adc_initSES(); // initialize the ADC module

  
  DDRC = 0x0C;  //Pins 0-1 4-7 output / Pins 2&3 input
  
  PORTC = 0x00; //Pins 4-7 Pullup / Pins 0-3 floating

  DDRB |= _BV(DDB5);
  DDRC |= _BV(DDC2);
  DDRC |= _BV(DDC3);
  DDRB &=~_BV(DDB4);

  unsigned int Buttons;
  unsigned int LDR;
  
  while(1) {
    
    Buttons = adc_readSES(6); // Value 0-1023 representing analog voltage on pin PC0
    //printf("\n %d", Buttons);
    _delay_ms(100);
    if(Buttons >= 570){
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
    else if(Buttons < 569 && Buttons > 200){
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
        PORTC |= _BV(PORTC3);
      }
      else if(LED2 == 1){
        PORTC &= ~_BV(PORTC3);
      }
    }
    if (PINB & (1 << 5)){
      LDR = adc_readSES(7); // Value 0-1023 representing analog voltage on pin PC0
      if(LDR < 400 && PINB & (1 << 4)){
        PORTC |= _BV(PORTC3);
      }
      else{
        PORTC &= ~_BV(PORTC3);
      }
      _delay_ms(100);
    } 
  }
  return 0;
}

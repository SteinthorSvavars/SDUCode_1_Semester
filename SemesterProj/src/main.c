/*
 * HelloWorld.c
 *
 * Created: 11/9/2023 10:43:27 AM
 * Author : Alin
 * 
 * DHT library https://tinusaur.wordpress.com/projects/tinudht/
 * 
 */ 

#include <stdio.h>
#include <stdlib.h>
#include <avr/io.h>
#include <util/delay.h>
#include <Arduino.h>

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

int main(void) {   
  /*  
  uart_init(); // open the communication to the microcontroller
  io_redirect(); // redirect input and output to the communication  
  */
  
  DDRC = 0xF0;  //Pins 4-7 output / Pins 0-3 inputs
  DDRD = 0xFF;  //PIns 0-7 outputs
  DDRB = 0xF0;  //Pins 4-7 output / Pins 0-3 inputs
  
  PORTC = 0xF0; //Pins 4-7 Pullup / Pins 0-3 floating
  PORTD = 0x00; //Pins 0-7 floating
  PORTB = 0x00; //Pins 0-7 floating
  

  //pinMode(12, INPUT); //MotionSensor

  DDRD |= _BV(DDD0); //LED out
  DDRD |= _BV(DDD1); //LED ent
  //DDRB &= ~_BV(DDB4);

  //i2c_init(); 
  //LCD_init(); 

  unsigned int Buttons;
  //unsigned int LDR;
  int LED1;
  int LED2;
    
  while(1) {
    
    Buttons = adc_readSES(2); // Value 0-1023 representing analog voltage on pin PC0
    _delay_ms(100);
    if(Buttons >= 570){
      _delay_ms(150);
      if(LED1 == 0){
        PORTD |= _BV(PORTD0);
      }
      else if(LED1 == 1){
        PORTD &= ~_BV(PORTD0);
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
      }
      else if(LED2 == 1){
        LED2 = 0;
      }
      if(LED2 == 0){
        PORTD |= _BV(PORTD1);
      }
      else if(LED2 == 1){
        PORTD &= ~_BV(PORTD1);
      }
    }
  /*  if (PINB & (1 << 5)){
      LDR = adc_readSES(3); // Value 0-1023 representing analog voltage on pin PC0
      if(LDR < 650 && digitalRead(12) == HIGH){
        PORTD |= _BV(PORTD0);
      }
      else{
        PORTD &= ~_BV(PORTD0);
      }
      _delay_ms(100);
    } */
  }
  return 0;
}

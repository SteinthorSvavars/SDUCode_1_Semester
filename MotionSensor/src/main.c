//Headers
#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include <Arduino.h>

//#include "i2cmaster.h"
//#include "twimaster.c"
#include "usart.h"
//#include "IO_Macros.h"


int main(void){

  pinMode(19, INPUT);
  pinMode(4, OUTPUT);
  digitalWrite(19, LOW);
  digitalWrite(4, LOW);

  uart_init(); // open the communication to the microcontroller
  io_redirect(); // redirect input and output to the communication
  

  while(1){
    if(digitalRead(19)== HIGH){
      digitalWrite(4, HIGH);
    }
    else{
      printf("Zero");
      digitalWrite(4, LOW);
    }
    _delay_ms(1000);
  }
  return 0;
}
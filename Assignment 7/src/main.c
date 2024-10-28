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

int main(void) {  

  int input;  

  /*  
  uart_init(); // open the communication to the microcontroller
  io_redirect(); // redirect input and output to the communication  
  */
  
  DDRC = 0x0F;
  DDRD = 0xF0;
  
    
  while(1) {
		if()

  }
  
  return 0;
}

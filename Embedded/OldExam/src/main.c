/*
 * HelloWorld.c
 *
 * Created: 11/9/2023 10:43:27 AM
 * Author : Alin
 */ 



#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>

/* I2C coms */
#include "i2cmaster.h"

/* LCD */ 
#include "lcd.h"

/* Temp sens */
/*
#include "lm75.c"
#include "lm75.h"
*/

//#include "twimaster.c"
#include "usart.h"

int randomStart(void);
int LCDOutput(void);
int hight[20];

int main(void) {  
  //int input;  
  int x;

  uart_init(); // open the communication to the microcontroller
  io_redirect(); // redirect input and output to the communication

  DDRC = 0xF0;
  DDRD = 0xFF;
  
  PORTC = 0x3F;

  i2c_init(); 
  LCD_init();
  x = randomStart();
  hight[x] = 1;
  LCDOutput();
  while(1) {
    PORTC = 0x3F;
    if((PINC & (1 << 0)) == 0){
      _dealy_ms(150);
      hight[] = hight[] >> 1;
      PORTD |= _BV(PORTD4);
    }
    else if((PINC & (1 << 1)) == 0){
      _dealy_ms(150);
      hight[] = hight[] << 1;
      PORTD &= ~_BV(PORTD4);
    }
    LCDOutput();

  }
  
  return 0;
}


int randomStart(void){
  int r = rand() % 20;
  return r;
}
int LCDOutput(void){
  for(int i = 0; i < 20; i++){
    LCD_set_cursor(i,0);
    printf("%d", hight[i]);
  }
  return 0;
}
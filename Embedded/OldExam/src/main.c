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
#include <limits.h>


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

int hight[20];
int r;
int x; 
int speed = 0;
int num = 2000;

void LCDOutput(void){
  for(int i = 0; i < 20; i++){
    LCD_set_cursor(i,0);
    printf("%d", hight[i]);
    hightSpeed();
  }
}
void shiftLeft(void){
  hight[x] = 0;
  hight[x-1] = 1;
  x--;
  LCDOutput();
}
void shiftRight(void){
  hight[x] = 0;
  hight[x+1] = 1;
  x++;
  LCDOutput();
}
void KeyPad(void) // tekur inn input frá 4x4 keypad
{
    _delay_ms(10);
    if(speed == 1 || speed == 2 || speed == 3 || speed == 4 ||speed == 5){
        switch(speed){
            case 1: num = 2000; PORTD &= ~_BV(PORTD7);    break;     // RD4    
            case 2: num = 1000; PORTD |= _BV(PORTD4);   break;     // RD5
            case 3: num = 500;  PORTD |= _BV(PORTD5); PORTD &= ~_BV(PORTD4);  break;     // RD6
            case 4: num = 333;  PORTD |= _BV(PORTD6); PORTD &= ~_BV(PORTD5);  break;    // RD7
            case 5: num = 250;  PORTD |= _BV(PORTD7); PORTD &= ~_BV(PORTD6);  break;
        }
    }
    _delay_ms(10);
}
void hightSpeed(void){
  for (int i = 0; i < num; i++){
    _delay_ms(1);
  }
}

int main(void) {
  r = rand() % 20;  
  hight[r] = 1;
  x = r; 

  for(int i = 0; i < 20; i++){
    LCD_set_cursor(i,0);
    printf("%d", hight[i]);
  } 

  uart_init(); // open the communication to the microcontroller
  io_redirect(); // redirect input and output to the communication

  DDRC = 0xF0;
  DDRD = 0xFF;
  
  PORTC = 0x3F;
  PORTD = 0x00;

  i2c_init(); 
  LCD_init();

  
  while(1) {
    PORTC = 0x3F;
    
    if((PINC & (1 << 0)) == 0 && hight[0] == 0){
      shiftLeft();
    }
    else if((PINC & (1 << 1)) == 0 && hight[19] == 0){
      shiftRight();
    }
    else if((PINC & (1 << 2)) == 0){
      while ((PINC & (1 << 2)) == 0)
      {
        for(int i = 0; i < 100; i++){
          _delay_ms(5);
        }
      }
      if(speed == 5){
        speed = 0;
      }
      else{
        speed++;
      }
    }
    KeyPad();
    LCDOutput();
  }
  return 0;
}


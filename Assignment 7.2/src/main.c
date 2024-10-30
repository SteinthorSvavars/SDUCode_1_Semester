/*
 * HelloWorld.c
 *
 * Created: 11/9/2023 10:43:27 AM
 * Author : Alin
 */ 
/*

*/


#include <stdio.h>
#include <stdlib.h>

#include <avr/io.h>
#include <util/delay.h>

/* I2C coms */
#include "i2cmaster.h"
/* LCD */ 
#include "lcd.h"
/* Temp sens */
#include "lm75.h"

//#include "twimaster.c"
#include "usart.h"


int main(void) {   
  i2c_init();
  LCD_init();
  lm75_init();
  DDRD = 0xFF;
  PORTD = 0x00;
  DDRC = 0xF0;
  PORTC = 0x3F;

  float current_temp;
  while (1){
    current_temp = get_temperature();
    LCD_set_cursor(0,1);
    printf("temp is %3.2f deg. c: ",current_temp);
    _delay_ms(500);

  }
  

  return 0;
}
/*
 * HelloWorld.c
 *
 * Created: 11/9/2023 10:43:27 AM
 * Author : Alin
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
/*
#include "lm75.c"
#include "lm75.h"
*/

//#include "twimaster.c"
#include "usart.h"
int main(void) {  

  int wheel_Index = 0;  
  int game_results[3];
  //float teljari = 0;
  int balance = 50;
  int lastwin = 0;
  int firstgame = 0;
  int slot1;
  int slot2;
  int slot3;

  uart_init(); // open the communication to the microcontroller
  io_redirect(); // redirect input and output to the communication

  DDRC = 0xF0;
  DDRD = 0xFF;

  PORTC = 0x3F;
  PORTD = 0x00;

  i2c_init(); 
  LCD_init();

  LCD_set_cursor(17,3);
  printf("%d", balance);

  while(1) {
    if(firstgame == 0){
      LCD_set_cursor(0,1);
      printf("Spin the wheel");
    }
    if((PINC & (1<<0)) == 0){
      firstgame = 1;
      LCD_set_cursor(0,1);
      printf("                    ");
      LCD_set_cursor(19,0);
      printf("%d", wheel_Index);
      LCD_set_cursor(0,3);
      printf("            ");
      if(wheel_Index == 0){
        balance -= 10;
        LCD_set_cursor(17,3);
        printf("%d", balance);
      }
      _delay_ms(150);
      PORTD = 0b00010000;
      while((PINC & (1<<0)) == 0){
        for (int i = 0; i < 85 && (PINC & (1<<0)) == 0; i++){
          _delay_ms(1);
        }
        PORTD = PORTD << 1;
        if(PORTD == 0b00000000){
          PORTD = 0b00010000;
        }
      }
      if(PORTD == 0b00000000){
          PORTD = 0b00010000;
        }
      if(PORTD == 0b00010000){
        game_results[wheel_Index] = 1;
        LCD_set_cursor(wheel_Index,0);
        printf("%d", game_results[wheel_Index]);
      }
      else if(PORTD == 0b00100000){
        game_results[wheel_Index] = 2;
        LCD_set_cursor(wheel_Index,0);
        printf("%d", game_results[wheel_Index]);
      }
      else if(PORTD == 0b01000000){
        game_results[wheel_Index] = 3;
        LCD_set_cursor(wheel_Index,0);
        printf("%d", game_results[wheel_Index]);
      }
      else if(PORTD == 0b10000000){
        game_results[wheel_Index] = 4;
        LCD_set_cursor(wheel_Index,0);
        printf("%d", game_results[wheel_Index]);
      } 
      _delay_ms(150);
      wheel_Index++;
      if (wheel_Index > 2){
        wheel_Index = 0;
        LCD_set_cursor(19,0);
        printf("%d", wheel_Index);
        slot1 = game_results[0];
        slot2 = game_results[1];
        slot3 = game_results[2];
        if((slot1 == 4 && slot2 == 3 && slot3 == 2) || (slot1 == 3 && slot2 == 2 && slot3 == 1)){
          balance += 20;
          lastwin = 20;
          LCD_set_cursor(0,3);
          printf("Lucky +20");
          LCD_set_cursor(17,3);
          printf("%d", balance);
        }
        else if((slot1 == 1  && slot2 == 2 && slot3 == 3) || (slot1 == 2 && slot2 == 3 && slot3 == 4)){
          balance += 20;
          lastwin = 20;
          LCD_set_cursor(0,3);
          printf("Lucky +20");
          LCD_set_cursor(17,3);
          printf("%d", balance);
        }
        else if(slot1 == 1 && slot2 == 1 && slot3 == 1){
          balance += 10;
          lastwin = 10;
          LCD_set_cursor(0,3);
          printf("Lucky +10");
          LCD_set_cursor(17,3);
          printf("%d", balance);
        }
        else if(slot1 == 2 && slot2 == 2 && slot3 == 2){
          balance += 20;
          lastwin = 20;
          LCD_set_cursor(0,3);
          printf("Lucky +20");
          LCD_set_cursor(17,3);
          printf("%d", balance);
        }
        else if(slot1 == 3 && slot2 == 3 && slot3 == 3){
          balance += 30;
          lastwin = 30;
          LCD_set_cursor(0,3);
          printf("Lucky +30");
          LCD_set_cursor(17,3);
          printf("%d", balance);
        }
        else if(slot1 == 4 && slot2 == 4 && slot3 == 4){
          balance += 40;
          lastwin = 40;
          LCD_set_cursor(0,3);
          printf("Lucky +40");
          LCD_set_cursor(17,3);
          printf("%d", balance);
        }
        else{
          LCD_set_cursor(0,3);
          printf("Next Time");
        }
        _delay_ms(750);
        LCD_set_cursor(0,3);
        printf("           ");
        LCD_set_cursor(0,0);
        printf("           ");
      }
      if(wheel_Index == 0){
        LCD_set_cursor(0,3);
        printf("Play again");
        if(lastwin != 0){
          LCD_set_cursor(0,2);
          printf("Last win: +%d", lastwin);
        }
        if(balance == 0){
          LCD_set_cursor(0,0);
          printf("                    ");
          LCD_set_cursor(0,1);
          printf("                    ");
          LCD_set_cursor(0,2);
          printf("                    ");
          LCD_set_cursor(0,3);
          printf("                    ");
          LCD_set_cursor(0,1);
          printf("BetterLuckNextTime");
          _delay_ms(500);
          LCD_set_cursor(0,1);
          printf("                    ");
          firstgame = 0;
          balance = 50;
        }
      }
    }
  }return 0;
}
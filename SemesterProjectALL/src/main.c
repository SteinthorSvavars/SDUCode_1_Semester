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

/*** Global ***/
int STOP;
/*** Entrance ***/
int LEDENT; int LEDOUT; unsigned int Buttons; unsigned int LDR;
/*** Hallway ***/
int LEDHALL;
/*** Bedroom ***/

int ModeSelect(void){

}

void ENT(Void){   //Entrence function
int EntranceOn = 1;
do{
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
    if((PIND & (1<<2)) == 0){
      EntranceOn = 0;
    }
  }while(EntranceOn == 1);
}

void HallWay(Void){   //Hallway funtion
  int HallWayOn = 1;
  do{
   if((PIND & (1 << 7)) == 0){
      _delay_ms(150);
      if(LEDHALL == 0){
        PORTD |= _BV(PORTD4);
      }
      else if(LEDHALL == 1){
        PORTD &= ~_BV(PORTD4);
      }
      if(LEDHALL == 0){
        LEDHALL = 1;
      }
      else if(LEDHALL == 1){
        LEDHALL = 0;
      }
    }
    else if((PIND & (1<<2)) == 0){
      HallWayOn = 0;
    }
  }while(HallWayOn == 1);
}

void BedRoom(void){   // Bedroom function
  unsigned int BedRoomPWM; int a; int BedRoomOn = 1;
  do{
    if ((PIND & (1 << 2)) == 0)
      {
        _delay_ms(150);
        if (a == 1) {
          while (a == 1) {
            BedRoomPWM = adc_read(0);
            pwm3_set_duty(BedRoomPWM/4);
            if ((PIND & (1 << 2)) == 0) {
              _delay_ms(150);
              PORTD &= ~_BV(PORTD3);
              a = 0;
            }
            else if((PIND & (1<<2)) == 0){
              BedRoomOn = 0;
            }
          }
        }
      }
    else {
      PORTD &= ~_BV(PORTD3);
    }
  }while(BedRoomOn == 1);
}

int main(void) { 

  uart_init(); // open the communication to the microcontroller
  //io_redirect(); // redirect input and output to the communication
  i2c_init(); 
  LCD_init(); 
  adc_init(); // initialize the ADC module 
  pwm3_init();
  adc_init();

  /*** PORTB ***/
  DDRB |= _BV(DDB0);  // PORTB 0  Hallway Light : D8
  DDRB |= _BV(DDB1);  // PORTB 1  Poul RGB  : D9
  DDRB |= _BV(DDB2);  // PORTB 2  Poul RGB  : D10
  DDRB |= _BV(DDB3);  // PORTB 3  Poul RGB  : D11
  DDRB &=~_BV(DDB4);  // PORTB 4  Motion Sensor : D12
  DDRB |= _BV(DDB5);  // PORTB 5  : Motion LDR controller : D13
  /*** PORTC ***/
  DDRC |= _BV(DDC0);  // PORTC 0  Emilija PWM : A0
  DDRC |= _BV(DDC1);  // PORTC 1  Poul  PWM : A1
  DDRC |= _BV(DDC2);  // PORTC 2  : Entrance light  : A2
  DDRC |= _BV(DDC3);  // PORTC 3  : Outside light   : A3
  //DDRC |= _BV(DDC4);  // PORTC 4  LCD : A4
  //DDRC |= _BV(DDC5);  // PORTC 5  LCD : A5
  //DDRC &= ~_BV(DDC6);  // PORTC 6  Button ENT / OUT: A6  : Analog only
  //DDRC &= ~_BV(DDC7);  // PORTC 7  LDR : A7              : Analog only
  /*** PORTD  ***/
  DDRD |=_BV(DDD0);  // PORTD 0  Rx  : D0
  DDRD |=_BV(DDD1);  // PORTD 1  Tx  : D1
  DDRD &=~_BV(DDD2);  // PORTD 2  Emilija Button : D2
  DDRD &=~_BV(DDD3);  // PORTD 3  Emilija Light  : D3
  DDRD &=~_BV(DDD4);  // PORTD 4  Poul  : D4
  DDRD &=~_BV(DDD5);  // PORTD 5  Select / Stop: D5
  DDRD &=~_BV(DDD6);  // PORTD 6  Next / Lights on/off: D6
  DDRD &=~_BV(DDD7);  // PORTD 7 = input  : Hallway button  : D7

  /*** B ***/
  PORTB &=~ _BV(DDB0);
  PORTB &=~ _BV(DDB1);
  PORTB &=~ _BV(DDB2);
  PORTB &=~ _BV(DDB3);
  PORTB &=~ _BV(DDB4);
  PORTB &=~ _BV(DDB5);

  /*** C ***/
  PORTC = _BV(DDC0);
  PORTC = _BV(DDC1);
  PORTC = _BV(DDC2);
  PORTC = _BV(DDC3);
  //PORTC = _BV(DDC4);
  //PORTC &=~ _BV(DDC5);

  /*** D ***/
  PORTD |= _BV(DDD0);
  PORTD |= _BV(DDD1);
  PORTD = _BV(DDD2);
  PORTD = _BV(DDD3);
  PORTD = _BV(DDD4);
  PORTD = _BV(DDD5);
  PORTD = _BV(DDD6);
  PORTD &=~ _BV(DDD7);
    
  while(1) {
    LCD_set_cursor(0,0);
    printf("ENT");
    LCD_set_cursor(0,1);
    printf("Hall");
    LCD_set_cursor(0,2);
    printf("Bed");
    LCD_set_Cursor(0,3);
    printf("Liv");
  }
  
  return 0;
}

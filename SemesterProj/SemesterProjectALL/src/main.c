#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>

#include "usart.h"
#include "adcpwm.h"
#include "i2cmaster.h"
#include "lcd.h"

/*** Global ***/
int STOP; int Menu = 0;
/*** Entrance ***/
int LEDENT; int LEDOUT; unsigned int Buttons; unsigned int LDR;
/*** Hallway ***/
int LEDHALL;
/*** Bedroom ***/

/*    Keypad
int KeyPad(void) // tekur inn input frá 4x4 keypad
{
    int tala = -1;
    int input;
    int press = 0;
    _delay_ms(10);
    input = PINC;  
    if(input == 0b00111110 || input == 0b00111101 || input == 0b00111011 || input == 0b00110111){
        switch(input){
            case 0b00111110: tala = 1; press++; break;     // RD4    
            case 0b00111101: tala = 2; press++; break;     // RD5
            case 0b00111011: tala = 3; press++; break;     // RD6
            case 0b00110111: tala = 4; press++; break;    // RD7
        }
    }
    _delay_ms(10);
    if((press == 0) && (tala == -1)){
        return tala;
    }
    return tala;
}
*/

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

int x = 0;
int y = 0;
int Counter = 0;

int main(void) { 

  uart_init(); // open the communication to the microcontroller
  //io_redirect(); // redirect input and output to the communication 
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
  //DDRC &=~ _BV(DDC0);  // PORTC 0  Emilija PWM : A0
  //DDRC &=~ _BV(DDC1);  // PORTC 1  Poul  PWM : A1
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
  DDRD |= _BV(DDD3);  // PORTD 3  Emilija Light  : D3
  DDRD |= _BV(DDD4);  // PORTD 4  Poul light  : D4
  DDRD &=~_BV(DDD5);  // PORTD 5  Select / Stop: D5
  DDRD &=~_BV(DDD6);  // PORTD 6  Next / Lights on/off: D6
  DDRD &=~_BV(DDD7);  // PORTD 7 = input  : Hallway button  : D7

  /*** B ***/
  PORTB &=~ _BV(DDB0);
  PORTB &=~ _BV(DDB1);
  PORTB &=~ _BV(DDB2);
  PORTB &=~ _BV(DDB3);
  PORTB |= _BV(DDB4);
  PORTB &=~ _BV(DDB5);

  /*** C ***/
  PORTC &=~ _BV(DDC0);
  PORTC &=~ _BV(DDC1);
  PORTC &=~ _BV(DDC2);
  PORTC &=~ _BV(DDC3);
  //PORTC = _BV(DDC4);
  //PORTC &=~ _BV(DDC5);

  /*** D ***/
  PORTD |= _BV(DDD0);
  PORTD |= _BV(DDD1);
  PORTD |= _BV(DDD2);
  PORTD &=~ _BV(DDD3);
  PORTD &=~ _BV(DDD4);
  PORTD |= _BV(DDD5);
  PORTD |= _BV(DDD6);
  PORTD |= _BV(DDD7);

  i2c_init(); 
  LCD_init();
    
  while(1) {
    if((PIND & (1 << 6)) == 0){
      Counter++;
    }
    if(Counter == 0){     // ENT/Out
      LCD_clear();
      LCD_set_cursor(0,0);
      printf("ENT/OUT");
      LCD_set_cursor(0,1);
      if(PINC & (1 << 2)){
        printf("ENT light On");
      }
      else{
        printf("ENT light Off");
      }
      LCD_set_cursor(0,2);
      if(PINC & (1 << 3)){
        printf("OUT light On");
      }
      else{
        print("OUT light Off");
      }
      LCD_set_cursor(0,3);
      printf("Select     Next");
      if((Counter == 1 && PIND & (1<<6)) == 0){
        ENT();
      }
    }
    else if(Counter == 1){      // Hallway
      LCD_clear();
      LCD_set_cursor(0,0);
      printf("HallWay");
      LCD_set_cursor(0,3);
      printf("Select     Next");
      if((Counter == 2 && PIND & (1<<6)) == 0){
        HallWay();
      }
    }
    else if(Counter == 2){      // Bedroom
      LCD_clear();
      LCD_set_cursor(0,0);
      printf("Bedroom");
      LCD_set_cursor(0,1);
      if(PIND & (1<<3)){
        printf("Light On");
      }
      else{
        printf("Light Off");
      }
      LCD_set_cursor(0,3);
      printf("Select     Next");
      if((Counter == 3 && PIND & (1<<6)) == 0){
        BedRoom();
      }
    }
    else if(Counter == 3){
      LCD_clear();
      LCD_set_cursor(0,0);
      printf("Living room");
      LCD_set_cursor(0,1);
      if(PIND & (1<<4)){
        printf("Light On");
      }
      else{
        printf("Light Off");
      }
      LCD_set_cursor(0,3);
      printf("Select     Next");
      if((Counter == 3 && PIND & (1<<6)) == 0){
        BedRoom();
      }
    }
    
    }return 0; //While (1) end
  }// Int Main end
#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include <Arduino.h> //set framework to arduino 

#include "usart.h"

//const int SensorPin = A6;
const int LEDPin = 2;

int SensorMin = 1023; //LDR min value
int SensorMax = 0; //LDR max value
int SensorValue = 0;

int main(void) {  
  pinMode(A6, INPUT);
  pinMode(13, OUTPUT);
  pinMode(LEDPin, OUTPUT);
  digitalWrite(13, HIGH);
  digitalWrite(LEDPin, LOW);
  //analogWrite(A6, LOW);
  

  uart_init(); // open the communication to the microcontroller
  io_redirect(); // redirect input and output to the communication

  while(millis() < 5000){
    SensorValue = analogRead(A6);
    if(SensorValue > SensorMax){
      SensorMax = SensorValue;
    }
    if(SensorValue < SensorMin){
      SensorMin = SensorValue;
    }
    digitalWrite(13, LOW);
  }

  while(1) {
		SensorValue = analogRead(A6);
    printf("%d", SensorValue);
    //_delay_ms(550);
    SensorValue = constrain(SensorValue, SensorMin, SensorMax);
    //SensorValue = map(SensorValue, SensorMin, SensorMax, 0, 255);
    analogWrite(LEDPin, SensorValue/5);
  }
  
  return 0;
}

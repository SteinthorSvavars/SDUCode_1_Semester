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

int main(void)
{
  int tempweek[7];

  int input;
  int avg = 0;
  int max = 0;
  int min;
  int i;

  uart_init();   // open the communication to the microcontroller
  io_redirect(); // redirect input and output to the communication

  for (i = 0; i <= 7; i++)
  {
    printf("Type temp");
    scanf("%d", &input);
    tempweek[i] = input;
  }
  min = tempweek[0];
  for (i = 0; i <= 7; i++)
  {
    avg = avg + tempweek[i];
    if (max <= tempweek[i])
    {
      max = tempweek[i];
    }
    if (min >= tempweek[i])
    {
      min = tempweek[i];
    }
  }
  for (i = 0; i <= 7; i++)
  {
    printf("%d: ", tempweek[i]);
  }
  printf("\nAvg temp is: %d", avg/7);
  printf("\nMax temp is: %d", max);
  printf("\nMin temp is: %d", min);

  return 0;
}

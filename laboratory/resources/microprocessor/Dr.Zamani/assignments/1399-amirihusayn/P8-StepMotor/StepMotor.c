/*******************************************************
Project : StepMotor
Version : 
Date    : 15/12/2020
Author  : 
Company : 
Comments: 

Chip type               : ATmega16
Program type            : Application
AVR Core Clock frequency: 8/000000 MHz
Memory model            : Small
External RAM size       : 0
Data Stack size         : 256
*******************************************************/

#include <mega16.h>
#include <delay.h>

unsigned char halfStep[8] = { 0x08 , 0x0C , 0x04 , 0x06 , 0x02 , 0x03 , 0x01 ,0x09 };
unsigned char fullStep[4] = { 0x08 , 0x04 , 0x02 , 0x01 };
unsigned char fastFullStep[4] = { 0x09 , 0x0C , 0x06 , 0x03 };


/******************************************************/
/******************************************************/
/*************** HalfStep *****************************/

void HalfStep_AntiClockWise()
{
      unsigned char index;
      for(index = 0; index < 8; index++)
      {
            PORTB = halfStep[index];
            delay_ms(100);
      }
}
void HalfStep_ClockWise()
{
      int index;
      for(index = 7; index >= 0; index--)
      {
            PORTB = halfStep[index];
            delay_ms(100);
      }
}

/******************************************************/
/******************************************************/
/**************** FullStep ****************************/

void FullStep_AntiClockWise()
{
      unsigned char index;
      for(index = 0; index < 4; index++)
      {
            PORTB = fullStep[index];
            delay_ms(100);
      }
}
void FullStep_ClockWise()
{
      int index;
      for(index = 3; index >= 0; index--)
      {
            PORTB = fullStep[index];
            delay_ms(100);
      }
}

/******************************************************/
/***************** Fast FullStep **********************/

void FullStep_Fast_AntiClockWise()
{
      unsigned char index;
      for(index = 0; index < 4; index++)
      {
            PORTB = fastFullStep[index];
            delay_ms(100);
      }
}
void FullStep_Fast_ClockWise()
{
     int index;
      for(index = 3; index >= 0; index--)
      {
            PORTB = fastFullStep[index];
            delay_ms(100);
      }
}

/******************************************************/
/**************** Turn using speed parameter **********/

void Turn(unsigned char speed)
{
      switch(speed)
      {
            case 0 :
            {
                  HalfStep_ClockWise();
                  break;
            }
            case 1 :
            {
                  FullStep_ClockWise();
                  break;
            }
            case 2 :
            {
                  FullStep_Fast_ClockWise();
                  break;
            }
            default :
            break;
      }
}

/******************************************************/
/******************************************************/

void main(void)
{
      unsigned char counter;

      PORTB = 0x00;
      DDRB = 0xff;

      while (1)
      {
            // HalfStep
            HalfStep_AntiClockWise();
            delay_ms(180);

            HalfStep_ClockWise();
            delay_ms(180);


            // FullStep
            FullStep_AntiClockWise();
            delay_ms(180);

            FullStep_ClockWise();
            delay_ms(180);


            // Fast FullStep
            FullStep_Fast_AntiClockWise();
            delay_ms(180);

            FullStep_Fast_ClockWise();
            delay_ms(180);

            // Turn by speed and clockwise option
            Turn(2);
            delay_ms(180);
      }
}

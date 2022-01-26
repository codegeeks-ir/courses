#include<mega16.h>
#include<delay.h>


unsigned char LEDNumber;
unsigned char counter;

void TurnRight(){
      LEDNumber = ( LEDNumber >> 1 ) | ( LEDNumber << (8 - 1) );
      PORTD = LEDNumber;
}
void TurnLeft(){
      LEDNumber = ( LEDNumber << 1 ) | ( LEDNumber >> (8 - 1) );
      PORTD = LEDNumber;
}
void DelayBetweenOperations(){
      delay_ms(50);
      PORTD = 0xff;
      delay_ms(20);  
      PORTD = 0x00;
      delay_ms(50);
}


void main(){
      DDRD = 0xff;
      PORTD = 0x00;

    while(1){

          for (counter = 0; counter < 16; counter++){
                PORTD.0 = ~ PORTD.0;
                delay_ms(20);  
          }
          DelayBetweenOperations();
          

          // answer of question 1
          for (counter = 0; counter < 16; counter++){
                PORTD.4 = ~ PORTD.4;
                delay_ms(20);  
          }
          DelayBetweenOperations();


          // answer of question 2
           // very fast blink that we can not see it in very low delay.
          for (counter = 0; counter < 128; counter++){
                PORTD.4 = ~ PORTD.4;
                delay_ms(5);  
          }
          DelayBetweenOperations();

          // answer of question 3
          PORTD.4 = 1;
          delay_ms(100);  
          PORTD.4 = 0;
          delay_ms(200);  
          DelayBetweenOperations();


          // answer of question 4
          LEDNumber = 0b00000001;
          for (counter = 0; counter < 16; counter++){
                TurnRight();
                delay_ms(20);
          }
          DelayBetweenOperations();


          // answer of question 5
          LEDNumber = 0b10000000;
          for (counter = 0; counter < 16; counter++){
                TurnLeft();
                delay_ms(20);
          }
          DelayBetweenOperations();


          // answer of question 6
          LEDNumber = 0b11000000;
          for (counter = 0; counter < 16; counter++){
                TurnRight();
                delay_ms(20);
          }
          DelayBetweenOperations();


          // answer of question 7
          LEDNumber = 0b01010101;
          for (counter = 0; counter < 32; counter++){
                LEDNumber = ~ LEDNumber;
                PORTD = LEDNumber;
                delay_ms(20);
          }
          DelayBetweenOperations();


          // answer of question 8
           // Turning will be slow in and fast out.
          LEDNumber = 0b10000000;
          for (counter = 0; counter < 32; counter++){
                TurnRight();
                delay_ms(200/(counter+1));
          }
          DelayBetweenOperations();
    }
}
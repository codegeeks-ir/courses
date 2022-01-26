#include<mega16.h>
#include<delay.h>

unsigned char row[8];
unsigned char i;
unsigned char rowIndex;
unsigned char columnNumber;

void MakeRows_A(){
      row[0] = 0b00000000;
      row[1] = 0b00011000;
      row[2] = 0b00100100;
      row[3] = 0b00111100;
      row[4] = 0b00100100;
      row[5] = 0b00100100;
      row[6] = 0b00000000;
      row[7] = 0b00000000;
}
void MakeRows_B(){
      row[0] = 0b00000000;
      row[1] = 0b00111000;
      row[2] = 0b00100100;
      row[3] = 0b00111100;
      row[4] = 0b00100100;
      row[5] = 0b00111000;
      row[6] = 0b00000000;
      row[7] = 0b00000000;
}
void MakeRows_7(){
      row[0] = 0b00000000;
      row[1] = 0b00111110;
      row[2] = 0b00100100;
      row[3] = 0b00001110;
      row[4] = 0b00000100;
      row[5] = 0b00000100;
      row[6] = 0b00000000;
      row[7] = 0b00000000;
}
void NextColumn()
{
      // Rotational Left Shift for column numbers
      columnNumber = ( columnNumber << 1 ) | ( columnNumber >> (8-1) );
}
void Show(){
      columnNumber = 0b11111110;
      for (rowIndex = 0; rowIndex < 8 ; rowIndex++){
            PORTB = columnNumber;
            PORTD = row[rowIndex];
            delay_ms(1);
            NextColumn();
      }
}


void main(){
      DDRB = 0xff;
      DDRD = 0xff;

      while(1){
            // Shows A :
            MakeRows_A();
            for (i = 0; i < 25; i++){
                  Show();
            }

            // Answer of question 1 :
            // Shows B :
            MakeRows_B();
            for (i = 0; i < 25; i++){
                  Show();
            }

            // Answer of question 2 :
            // Shows 7 :
            MakeRows_7();
            for (i = 0; i < 25; i++){
                  Show();
            }
      }
}
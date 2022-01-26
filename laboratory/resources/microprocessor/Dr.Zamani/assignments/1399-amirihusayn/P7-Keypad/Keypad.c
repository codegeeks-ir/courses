/*******************************************************
Project : Keypad
Version : 
Date    : 08/12/2020
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
#include <alcd.h>

unsigned char rowNumber;
char rowChars[] = "741c";

void AssignRowChars(char ch0 ,char ch1 ,char ch2 ,char ch3)
{
      rowChars[0] = ch0;
      rowChars[1] = ch1;
      rowChars[2] = ch2;
      rowChars[3] = ch3;  
}
void ChooseRelatedRow()
{
      if(rowNumber == 0b11111110)
      {
            AssignRowChars('7','4','1','c');
      }
      else if (rowNumber == 0b11111101)
      {
            AssignRowChars('8','5','2','0');
      }
      else if (rowNumber == 0b11111011)
      {
            AssignRowChars('9','6','3','=');
      }
      else if (rowNumber == 0b11110111)
      {
            AssignRowChars('/','*','-','+');
      }  
}

void CheckRow()
{
      PORTB = rowNumber;
      ChooseRelatedRow();
      delay_ms(2);
      lcd_gotoxy(1,1);

      if(PIND.0 == 0)
      {
            lcd_gotoxy(1,1);
            lcd_putchar(rowChars[0]);
      }
      else if (PIND.1 == 0)
      {
            lcd_gotoxy(1,1);
            lcd_putchar(rowChars[1]); 
      }
      else if (PIND.2 == 0)
      {
            lcd_gotoxy(1,1);
            lcd_putchar(rowChars[2]);
      }
      else if (PIND.3 == 0)
      {
            lcd_gotoxy(1,1);
            lcd_putchar(rowChars[3]);
      }  
}

void main(void)
{
      DDRA = 0xff;
      DDRB = 0xff;
      DDRD = 0x00;

      // Alphanumeric LCD initialization
      // Connections are specified in the
      // Project|Configure|C Compiler|Libraries|Alphanumeric LCD menu:
      // RS - PORTA Bit 0
      // RD - PORTA Bit 1
      // EN - PORTA Bit 2
      // D4 - PORTA Bit 4
      // D5 - PORTA Bit 5
      // D6 - PORTA Bit 6
      // D7 - PORTA Bit 7
      // Characters/line: 16
      lcd_init(16);
      lcd_gotoxy(0,0);
      lcd_puts("Press a key");
      delay_ms(100);
      lcd_clear();
      lcd_gotoxy(1,1);

      while (1)
      {
            rowNumber = 0b11111110;
            CheckRow();

            rowNumber = 0b11111101;
            CheckRow();

            rowNumber = 0b11111011;
            CheckRow();

            rowNumber = 0b11110111;
            CheckRow();
      }
}

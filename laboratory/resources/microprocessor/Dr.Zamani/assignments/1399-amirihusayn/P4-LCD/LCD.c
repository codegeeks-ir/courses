/*****************************************************
Project : LCD
Version : 
Date    : 17/11/2020
Author  : Freeware, for evaluation and non-commercial use only
Company : 
Comments: 


Chip type               : ATmega16
Program type            : Application
AVR Core Clock frequency: 8/000000 MHz
Memory model            : Small
External RAM size       : 0
Data Stack size         : 256
*****************************************************/

#include <mega16.h>
#include <delay.h>
#include <alcd.h>
#include <string.h>


void ShowInCenter(const char *firstRow , const char *secondRow)
{
      unsigned char offset;
      lcd_clear();

      offset = (16 - strlen(firstRow)) / 2;
      lcd_gotoxy(offset,0);
      lcd_puts(firstRow);
      delay_ms(200);

      offset = (16 - strlen(secondRow)) / 2;
      lcd_gotoxy(offset,1);
      lcd_puts(secondRow);
      delay_ms(200);
}
void Show(const char *firstRow , const char *secondRow)
{
      lcd_gotoxy(0,0);
      lcd_puts(firstRow);

      lcd_gotoxy(0,1);
      lcd_puts(secondRow);
}
void Blink(const char *firstRow , const char *secondRow)
{
      unsigned char index;
      for(index = 0; index < 100; index++)
      {
            lcd_clear();
            delay_ms(20);
            Show(firstRow , secondRow);
            delay_ms(20);
      }
}

void main(void)
{
      // Alphanumeric LCD initialization
      // Connections specified in the
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
      lcd_putsf("RN-MICRO+");
      delay_ms(200);
      lcd_gotoxy(0,1);
      lcd_putsf("www.rayannik.com");
      delay_ms(200);

      // Answer of question 1
      lcd_clear();
      lcd_putsf("UUT");
      delay_ms(200);
      lcd_gotoxy(0,1);
      lcd_putsf("www.uut.ac.ir");
      delay_ms(200);

      // Answer of question 2
      ShowInCenter("Micro" , "Atmega16");

      // Answer of question 3
      Blink("Some blink !" , ";D");

      while (1)
      {

      }
}

/*****************************************************
Project : LCD2
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

int index;

void TurnRigth(const char *firstRow , const char *secondRow)
{
      for(index = 0; index < 16; index++)
      {
            lcd_gotoxy(index,1);
            lcd_putchar(secondRow[index]);
            delay_ms(30);
      }
      delay_ms(50);

      for(index = 0; index < 16; index++)
      {
            lcd_gotoxy(index,1);
            lcd_putchar(' ');
            delay_ms(30);
      }
      delay_ms(50);

      for(index = 0; index <= 16; index++)
      {
            lcd_gotoxy(index,0);
            lcd_puts(firstRow);
            delay_ms(60);
            lcd_clear();
      }
      delay_ms(100);
}
void TurnLeft(const char *firstRow , const char *secondRow)
{
      for(index = 15; index >= 0; index--)
      {
            lcd_gotoxy(index,1);
            lcd_putchar(secondRow[index]);
            delay_ms(30);
      }
      delay_ms(50);

      for(index = 15; index >= 0; index--)
      {
            lcd_gotoxy(index,1);
            lcd_putsf(" ");
            delay_ms(30);
      }
      delay_ms(50);

      for(index = 16; index >= 0; index--)
      {
            lcd_gotoxy(index,0);
            lcd_puts(firstRow);
            delay_ms(60);
            lcd_clear();
      }
      delay_ms(100);
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

      while (1)
      {
            TurnRigth("RN_MICRO+" , "www.rayannik.com");

            // Answer of question 1
            TurnRigth("UUT" , "www.uut.ac.ir   ");

            // Answer of question 2
            TurnLeft("RN_MICRO+" , "www.rayannik.com");
      }
}

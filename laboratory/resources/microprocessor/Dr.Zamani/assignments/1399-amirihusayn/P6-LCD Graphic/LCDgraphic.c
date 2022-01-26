/*******************************************************
Project : LCDgraphic
Version : 
Date    : 02/12/2020
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

// Graphic Display functions
#include <glcd.h>

// Font used for displaying text
// on the graphic display
#include <font5x7.h>

/******************************************************/

#define RS PORTB.0
#define RW PORTB.1
#define E PORTB.2
#define CS1 PORTB.3
#define CS2 PORTB.4
#define Reset PORTB.5
#define DATA_LCD PORTD

/******************************************************/
unsigned char addrx_cs1 = 0 , addrx_cs2 = 0 , line = 0;
unsigned int pointer = 0;
flash unsigned char dis[1024] = 
{
255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255, 255,
255,255,255,255,255,255,255,255,255,255,255,255,255,255,255, 255,255,
255,255,255,255,255,255,255,255,255,255,255,255,255,255, 255,255,255,
255,255,255,255,255,255,255,255,255,255,255,255,255, 255,255,255,255,
255,255,255,255,255,255,255,255,255,255,255,255, 255,255,255,255,255,
255,255,255,255,255,255,255,255,255,255,255, 255,255,255,255,255,255,
255,255,255,255,255,255,255,255,255,255, 255,255,255,255,255,255,255,
255,255,255,255,255,255,255,255,255, 255,255,255,255,255,255,255,255,
255,255,255,255,255,255,255,255, 255,255,255,255,255,255,255,127, 63,
 63, 31, 15,  7,  7,  3,  3, 131,129,193,193,193,224,224,224,224,224,
 224,224,224,224,193,193, 193,129,131,  3,  3,  7,  7, 15, 31, 31, 63,
  63, 63, 31, 15, 15, 7,  7,  3,  3,  3,  1,  1,  1,  0,  0,  0,  0,  0,
    0,  0,  0, 0,  0,  0,  1,  1,  1,  3,  3,  3,  7,  7, 15, 15, 31, 63,
     63, 127,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
      255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255, 255,
      255,255,255,255,255,255,255,255,255,255,255,255,255,255,255, 255,255,
       63, 15,  3,  1,  0,128,192,240,248,252,254,254,255,255, 255,255,255,
         7,247,247,247,247,247,247,231,239,207,159, 63,255, 255,255,255,255,
         255, 62, 14,  4,  0,  0,  0,  0,  0,  0,  0,  0, 0,  0,  0,  0,  0,
           0,248,224,128,  0,  0,  0,  0,  0,  0,  0, 0,  0,  0,  0,  0,  0,
             0,248,  0,  0,  0,  0,  0,  0,  0,  0, 0,  0,  1,  7, 15, 63,255,
             255,255,255,255,255,255,255,255,255, 255,255,255,255,255,255,255,
             255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
             255,255,255,255,255,255,255,255,255, 7,  0,  0,  0,  0,240,254,
             255,255,255,255,255,255,255,255,255, 255,255,255,  0, 63, 63,191,
             191,191,191,191,159,223,223,207,224, 255,255,255, 15,  1,  0,  0,
               0,  0,  0,  0,  0,  0,  0,  0,  0, 0,  0,  0,  0,  0,  0,255,  0,
                 3,  6, 12, 24, 48, 96,192,128, 0,  0,  0,  0,  0,  0,  0,255,  0,
                   0,  0,  0,  0,  0,  0,  0, 0,  0,  0,  0,  0,  0,  0,  7,255
                   ,255,255,255,255,255,255,255, 255,255,255,255,255,255,255,255,
                   255,255,255,255,255,255,255,255, 255,255,255,255,255,255,255,
                   255,255,255,255,255,255,255,255,255, 224,  0,  0,  0,  0, 15
                   ,127,255,255,255,255,255,255,255,255,255, 255,255,255,  0,255,
                   254,252,253,251,243,231,207,223,159, 63,127, 255,255,255,240,
                     0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0,  0,  0,  0,
                       0,  0,255,  0,  0,  0,  0,  0,  0,  0,  0,  1, 3,  6, 12, 24,
                       112,192,128,255,  0,  0,  0,  0,  0,  0,  0, 0, 0,  0,  0,  0,
                         0,  0,  0,224,255,255,255,255,255,255,255,255, 255,255,255,255,
                         255,255,255,255,255,255,255,255,255,255,255,255, 255,255,255,255,
                         255,255,255,255,255,255,255,255,255,255,255,255, 255,255,252,240,192,128,
                           0,  1,  7, 15, 31, 63,127,127,255,255, 255,255,255,248,255,255,255,255,255,
                           255,255,255,255,255,255,254, 252,249,251,255,255,124,112, 
                           32,  0,  0,  0,  0,  0,  0,  0,  0, 0,  0,  0,  0,  0,  0,  
                           7,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0,  0,  0,  0,  0,  
                           0,  1, 15,  0,  0,  0,  0,  0,  0,  0,  0, 0,  0,128,224,240,
                           252,255,255,255,255,255,255,255,255,255,255, 255,255,255,255,
                           255,255,255,255,255,255,255,255,255,255,255,255, 255,255,255,
                           255,255,255,255,255,255,255,255,255,255,255,255,255, 255,255,
                           255,255,255,255,255,254,252,248,248,240,224,224,192,192, 193,
                           129,131,131,  3,  7,  7,  7,  7,  7,  7,  7,  7,  7,  3,131, 
                           131,131,193,193,192,224,224,240,248,248,252,252,252,248,240,240,
                            224,224,192,192,128,128,128,128,  0,  0,  0,  0,  0,  0,  0,  0,
                             0,  0,  0,128,128,128,128,192,192,224,224,240,240,248,252,252, 
                             254,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
                              255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
                               255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
                                255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255, 
                                255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
                                 255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
                                  255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
                                   255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
                                    255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
                                     255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255 
};

/******************************************************/
flash unsigned char dis2[1024] = {
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
 224, 32, 16, 24,  8,  8,  8,  8, 16, 16, 32, 64,128,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,128, 64, 32, 16, 16,  8,  8,  8,  8, 24, 16, 32,224,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 15, 
  48,192,  0,  0,  0,  0,  0,  0,  0,  0,128, 96, 31,  0,  0,  0, 
 128,192, 96,112,156,148,152,144,144,240,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,240,144,144,152,148,156,112, 96,192,128,  0,  0, 
   0, 31, 96,128,  0,  0,  0,  0,  0,  0,  0,  0,192, 48, 15,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,192, 32, 16,  8, 
 136,132,  5,  2,  0,  0,  0,  0,  1,  1,  2,194, 50,  9,  9,  9, 
   4,  2,  2,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  2,  2,  4,  9,  9, 
   9, 50,194,  2,  1,  1,  0,  0,  0,  0,  2,  5,132,136,  8, 16, 
  32,192,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0, 96,146,141,137,129, 65, 50, 26,  9,  4,  4,  2,  2,  1, 
   0,128,127,  0,  0,  0,  0,  0,  0,  0,  0,  7, 24,224,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
 224, 24,  7,  0,  0,  0,  0,  0,  0,  0,  0,127,128,  0,  1,  2, 
   2,  4,  4,  9, 26, 50, 65,129,137,141,146, 96,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128, 
 252,  7,  0,  0,192,120,  6,  1, 14, 32,192,  0,  0, 47,192,  0, 
   0,  0,  0, 48,  8,  8,  4,  4,  4,  4,  8,  8, 48,192,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
 255,  0,  0,  0,240, 14,  1,  6,120,192,  0,  0,  7,252,128,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 56, 39, 
  32, 32, 32, 23,  8,  0,  0,  0,  0,  8, 23, 32, 32, 64, 65, 78, 
  88, 48,  0, 12, 16, 16, 32, 32, 32, 32, 16, 16, 12,  3,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 16, 56, 44, 39, 
  32, 32, 16, 16, 11,  4,  0,  0,  0,  8, 23, 32, 32, 32, 39, 56, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
};

/**************************************************************/

void Data_Command()
{
      delay_us(500);
      RS = 0;
      RW = 0;
      E = 1;
      delay_us(1);
      E = 0;
}
void Data_Display()
{
      delay_us(500);
      RS = 1;
      RW = 0;
      E = 1;
      delay_us(1);
      E = 0;
}
void Table()
{
      unsigned char i;
      for(i = 0; i < 64; i++)
      {
            DATA_LCD = dis[pointer];
            pointer++;
            Data_Display();
      }
}
void Display_Right()
{
      DATA_LCD = 0x40;
      Data_Command();
      addrx_cs1++;
      DATA_LCD = addrx_cs1;
      Data_Command();
      DATA_LCD = 0x3f;
      Data_Command();
      Table();
}
void Display_Left()
{
      DATA_LCD = 0x40;
      Data_Command();
      addrx_cs2++;
      DATA_LCD = addrx_cs2;
      Data_Command();
      DATA_LCD = 0x3f;
      Data_Command();
      Table();
}
void Setting()
{
      unsigned char j;
      for(j = 0; j < line; j++)
      {
            CS1 = 1;
            CS2 = 0;
            Display_Left();
            CS1 = 0;
            CS2 = 1;
            Display_Right();
      }
}
void Reset_gLCD()
{
      Reset = 0;
      delay_us(3);
      Reset = 1;
}
void Display()
{
      addrx_cs1 = 0xb7;
      addrx_cs2 = 0xb7;
      line = 8;
      Setting();
}


void Table2()
{
      unsigned char i;
      for(i = 0; i < 64; i++)
      {
            DATA_LCD = dis2[pointer];
            pointer++;
            Data_Display();
      }
}
void Display_Right2()
{
      DATA_LCD = 0x40;
      Data_Command();
      addrx_cs1++;
      DATA_LCD = addrx_cs1;
      Data_Command();
      DATA_LCD = 0x3f;
      Data_Command();
      Table2();
}
void Display_Left2()
{
      DATA_LCD = 0x40;
      Data_Command();
      addrx_cs2++;
      DATA_LCD = addrx_cs2;
      Data_Command();
      DATA_LCD = 0x3f;
      Data_Command();
      Table2();
}
void Setting2()
{
      unsigned char j;
      for(j = 0; j < line; j++)
      {
            CS1 = 1;
            CS2 = 0;
            Display_Left2();
            CS1 = 0;
            CS2 = 1;
            Display_Right2();
      }
}
void Display2()
{
      addrx_cs1 = 0xb7;
      addrx_cs2 = 0xb7;
      line = 8;
      Setting2();
}


void main(void)
{
// Declare your local variables here
// Variable used to store graphic display
// controller initialization data
GLCDINIT_t glcd_init_data;

// Input/Output Ports initialization
// Port A initialization
// Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In 
DDRA=(0<<DDA7) | (0<<DDA6) | (0<<DDA5) | (0<<DDA4) | (0<<DDA3) | (0<<DDA2) | (0<<DDA1) | (0<<DDA0);
// State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T 
PORTA=(0<<PORTA7) | (0<<PORTA6) | (0<<PORTA5) | (0<<PORTA4) | (0<<PORTA3) | (0<<PORTA2) | (0<<PORTA1) | (0<<PORTA0);

// Port B initialization
// Function: Bit7=Out Bit6=Out Bit5=Out Bit4=Out Bit3=Out Bit2=Out Bit1=Out Bit0=Out 
DDRB=(1<<DDB7) | (1<<DDB6) | (1<<DDB5) | (1<<DDB4) | (1<<DDB3) | (1<<DDB2) | (1<<DDB1) | (1<<DDB0);
// State: Bit7=0 Bit6=1 Bit5=1 Bit4=1 Bit3=1 Bit2=1 Bit1=1 Bit0=1 
PORTB=(0<<PORTB7) | (1<<PORTB6) | (1<<PORTB5) | (1<<PORTB4) | (1<<PORTB3) | (1<<PORTB2) | (1<<PORTB1) | (1<<PORTB0);

// Port C initialization
// Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In 
DDRC=(0<<DDC7) | (0<<DDC6) | (0<<DDC5) | (0<<DDC4) | (0<<DDC3) | (0<<DDC2) | (0<<DDC1) | (0<<DDC0);
// State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T 
PORTC=(0<<PORTC7) | (0<<PORTC6) | (0<<PORTC5) | (0<<PORTC4) | (0<<PORTC3) | (0<<PORTC2) | (0<<PORTC1) | (0<<PORTC0);

// Port D initialization
// Function: Bit7=Out Bit6=Out Bit5=Out Bit4=Out Bit3=Out Bit2=Out Bit1=Out Bit0=Out 
DDRD=(1<<DDD7) | (1<<DDD6) | (1<<DDD5) | (1<<DDD4) | (1<<DDD3) | (1<<DDD2) | (1<<DDD1) | (1<<DDD0);
// State: Bit7=1 Bit6=1 Bit5=1 Bit4=1 Bit3=1 Bit2=1 Bit1=1 Bit0=1 
PORTD=(1<<PORTD7) | (1<<PORTD6) | (1<<PORTD5) | (1<<PORTD4) | (1<<PORTD3) | (1<<PORTD2) | (1<<PORTD1) | (1<<PORTD0);

// Timer/Counter 0 initialization
// Clock source: System Clock
// Clock value: Timer 0 Stopped
// Mode: Normal top=0xFF
// OC0 output: Disconnected
TCCR0=(0<<WGM00) | (0<<COM01) | (0<<COM00) | (0<<WGM01) | (0<<CS02) | (0<<CS01) | (0<<CS00);
TCNT0=0x00;
OCR0=0x00;

// Timer/Counter 1 initialization
// Clock source: System Clock
// Clock value: Timer1 Stopped
// Mode: Normal top=0xFFFF
// OC1A output: Disconnected
// OC1B output: Disconnected
// Noise Canceler: Off
// Input Capture on Falling Edge
// Timer1 Overflow Interrupt: Off
// Input Capture Interrupt: Off
// Compare A Match Interrupt: Off
// Compare B Match Interrupt: Off
TCCR1A=(0<<COM1A1) | (0<<COM1A0) | (0<<COM1B1) | (0<<COM1B0) | (0<<WGM11) | (0<<WGM10);
TCCR1B=(0<<ICNC1) | (0<<ICES1) | (0<<WGM13) | (0<<WGM12) | (0<<CS12) | (0<<CS11) | (0<<CS10);
TCNT1H=0x00;
TCNT1L=0x00;
ICR1H=0x00;
ICR1L=0x00;
OCR1AH=0x00;
OCR1AL=0x00;
OCR1BH=0x00;
OCR1BL=0x00;

// Timer/Counter 2 initialization
// Clock source: System Clock
// Clock value: Timer2 Stopped
// Mode: Normal top=0xFF
// OC2 output: Disconnected
ASSR=0<<AS2;
TCCR2=(0<<PWM2) | (0<<COM21) | (0<<COM20) | (0<<CTC2) | (0<<CS22) | (0<<CS21) | (0<<CS20);
TCNT2=0x00;
OCR2=0x00;

// Timer(s)/Counter(s) Interrupt(s) initialization
TIMSK=(0<<OCIE2) | (0<<TOIE2) | (0<<TICIE1) | (0<<OCIE1A) | (0<<OCIE1B) | (0<<TOIE1) | (0<<OCIE0) | (0<<TOIE0);

// External Interrupt(s) initialization
// INT0: Off
// INT1: Off
// INT2: Off
MCUCR=(0<<ISC11) | (0<<ISC10) | (0<<ISC01) | (0<<ISC00);
MCUCSR=(0<<ISC2);

// USART initialization
// USART disabled
UCSRB=(0<<RXCIE) | (0<<TXCIE) | (0<<UDRIE) | (0<<RXEN) | (0<<TXEN) | (0<<UCSZ2) | (0<<RXB8) | (0<<TXB8);

// Analog Comparator initialization
// Analog Comparator: Off
// The Analog Comparator's positive input is
// connected to the AIN0 pin
// The Analog Comparator's negative input is
// connected to the AIN1 pin
ACSR=(1<<ACD) | (0<<ACBG) | (0<<ACO) | (0<<ACI) | (0<<ACIE) | (0<<ACIC) | (0<<ACIS1) | (0<<ACIS0);
SFIOR=(0<<ACME);

// ADC initialization
// ADC disabled
ADCSRA=(0<<ADEN) | (0<<ADSC) | (0<<ADATE) | (0<<ADIF) | (0<<ADIE) | (0<<ADPS2) | (0<<ADPS1) | (0<<ADPS0);

// SPI initialization
// SPI disabled
SPCR=(0<<SPIE) | (0<<SPE) | (0<<DORD) | (0<<MSTR) | (0<<CPOL) | (0<<CPHA) | (0<<SPR1) | (0<<SPR0);

// TWI initialization
// TWI disabled
TWCR=(0<<TWEA) | (0<<TWSTA) | (0<<TWSTO) | (0<<TWEN) | (0<<TWIE);

// Graphic Display Controller initialization
// The KS0108 connections are specified in the
// Project|Configure|C Compiler|Libraries|Graphic Display menu:
// DB0 - PORTD Bit 0
// DB1 - PORTD Bit 1
// DB2 - PORTD Bit 2
// DB3 - PORTD Bit 3
// DB4 - PORTD Bit 4
// DB5 - PORTD Bit 5
// DB6 - PORTD Bit 6
// DB7 - PORTD Bit 7
// E - PORTB Bit 2
// RD /WR - PORTB Bit 1
// RS - PORTB Bit 0
// /RST - PORTB Bit 5
// CS1 - PORTB Bit 3
// CS2 - PORTB Bit 4

// Specify the current font for displaying text
glcd_init_data.font=font5x7;
// No function is used for reading
// image data from external memory
glcd_init_data.readxmem=NULL;
// No function is used for writing
// image data to external memory
glcd_init_data.writexmem=NULL;

glcd_init(&glcd_init_data);

Reset_gLCD();
Display();
delay_ms(100);

// Answer of question
addrx_cs1 = 0 ;
addrx_cs2 = 0 ;
line = 0;
pointer = 0;
Reset_gLCD();
Display2();
delay_ms(50000);

while (1)
      {

      }
}

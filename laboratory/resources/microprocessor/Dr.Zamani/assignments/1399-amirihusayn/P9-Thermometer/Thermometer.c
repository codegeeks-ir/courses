/*******************************************************
Project : Thermometer
Version : 
Date    : 27/12/2020
Author  : 
Company : 
Comments: 

Chip type               : ATmega16
Program type            : Application
AVR Core Clock frequency: 1/000000 MHz
Memory model            : Small
External RAM size       : 0
Data Stack size         : 256
*******************************************************/

#include <mega16.h>
#include <delay.h>
#include <alcd.h>
#include <stdio.h> // for using sprintf function

// Voltage Reference: AREF pin
#define ADC_VREF_TYPE ((1<<REFS1) | (1<<REFS0) | (0<<ADLAR))

// Read the AD conversion result
unsigned int read_adc(unsigned char adc_input)
{
      ADMUX=adc_input | ADC_VREF_TYPE;
      // Delay needed for the stabilization of the ADC input voltage
      delay_us(10);
      // Start the AD conversion
      ADCSRA|=(1<<ADSC);
      // Wait for the AD conversion to complete
      while ((ADCSRA & (1<<ADIF))==0);
      ADCSRA|=(1<<ADIF);
      return ADCW;
}

void main(void)
{
      int adcValue;
      float temprature;
      char lcdBuffer[16];

      // Input/Output Ports initialization

      // Port A initialization
      // Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In 
      DDRA=(0<<DDA7) | (0<<DDA6) | (0<<DDA5) | (0<<DDA4) | (0<<DDA3) | (0<<DDA2) | (0<<DDA1) | (0<<DDA0);
      // State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T 
      PORTA=(0<<PORTA7) | (0<<PORTA6) | (0<<PORTA5) | (0<<PORTA4) | (0<<PORTA3) | (0<<PORTA2) | (0<<PORTA1) | (0<<PORTA0);

      // Port B initialization
      // Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In 
      DDRB=(0<<DDB7) | (0<<DDB6) | (0<<DDB5) | (0<<DDB4) | (0<<DDB3) | (0<<DDB2) | (0<<DDB1) | (0<<DDB0);
      // State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T 
      PORTB=(0<<PORTB7) | (0<<PORTB6) | (0<<PORTB5) | (0<<PORTB4) | (0<<PORTB3) | (0<<PORTB2) | (0<<PORTB1) | (0<<PORTB0);

      // Port C initialization
      // Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In 
      DDRC=(0<<DDC7) | (0<<DDC6) | (0<<DDC5) | (0<<DDC4) | (0<<DDC3) | (0<<DDC2) | (0<<DDC1) | (0<<DDC0);
      // State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T 
      PORTC=(0<<PORTC7) | (0<<PORTC6) | (0<<PORTC5) | (0<<PORTC4) | (0<<PORTC3) | (0<<PORTC2) | (0<<PORTC1) | (0<<PORTC0);

      // Port D initialization
      // Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In 
      DDRD=(0<<DDD7) | (0<<DDD6) | (0<<DDD5) | (0<<DDD4) | (0<<DDD3) | (0<<DDD2) | (0<<DDD1) | (0<<DDD0);
      // State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T 
      PORTD=(0<<PORTD7) | (0<<PORTD6) | (0<<PORTD5) | (0<<PORTD4) | (0<<PORTD3) | (0<<PORTD2) | (0<<PORTD1) | (0<<PORTD0);



      // ADC initialization
      // ADC Clock frequency: 500/000 kHz
      // ADC Voltage Reference: AREF pin
      // ADC Auto Trigger Source: ADC Stopped
      ADMUX=ADC_VREF_TYPE;
      ADCSRA=(1<<ADEN) | (0<<ADSC) | (0<<ADATE) | (0<<ADIF) | (0<<ADIE) | (0<<ADPS2) | (0<<ADPS1) | (1<<ADPS0);
      SFIOR=(0<<ADTS2) | (0<<ADTS1) | (0<<ADTS0);


      // Alphanumeric LCD initialization
      // Connections are specified in the
      // Project|Configure|C Compiler|Libraries|Alphanumeric LCD menu:
      // RS - PORTD Bit 0
      // RD - PORTD Bit 1
      // EN - PORTD Bit 2
      // D4 - PORTD Bit 4
      // D5 - PORTD Bit 5
      // D6 - PORTD Bit 6
      // D7 - PORTD Bit 7
      // Characters/line: 16
      lcd_init(16);
      lcd_clear();

      while (1)
      {
            // read_adc(0) reads analog value of Pin0 and returns an digital integer value between 0 and 1023 :
            adcValue = read_adc(0); 
            // converts digital value to temprature :
            temprature = adcValue / 4.03;

            // adds string of temprature value to lcdBuffer array :
            sprintf(lcdBuffer , "T = %3.1f" , temprature);

            // shows lcdBuffer on LCD :
            lcd_gotoxy(0,0);
            lcd_puts(lcdBuffer);
            lcd_gotoxy(8,0);
            lcd_puts("C");

            delay_us(250);
      }
}

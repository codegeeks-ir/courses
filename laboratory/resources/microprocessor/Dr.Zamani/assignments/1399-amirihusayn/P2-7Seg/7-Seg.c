#include<mega16.h>
#include<delay.h>


unsigned char i,j,k,l,delay;

unsigned short MaskNumber(int number)
{
    switch (number)
    {
        case 0 : return 0x3f;
        case 1 : return 0x06;
        case 2 : return 0x5b;
        case 3 : return 0x4f;
        case 4 : return 0x66;
        case 5 : return 0x6d;
        case 6 : return 0x7d;
        case 7 : return 0x07;
        case 8 : return 0x7f;
        case 9 : return 0x6f;
        default : return 0x00;
    }
}

void main(){
    DDRC = 0xff;
    DDRD.0 = 1;
    DDRD.1 = 1;
    DDRD.2 = 1;
    DDRD.3 = 1;

    PORTC = 0;
    PORTD = 0;

    while(1){
        for(i = 0; i <= 9; i++){
            for(j = 0; j <= 9; j++){
                for(k = 0; k <= 9; k++){
                    for(l = 0; l <= 9; l++){
                        for(delay = 0; delay <= 9; delay++){
                            PORTD = 0x07;
                            PORTC = MaskNumber(l);
                            delay_ms(1);

                            PORTD = 0x0B;
                            PORTC = MaskNumber(k);
                            delay_ms(1);

                            PORTD = 0x0D;
                            PORTC = MaskNumber(j);
                            delay_ms(1);
                            
                            PORTD = 0x0E;
                            PORTC = MaskNumber(i);
                            delay_ms(1);
                        }
                    }
                }
            }
        }
    }
}
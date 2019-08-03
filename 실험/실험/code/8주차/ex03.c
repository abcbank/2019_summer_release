#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define rst 0
#define shift 1
#define segoverflow 2

unsigned char FND_SEG[10]={0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7C, 0x07, 0x7F, 0x67};
unsigned char cnt;
unsigned char state;
int seg;
void segSetting() {
	DDRA = 0xFF;
	DDRE |= (_BV(2)|_BV(3));
	PORTE |= (_BV(2));
	PORTA = 0x00;
	PORTE |= (_BV(3));
	PORTA = 0x00;
}

void resetSystem(){
    PORTE = 0x04;
    PORTA = 0x10;
	PORTE = 0x08;
    PORTA = FND_SEG[cnt];
    _delay_ms(1000);
}

int main(void){
    cnt = 0; 
	state = 0;
	seg = 0;
    segSetting();
    
    while(1){
                PORTE = 0x04;
                PORTA = 0x01 << seg;
                PORTE = 0x08;
                PORTA = FND_SEG[cnt];
                _delay_ms(1000);
				seg = (seg+1) % 4;
         
        cnt = (cnt+1)%10;
    }
}

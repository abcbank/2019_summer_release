#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#define startpoint 0x83

unsigned char FND_SEG[10]={0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7C, 0x07, 0x7F, 0x67};
unsigned int LED[4]={0,0,0,0};
volatile int timer= 0;
volatile int mode = 1;
void setLED(){
	LED[3] =  timer%10;
	LED[2] = (timer/10)%10;
	LED[1] = (timer/100)%10;
	LED[0] = (timer/1000);
}

void switch_setting(){
	DDRD &= ~(_BV(0)|_BV(1));
}

void LED_setting() {
	DDRA = 0xFF;
	DDRE |= (_BV(2)|_BV(3));
	PORTE |= (_BV(2));
	PORTA = 0x0F;
	PORTE |= (_BV(3));
	PORTA = 0x00;
}

int main(void)
	{
	int j;
	LED_setting(); 
	switch_setting();
	while(1)
	{
		switch(PING&0x0F){
			case 0x0E :
				_delay_ms(100);
				mode ^= 1;
				break;
			case 0x0D :
				_delay_ms(100);
				timer = 0;
				mode = 1;
				break;
			
		}
		if(!mode)
			timer++;
		setLED();
		for(j=0; j<4; j++){
			PORTE = 0x04;
			PORTA = 0x01<<j;
			PORTE = 0x08;
			if(j==1)
				PORTA = FND_SEG[LED[j]]|0x80;
			else
				PORTA = FND_SEG[LED[j]];
			_delay_ms(1);
		}
	}
	return 0;

	}

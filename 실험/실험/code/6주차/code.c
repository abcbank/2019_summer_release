#include <avr/io.h>
#include <util/delay.h>

int main(void){
	DDRF = 0xF0;
	PORTF = 0x00;
	DDRG = 0x00;
	while(1){
		switch(PING&0x0F){
		case 0x0E:
			PORTF = 0x01 <<4;
			break;
		case 0x0D:
			PORTF = 0x02<<4;
			break;
		case 0x0B:
			PORTF = 0x04<<4;
			break;
		case 0x07:
			PORTF = 0x08<<4;
			break;
			default : 
				PORTF = 0x00;
				break;
        }
	}
}

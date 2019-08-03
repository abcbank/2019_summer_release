#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define up 0
#define down 1
#define reset 2;

int state;
int cnt;

void gpioSet(){
    DDRF = 0xF0;
    PORTF = 0x00;
}

int main(){
	gpioSet();
	state = up;
	PORTF = 0x10;
    while(1){
        switch(state){	
            case up: 
				_delay_ms(2000);
                PORTF = PORTF << 1;
				cnt++;
				if(cnt % 3 == 0)
					state = down;
                break;
            case down:
                _delay_ms(4000);
                PORTF = PORTF >> 1;
				cnt++;
                if(cnt % 3 == 0 ) 
					state = up;
				break;	
			default : state = reset;
        }
    }
}

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

void gpioSet(){
    DDRF = 0xF0;
    PORTF = 0x00;
}

int main(void){
    gpioSet();

    while(1){
        _delay_ms(1000);
        PORTF ^= (_BV(4)|_BV(5)|_BV(6)|_BV(7));
    }    
}

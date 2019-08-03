#include <avr/io.h>
#include <avr/interrupt.h>
volatile int temp = 0;
int t = 61;
ISR(TIMER0_OVF_vect) {
	temp++;
	if (temp == t) {
		// temp * t -> 
		temp = 0;
		//		PORTF = (PORTF==(0x80))? 0x10:PORTF<<1;
		PORTF = (PINF == (0x80)) ? 0x10 : PINF << 1;
		// if PORTF is 0x80 : PINF <<1 -> overflow
		// so set 0x10 when PINF == 0x80
	}
}
void timer_setting() {
	TCCR0 = _BV(CS00) | _BV(CS01) | _BV(CS02);
	// CS = prescaler setting : 111 = 1/(16000000/1024) = 0.000064
	// for overflow, 0.000064 * 256 = 0.016384
	// for 1 sec, 1/0.016384 = 61.03515 = 61. t = 61
	TCNT0 = 0x00;
	// clear TCNT
	TIMSK = 0x01;
	// TIMSK[1] : TOIE0 -> interrupt enable when overflow
	TIFR = 0xFF;
	// init flag register
}
int main(void) {
	timer_setting();
	DDRF = 0xFF;
	PORTF = 0x10;
	sei();
	while (1)
	{
	}
	return 0;
}
#include <avr/io.h>
#include <avr/interrupt.h>
#include<util/delay.h>
//use compile optimization Option as "O1"
void init_port(void) {
	DDRF = 0xF0;	// Port F[7:4] for output : LED
	PORTF = 0x00; 	// Port F[7:4] -> set to LED on, clear to LED off
	DDRE = 0x00;	// Port E[2:1] for input : switch
	PORTE = 0xFF;	// PULL UP Switch : clear when floating
}
void init_interrupt(void) {
	EIMSK = 0x00;	//Mask Bit : clear before change setting
	EICRA = 0x00; 	// DON¡¯T USE
	EICRB = 0x0A; 	// Set Bit for interrupt 4, 5
	EIMSK = 0x30; 	// Set Mask bit for interrupt 4, 5
	EIFR = 0xFF; 	// init flag resigter before start
}
int main(void) {
	init_port();
	init_interrupt();
	while (1) {
		while (((EIFR & 0x10) | (EIFR & 0x20)) != 0x30) {}
		// EIFR&0x10 : focus on EIFR[4], EIFR&0x20 : focus on EIFR[5]
		// wait until INT 4 and INT 5 both occurred at least once

		if (((EIFR & 0x10) | (EIFR & 0x20)) == 0x30)
			// If flag[5:4] == ¡°11¡± is set, then turn on LED 3, 4.
		{
			PORTF = 0xC0; _delay_ms(1000);
		}
		sei(); 	//If I Bit of SREG is set, then ISR will be excuted.
		_delay_ms(100);
		// perform INT 4 first, then perform INT 5
		if (EIFR == 0) {
			PORTF = 0x00;
		}
		cli();	// clear Global Interrupt Register
	}
	return 0;
}

ISR(INT4_vect) {
	PORTF = ~PORTF; _delay_ms(1000);
	//	EIFR = 0xFF -> init mask register : clear flag[5]
}
ISR(INT5_vect) {
	PORTF = 0x90; _delay_ms(1000);
}
#include <avr/io.h>
#include <avr/interrupt.h>

void init_port(void) {
	DDRF = 0xF0; 	// DDRF : Set Port F to output
			// Port F[7:4] for output : LED
	PORTF = 0x00; 	// PORTF : clear bit
			// Port F[7:4] -> set to LED on, clear to LED off
	DDRE = 0x00; 	// DDRE : Set Port F to input
			// Port E[2:1] for input : switch
	PORTE = 0xFF;	// PULL UP Switch : clear when floating
}

void init_interrupt(void) {
	EIMSK = 0x00; // When changing ISCn1/ISCn0 bits, the interrupt must be 			// disabled by clearing its Interrupt Enable bit in the 				// EIMSK Register.
			// Otherwise an interrupt can occur when the bits are 			// changed.
	EICRA = 0x00; 	// A : don't use! 
	EICRB = 0x08; 	// set bit for INT 5
	EIMSK = 0x20; 	// set Mask Bit for INT 5
	EIFR = 0xFF; 	// init Flag Bit before start
}

int main(void) {
	init_port();
	init_interrupt();
	sei();	// function sei : set global interrupt flag -> start checking 			// interrupt
	while (1)
	{
	}
	return 0;
}

ISR(INT5_vect) {
	PORTF = ~PORTF;	// when switch 5 floated, toggle all bits for LED
}
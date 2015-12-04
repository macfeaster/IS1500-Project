#include <stdint.h>
#include <pic32mx.h>
#include "mipslab.h"

/**
 *	Returns integer representation of state of toggle 
 *	switches where bit 4-0 represent switches 4-1. 
 *	1 is on, 0 off.
 */
int getsw(void) {

	// Get value from port D, shift to make 11-8 
	// least significant bits, mask out unwanted bits
	return (PORTD >> 8) & 0xf;
}

/**
 *	Returns integer representation of state of buttons 
 *	where bit 3-0 represent buttons 4-1. 
 *	1 is on, 0 off.
 */
int getbtns(void) {
	
	// Get bits 7-5 from port D (buttos 4-2), 
	// and bit 1 from port F (button 1), 
	// shift to mask unwanted bits, combine
	return ((PORTD >> 4) & 0x7) | ((PORTF >> 1) & 0x1);
}
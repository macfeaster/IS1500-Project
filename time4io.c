#include <stdint.h>
#include <pic32mx.h>
#include "mipslab.h"

int getsw(void);
int getbtns(void);

int getsw (void)
{
	// SW1:		Shield Pin 2	PIC32 Signal RD8
	// SW2:		Shield Pin 7	PIC32 Signal RD9
	// SW3:		Shield Pin 8	PIC32 Signal RD10
	// SW4:		Shield Pin 35	PIC32 Signal RD11

	// Set TRISD bits 8 through 11 to 1 (Input)
	// TRISD |= 0xf00;

	// Retrieve 32-bit raw values from memory
	int switches = PORTD;

	// Shift right 8 bits to clean unwanted first 8 bits
	switches = (switches >> 8);

	// Clean everything but the four least significant bits
	switches &= 0xf;

	return switches;
}

int getbtns (void)
{
	// BTN2:	Shield Pin 34	PIC32 Signal RD5
	// BTN3:	Shield Pin 36	PIC32 Signal RD6
	// BTN4:	Shield Pin 37	PIC32 Signal RD7

	// Set TRISD bits 5 through 7 to 1 (Input)
	// TRISD |= 0xe0;

	// Retrieve 32-bit raw values from memory
	int buttons = PORTD;

	// Shift right 5 bits to clean unwanted first 5 bits
	buttons = (buttons >> 5);

	// Clean everything but the three least significant bits
	buttons &= 0x7;

	return buttons;
}
/**
 *
 */

#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "caesar.h"

/* Interrupt Service Routine */
void user_isr( void )
{
    // Example interrupt code
    if (IFS(0) & 0x100)
    {
        IFSCLR(0) = 0x100;

        display_string(0, "interrupt fired");
        display_update();

        /* if (timeoutcount == 10)
        {
          display_string( 3, "oppa" );
          display_update();
          timeoutcount = 0;
        } */
    }
}

/* Lab-specific initialization goes here */
void init(void)
{
    // Initialize Port E so bits 7 though 0 of port E
    // are set as outputs (i.e. the 8 least significant bits)
    volatile int* trise = (volatile int*) 0xbf886100;

    // Leave everything but 8 LSB's as is, set LSB's to zero
    // This could be done by writing to TRISECLR
    *trise &= ~0xff;

    // Set up port D for input

    PORTD &= 0xfe0;
    // Initialize Timer 2 for timeouts every 100 ms (10 timeouts per second), by:
    // - Setting prescaling to 1:256
    // - Setting the period to 31,250
    // Since 256 * 31,250 = 8M (and clock is 80 MHz, equalling 80M clock cycles per second)

    // Set bits 6 through 4 to 111 (0x70) to achieve 1:256 prescaling
    T2CONSET = 0x70;
    PR2 = 31250;
    PR2 *= 2;           // Half the interrupt frequency

    // Turn on the timer
    T2CONSET = 0x8000;

    // Enable interrupts globally (call the asm code)
    asm("ei");

    // Enable interrupts for Timer 2 (set T2IE, bit 8 of IEC0, to 1)
    IECSET(0) = 0x100;

    // Set interrupt priority to highest, and sub-priority to highest
    IPCSET(2) = 0x1f;

    display_string( 0, "HEI \\_('-')_/ LEL" );
    display_string( 1, "LEL \\_('-')_/ LEL" );
    display_update();

    return;
}

/* This function is called repetitively from the main program */
void work(void)
{
}
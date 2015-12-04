/* mipslabwork.c

   This file written 2015 by F Lundevall

   This file should be changed by YOU! So add something here:

   This file modified 2015-12-24 by Ture Teknolog 

   Latest update 2015-08-28 by F Lundevall

   For copyright and licensing, see file COPYING */

#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "mipslab.h"  /* Declatations for these labs */

/* Interrupt Service Routine */
void user_isr( void )
{
  // Example interrupt code
  if (IFS(0) & 0x100)
  {
    IFSCLR(0) = 0x100;

    /* if (timeoutcount == 10)
    {
      display_string( 3, "oppa" );
      display_update();
      timeoutcount = 0;
    } */
  }
}

/* Lab-specific initialization goes here */
void labinit( void )
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
  enable_interrupt();

  // Enable interrupts for Timer 2 (set T2IE, bit 8 of IEC0, to 1)
  IECSET(0) = 0x100;

  // Set interrupt priority to highest, and sub-priority to highest
  IPCSET(2) = 0x1f;

  return;
}

/* This function is called repetitively from the main program */
void labwork( void )
{
  display_string( 0, "HEI \\_('-')_/" );
  display_update();
}
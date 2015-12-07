// app.c
// Part of the KTH course IS1500 Computer Organization and Components project
// Authors: Alice Heavey and Mauritz Zachrisson

#include "../headers/caesar.h"

// Message buffer
char msg[16];
int transmitting = 0;
char curr_char = (char) 65;
int msg_pos = 0;

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
void init(void) {

    // Initialize display
    display_init();

    // Initialize SPI

    // Initialize empty message (spaces only)
    int i;
    for (i = 0; i < 16; ++i)
        msg[i] = (char) 32;

//    // Initialize Port E so bits 7 though 0 of port E
//    // are set as outputs (i.e. the 8 least significant bits)
//    volatile int* trise = (volatile int*) 0xbf886100;
//
//    // Leave everything but 8 LSB's as is, set LSB's to zero
//    // This could be done by writing to TRISECLR
//    *trise &= ~0xff;
//
    // Set up port D for input

    PORTD &= 0xfe0;
//    // Initialize Timer 2 for timeouts every 100 ms (10 timeouts per second), by:
//    // - Setting prescaling to 1:256
//    // - Setting the period to 31,250
//    // Since 256 * 31,250 = 8M (and clock is 80 MHz, equalling 80M clock cycles per second)
//
//    // Set bits 6 through 4 to 111 (0x70) to achieve 1:256 prescaling
//    T2CONSET = 0x70;
//    PR2 = 31250;
//    PR2 *= 2;           // Half the interrupt frequency
//
//    // Turn on the timer
//    T2CONSET = 0x8000;
//
//    // Enable interrupts globally (call the asm code)
//    asm("ei");
//
//    // Enable interrupts for Timer 2 (set T2IE, bit 8 of IEC0, to 1)
//    IECSET(0) = 0x100;
//
//    // Set interrupt priority to highest, and sub-priority to highest
//    IPCSET(2) = 0x1f;
//
    display_string( 0, "HEI \\_('-')_/ LEL" );
    display_string( 1, "LEL \\_('-')_/ LEL" );
    display_update();



    return;
}

/* This function is called repetitively from the main program */
void work(void) {

    if (!get_state()) {

        display_string(0, "RECEIVE MODE");
        display_string(1, "");
        display_string(2, "");
        display_string(3, "");
        display_update();

        // Reset transmission values
        curr_char = (char) 65;
        msg_pos = 0;
        transmitting = 0;

        int i;
        for (i = 0; i < 16; ++i)
            msg[i] = (char) 32;

        // If receiving, poll SPI buffer (maybe flash LED when a message is incoming)
        // Poll switches repeatedly to try decode using key
        // Decode and display the message on the screen

    } else {

        if (transmitting || msg_pos == MSG_MAX_LEN) {

            display_string(0, "TRANSMITTING...");
            display_string(1, msg);
            display_string(2, "");
            display_string(3, "FLIPSWITCH 4 NEW");
            display_update();
            // Hang program until receive mode is initialized
            while (get_state()) {};

        } else {

            display_string(0, "TRANSMIT MODE");
            display_update();

            // Check for state change or button event
            while (get_btns() == 0 && get_state()) {};

            // Don't redraw until a button is pressed, or the state is changed
            button_control(&transmitting, msg, &curr_char, &msg_pos, MSG_MAX_LEN);

            // char out[16];
            // num32asc(out, get_btns());

            // TODO: Currently, the program redraws continually
            // TODO: When

            // Prints curr_char right after msg
            msg[msg_pos] = curr_char;

            display_string(1, msg);
            display_string(2, "");
            display_string(3, "");
            display_update();

            // If transmission
            // Enable user to write message
            // When they push EOM button, lock board until transmission state switch is flipped

        }

    }

}
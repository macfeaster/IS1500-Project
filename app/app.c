// app.c
// Part of the KTH course IS1500 Computer Organization and Components project
// Authors: Alice Heavey and Mauritz Zachrisson

#include "../headers/caesar.h"

/* Interrupt Service Routine */
void user_isr( void ) {}

/* Lab-specific initialization goes here */
void config(void) {

    // Initialize display
    display_init();

    /**
     * Config U1MODE:
     *
     * Bits 8-9 = 10 = Enable and use UxTX, UxRX, UxCTS and UxRTS (all pins)
     *
     * Flow control mode, which (essentially) means that the boards will wait
     * for each other when sending and receiving data, so no data is lost.
     * Enables
     */
    U1MODE = 0x0285;
    U1STA = 0x0000D400;
    U1BRG = 0xFFFF;
    U1MODESET = 0x00008000;

    // Set up port D for input
    PORTD &= 0xfe0;

    display_string( 0, "\\_('-')_/" );
    display_string( 1, "\\_('-')_/" );
    display_update();

    return;
}

/* This function is called repetitively from the main program */
void run(void) {

    // If state is 0, board is in receive mode
    if (!get_state())
        receive();
    else
        transmit();

}

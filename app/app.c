// app.c
// Part of the KTH course IS1500 Computer Organization and Components project
// Authors: Alice Heavey and Mauritz Zachrisson

#include "../headers/caesar.h"

// Message buffer
char msg[16];
int transmitting = 0;
char curr_char = (char) 32;
int msg_pos = 0;

// Receive buffer
char rec_buffer[16];
char decrypted_rec_msg[16];

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
    U1BRG = 0x4119;
    U1MODESET = 0x00008000;

    // Initialize empty message (spaces only)
    int i;
    for (i = 0; i < 16; ++i)
        msg[i] = (char) 32;

    // Set up port D for input
    PORTD &= 0xfe0;

    display_string( 0, "HEI \\_('-')_/ LEL" );
    display_string( 1, "LEL \\_('-')_/ LEL" );
    display_update();

    return;
}

/* This function is called repetitively from the main program */
void work(void) {

    // If state is 0, board is in receive mode
    if (!get_state()) {

        display_string(0, "RECEIVE MODE");
        display_string(1, "");
        display_string(2, "");
        display_string(3, "");
        display_update();

        // Reset transmission values
        curr_char = (char) 32;
        msg_pos = 0;
        transmitting = 0;

        // Reset transmission message
        int i;
        for (i = 0; i < 16; ++i)
            msg[i] = (char) 32;

        // Empty rec buffer
        for (i = 0; i < 16; ++i)
            rec_buffer[i] = (char) 32;

        // Empty decrypted buffer
        for (i = 0; i < 16; ++i)
            decrypted_rec_msg[i] = (char) 32;

        int buf_index = 0;

        // Receive incoming message
        while (1) {
            // When Receive Buffer Data Available bit turns 1,
            // an incoming message is waiting to be read
            if (U1STA & 1)
            {
                // Receive until the
                if (buf_index < 16)
                {
                    // Receive one byte from receive register
                    unsigned int buf = U1RXREG;
                    rec_buffer[buf_index] = buf;
                    display_string(1, buf);
                    display_string(2, rec_buffer);
                    quicksleep(2500);
                    display_update();
                    buf_index++;
                } else break;
            }
        }

        display_string(0, "RECEIVED MSG");
        display_string(1, "");
        display_string(2, "");
        display_string(3, "");
        display_update();

        // Get key from switches
        int key = get_key();

        strcpy(rec_buffer, decrypted_rec_msg);
        decrypt(decrypted_rec_msg, key, MSG_MAX_LEN);

        display_string(0, "RECEIVED MSG");
        display_string(1, "");
        display_string(2, rec_buffer);
        display_string(3, decrypted_rec_msg);
        display_update();

        // Pause until mode is switched
        while (!get_state()) {};

        // If receiving, poll SPI buffer (maybe flash LED when a message is incoming)
        // Poll switches repeatedly to try decode using key
        // Decode and display the message on the screen

    } else {

        if (transmitting || msg_pos == MSG_MAX_LEN) {

            // Fetch encryption key
            int key = get_key();

            display_string(0, "TRANSMITTING...");
            // Display message submitted for encryption
            display_string(1, msg);

            // Encrypt message
            encrypt(&msg[0], key, MSG_MAX_LEN);

            // Display encrypted message
            display_string(2, msg);
            display_string(3, "FLIP SWTCH 4 NEW");
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

            // Prints curr_char right after msg
            // Where beautiful solutions go to die 
            // *RIP*
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

void strcpy(char *dst, char *src) {
    while((*dst++ = *src++));
}
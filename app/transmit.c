#include "../headers/caesar.h"

int transmitting = 0;
char curr_char = (char) 32;
int msg_pos = 0;
char msg[16];

void transmit() {

    // Initialize empty message (spaces only)
    int i;
    for (i = 0; i < 16; ++i)
        msg[i] = (char) 32;

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
        while (get_state()) { };

    } else {

        display_string(0, "TRANSMIT MODE");
        display_update();

        // Check for state change or button event
        while (get_btns() == 0 && get_state()) { };

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

        // Reset transmission values
        curr_char = (char) 32;
        msg_pos = 0;
        transmitting = 0;

        // Reset transmission message
        int i;
        for (i = 0; i < 16; ++i)
            msg[i] = (char) 32;


    }
}
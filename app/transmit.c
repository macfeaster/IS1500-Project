#include "../headers/caesar.h"

char curr_char = (char) 32;
int msg_pos = 0;
char msg[16];
int is_transmitting = 0;

// Forward declarations
void input_transmission_msg();
void transmitting();
void go_receive();

/**
 * Transmit
 */
void transmit() {

    // Setup
    display_clear();
    display_string(0, "TRANSMIT MODE");
    display_update();

    msg_init(msg);

    while (!is_transmitting)
        input_transmission_msg();

    transmitting();

    while(get_state());
    go_receive();
}

void input_transmission_msg() {

    // Check for state change or button event
    while (get_btns() == 0 && get_state());

    // Jump to receive is switch is flipped
    if (!get_state())
        go_receive();

    // Don't redraw until a button is pressed, or the state is changed
    button_control(&is_transmitting, msg, &curr_char, &msg_pos, MSG_MAX_LEN);

    // Prints curr_char right after msg
    // Where beautiful solutions go to die
    // *RIP*
    msg[msg_pos] = curr_char;
    display_clear();
    display_string(1, msg);
    display_update();
}

void transmitting() {

    display_clear();
    display_string(0, "TRANSMITTING ...");
    display_update();

    // Encrypt message
    encrypt(&msg[0], get_key(), MSG_MAX_LEN);

    // Transmit message
    int i;
    for (i = 0; i < MSG_MAX_LEN; i++) {
        // Block until the buffer is available
        while((U1STA & 0x0200) && get_state());
        U1TXREG = msg[i];

        if (!get_state())
            go_receive();
    }

    msg_pos = 0;
    is_transmitting = 0;

    display_clear();
    display_string(0, "MSG TRANSMITTED.");
    display_update();

}

void go_receive() {
    transmission_clear(&curr_char, msg, &msg_pos, &is_transmitting);
    receive();
}
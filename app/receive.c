#include "../headers/caesar.h"

char rec_buffer[MSG_MAX_LEN];

// Forward declarations
void read_buffer(char* out);

void receive() {

    // Clear the buffer
    msg_init(rec_buffer);

    // Show welcome display
    display_clear();
    display_string(0, "RECEIVE MODE");
    display_update();

    // Block until
    while (!(U1STA & 1) && !get_state());

    // Jump to transmit mode if user toggles switch
    if (get_state())
        transmit();

    display_clear();
    display_string(0, "INCOMING MSG...");
    display_update();

    read_buffer(rec_buffer);

    decrypt(rec_buffer, get_key(), MSG_MAX_LEN);

    display_clear();
    display_string(0, "RECEIVED MSG.");
    display_string(1, rec_buffer);
    display_update();

    // Hang until mode is switched
    while (!get_state()) {};

    transmit();

}

void read_buffer(char* out) {

    unsigned int buf;
    int buf_index = 0;

    // Create 16 spaces which will be used as progress bar
    char dots[16];
    msg_init(dots);

    while ((U1STA & 1) && buf_index < MSG_MAX_LEN) {

        buf = U1RXREG;
        out[buf_index] = (char) buf;
        dots[buf_index] = (char) 46;
        buf_index++;

        display_clear();
        display_string(0, "RECEIVING MSG");
        display_string(1, dots);
        display_update();

        quicksleep(2500000);
    }
}
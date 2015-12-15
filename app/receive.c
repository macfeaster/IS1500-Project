#include "../headers/caesar.h"

char rec_buffer[MSG_MAX_LEN];

// Forward declarations
void read_buffer(char* out);

void receive() {

    display_clear();
    display_string(0, "RECEIVE MODE");
    display_update();

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
    display_string(2, itoaconv(get_key()));
    display_update();


    // Hang until mode is switched
    while (!get_state()) {};

    transmit();

}

void read_buffer(char* out) {

    unsigned int buf;
    int buf_index = 0;

    while ((U1STA & 1) && buf_index < MSG_MAX_LEN) {

        buf = U1RXREG;
        out[buf_index] = (char) buf;
        buf_index++;

        display_clear();
        display_string(0, itoaconv(buf));
        display_string(1, itoaconv(buf_index));
        display_string(2, rec_buffer);
        display_update();

        quicksleep(10000000);

    }
}
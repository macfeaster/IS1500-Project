#include "../headers/caesar.h"

char rec_buffer[MSG_MAX_LEN];

// Forward declarations
void read_buffer(char* out);

// Clear display line values
void display_clear() {

    display_string(0, "");
    display_string(1, "");
    display_string(2, "");
    display_string(3, "");

}

void receive() {

    display_clear();
    display_string(0, "RECEIVE MODE");
    display_update();

    while (!(U1STA & 1));

    display_clear();
    display_string(0, "INCOMING MSG...");
    display_update();

    read_buffer(rec_buffer);

    display_clear();
    display_string(0, "RECEIVED MSG.");
    display_string(1, rec_buffer);
    display_update();

    // Hang until new data
    while (!get_state()) {};

    receive();

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
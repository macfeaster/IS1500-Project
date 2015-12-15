#include "../headers/caesar.h"

void receive() {

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

    // Wait for incoming message
    display_string(0, "WAITING4INC");
    display_update();
    while (!(U1STA & 1));

    // Receive incoming message
    int j;
    for (j = 0; j < MSG_MAX_LEN; ++j) {
        // Receive one byte from receive register
        unsigned int buf = U1RXREG;
        rec_buffer[j] = buf;
        display_string(1, buf);
        display_string(2, rec_buffer);
        display_update();
        quicksleep(50000);
    }

    // Vaska all jävla skit som är kvar i buffern
    while (U1STA & 1) {
        int vask = U1RXREG;
    }

    /*
    // Receive incoming message
    while (!get_state()) {
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
        display_string(0, "IZ STUCK!!!");
        display_update();
    } */

    // Get key from switches
    int key = get_key();

    display_string(0, "RECEIVED MSG");
    display_string(1, itoaconv(U1STA & 1));
    display_string(2, rec_buffer);

    decrypt(&rec_buffer[0], key, MSG_MAX_LEN);

    display_string(3, rec_buffer);
    display_update();

    // Pause until mode is switched
    while (!get_state()) {};

    // If receiving, poll SPI buffer (maybe flash LED when a message is incoming)
    // Poll switches repeatedly to try decode using key
    // Decode and display the message on the screen


}
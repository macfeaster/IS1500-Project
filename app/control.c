// control.c
// Part of the KTH course IS1500 Computer Organization and Components project
// Authors: Alice Heavey and Mauritz Zachrisson

#include "../headers/caesar.h"

// This removes compiler and IDE warnings raised from memory mapped behavior
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wfor-loop-analysis"
#pragma ide diagnostic ignored "OCDFAInspection"

/**
 *	Handles input from buttons.
 *	Button 1: send message
 *	Button 2: set char
 *	Button 3, 4: browse chars
 *
 *	Only takes input from one button at a time
 */
void button_control(int *transmitting, char *message, char *curr_char, int *msg_pos, int msg_max_len) {

    volatile int btns = get_btns();

    // If one or more buttons are pressed and not currently
    // transmitting message, handle button actions
    if (btns && !(*transmitting)) {
        switch (btns) {

            // If rightmost button (1) is pressed,
            // turn transmission on
            case 1:
                display_string(2, "TRANSMITTING=1");
                display_update();
                *transmitting = 1;
                break;

            case 2:
                // If button 2 is pressed, wait for its release, then
                // add the current character to the message buffer
                while(get_btns() == 2){};
                display_string(2, "MSG " + *message);
                display_update();
                add_char(message, curr_char, msg_pos, msg_max_len);
                break;

            case 4:
                while(get_btns() == 4){};
                increment_char(curr_char, 1);
                display_string(2, "INCR CHAR" + *curr_char);
                display_update();
                break;

            case 8:
                while(get_btns() == 8){};
                decrement_char(curr_char, 1);
                display_string(2, "DECR CHAR" + *curr_char);
                display_update();
                break;

            default:
                display_string(2, "ILLEGAL BTN CODE");
                display_update();
                break;
        }
    }
}

#pragma clang diagnostic pop
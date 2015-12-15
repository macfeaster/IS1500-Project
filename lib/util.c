// util.c
// Part of the KTH course IS1500 Computer Organization and Components project
// Authors: Alice Heavey and Mauritz Zachrisson

#include "../headers/caesar.h"

/**
 * Clear display line values
 */
void display_clear() {

    display_string(0, "");
    display_string(1, "");
    display_string(2, "");
    display_string(3, "");

}

/**
 * Clear a message buffer
 */
void msg_init(char* msg) {
    // Initialize empty message (spaces only)
    int i;
    for (i = 0; i < MSG_MAX_LEN; ++i)
        msg[i] = (char) 32;
}

/**
 * Clear all transmission data
 */
void transmission_clear(char* curr_char, char* msg, int* msg_pos, int*is_transmitting) {
    // Reset transmission values
    *curr_char = (char) 32;
    *msg_pos = 0;
    *is_transmitting = 0;

    msg_init(msg);
}
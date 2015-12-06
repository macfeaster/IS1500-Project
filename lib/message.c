// message.c
// Part of the KTH course IS1500 Computer Organization and Components project
// Authors: Alice Heavey and Mauritz Zachrisson

#include "../headers/caesar.h"

char *curr_char = (char *) 'A';

/**
 *	Add next char to transmission message
 *	If message is already of max size nothing happens
 */
void add_char(char *message, int *msg_len, int msg_max_len) {

	if (*msg_len < msg_max_len) {
		*msg_len = *msg_len + 1;
		message[*msg_len] = *curr_char;
	}
}

/**	
 *	Increment char value using the char pointer n steps
 *	For character value Z, jump to start of alphabet 
 */
void increment_char(char *curr_char, int steps) {

    // Avoid redundant calculations resulting from steps > 26
    int new_char = *curr_char + steps % 26;

    // if new char does not exceed 90 (Z), assign to curr_char,
    // otherwise add residual - 1 to 65 (A)
    if (new_char =< 90) {
        (int) *curr_char = new_char;
    } else {
        (int) *curr_char = new_char - 1 - 90 + 65;
    }

}

/**
 *	Decrement char value using the char pointer n steps
 *	For character value A, jump to end of alphabet 
 */
void decrement_char(char *curr_char, int steps) {

    // Avoid redundant calculations resulting from steps > 26
    int new_char = *curr_char - steps % 26;

    // if new char does not fall below 65 (A), assign to curr_char,
    // otherwise add negative residual + 1 to 90 (Z)
    if (new_char >= 65) {
        (int) *curr_char = new_char;
    } else {
        (int) *curr_char = new_char + 1 - 65 + 90;
    }
}
// message.c
// Part of the KTH course IS1500 Computer Organization and Components project
// Authors: Alice Heavey and Mauritz Zachrisson

#include "../headers/caesar.h"

/**
 *	Add next char to transmission message
 *	If message is already of max size nothing happens
 */
void add_char(char *message, char *curr_char, int *msg_len, int msg_max_len) {

	if (*msg_len < msg_max_len) {
		*msg_len = *msg_len + 1;
		message[*msg_len] = *curr_char;
        *curr_char = (char) 32;
	}
}

/**	
 *	Increment char value using the char pointer n steps
 *	For character value Z, jump to start of alphabet 
 */
void increment_char(char *curr_char, int steps) {

    // Avoid redundant calculations resulting from steps > 26
    int new_char = *curr_char + steps % 26;

    // If new char does not exceed 90 (Z), assign to curr_char,
    if (new_char <= 90)
        *curr_char = (char) new_char;

    // Otherwise add residual - 1 to 65 (A)
    else
        *curr_char = (char) (new_char - 1 - 90 + 65);

}

/**
 *	Decrement char value using the char pointer n steps
 *	For character value A, jump to end of alphabet 
 */
void decrement_char(char *curr_char, int steps) {

    // Avoid redundant calculations resulting from steps > 26
    int new_char = *curr_char - steps % 26;

    // If new char does not fall below 65 (A), assign to curr_char,
    if (new_char >= 65)
        *curr_char = (char) new_char;

    // Otherwise add negative residual + 1 to 90 (Z)
    else
        *curr_char = (char) (new_char + 1 - 65 + 90);

}
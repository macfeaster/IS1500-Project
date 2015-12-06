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

    // Run the incrementation n steps
    // This should be replaced by a smarter algorithm later on
    int i;
    for (i = 0; i < steps; ++i) {

        // Characters out of bound produce an A
        if ((int) *curr_char >= 90)
            *curr_char = 'A';

        // Otherwise, the curr_char pointer is incremented
        else
            *curr_char = (char) (*curr_char + 1);

    }

}

/**
 *	Decrement char value using the char pointer n steps
 *	For character value A, jump to end of alphabet 
 */
void decrement_char(char *curr_char, int steps) {

    // Run the decrementation n steps
    // This should be replaced by a smarter algorithm later on
    int i;
    for (i = 0; i < steps; ++i) {

        // Characters out of bound produce a Z
        if ((int) *curr_char <= 65)
		    *curr_char = 'Z';

        // Otherwise, the curr_char pointer is incremented
        else
		    *curr_char = (char) (*curr_char - 1);

	}
}
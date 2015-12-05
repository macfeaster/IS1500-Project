#include "../caesar.h"

char *curr_char = (char *) 'A';

/**	
 *	Handles input from buttons. 
 *	Button 1: send message 
 *	Button 2: set char
 *	Button 3, 4: browse chars
 *		
 *	Only takes input from one button at a time
 */
void button_control(int *transmitting) {

	volatile int btns = get_btns();

	// If one or more buttons are pressed and not currently 
	// transmitting message, handle button actions
	if (btns && !(*transmitting)) {
		switch (btns) {

            // If rightmost button (1) is pressed,
            // turn transmission on
			case 1:
				*transmitting = 1;
				break;

            // If button 2 is pressed, wait for its release, then
            // add the current character to the message buffer
			case 2:
				while(btns == 2){};
				add_char();
				break;

			case 4:
				while(btns == 4){};
				increment_char();
				break;

			case 8:
				while(btns == 8){};
				decrement_char();
				break;

			default:
				break;
		}
	}
}

/**
 *	Add next char to transmission message
 *	If message is already of max size nothing happens
 */
void add_char(char *message, int *msg_len, int msg_max_size) {

	if (*msg_len < msg_max_size) {
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
    for (int i = 0; i < steps; ++i) {

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
    for (int i = 0; i < steps; ++i) {

        // Characters out of bound produce a Z
        if ((int) *curr_char <= 65)
		    *curr_char = 'Z';

        // Otherwise, the curr_char pointer is incremented
        else
		    *curr_char = (char) (*curr_char - 1);

	}
}
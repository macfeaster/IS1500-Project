char* current_char;
char transm_msg[16];
int* transm_msg_max_size;
int* transm_msg_length;

void add_char(void);
void increment_char(void);
void decrement_char(void);


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
			case 1:
				*transmitting = 1;
				break;
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
void add_char() {

	if (*transm_msg_length < *transm_msg_max_size){
		*transm_msg_length = *transm_msg_length + 1;
		*message[*transm_msg_length] = *current_char;
	}
}

/**	
 *	Increment char value using the char pointer
 *	For character value Z, jump to start of alphabet 
 */
void increment_char(void) {
	if ((int) *current_char >= 90) {
		*current_char = 'A';
	} else {
		*current_char = *current_char + 1;
	}
}

/**
 *	Decrement char value using the char pointer
 *	For character value A, jump to end of alphabet 
 */
void decrement_char(void) {
	if ((int) *current_char <= 65) {
		*current_char = 'Z';
	} else {
		*current_char = *current_char - 1;
	}
}

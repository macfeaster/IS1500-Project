char* current_char;

void set_message(void) {

	volatile int btns = get_btns();

	if (btns) {

		switch (btns) {
			case 1:
			case 2:
			case 4:

				// Increment char value using the char pointer
				// For character value Z, jump to start of alphabet 

				if ((int) *current_char >= 90) {
					*current_char = 'A';
				} else {
					*current_char = *current_char + 1;
				}
			case 8:

				// Decrement char value using the char pointer
				// For character value A, jump to end of alphabet 

				if ((int) *current_char <= 65) {
					*current_char = 'Z';
				} else {
					*current_char = *current_char - 1;
				}
			default:
				break;
		}
	}
}
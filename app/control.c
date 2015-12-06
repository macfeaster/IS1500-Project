// control.c
// Part of the KTH course IS1500 Computer Organization and Components project
// Authors: Alice Heavey and Mauritz Zachrisson

/**
 *	Handles input from buttons.
 *	Button 1: send message
 *	Button 2: set char
 *	Button 3, 4: browse chars
 *
 *	Only takes input from one button at a time
 */
void button_control(int *transmitting, char *message, char *curr_char, int *msg_len, int msg_max_len) {

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
                add_char(message, msg_len, msg_max_len);
                break;

            case 4:
                while(btns == 4){};
                increment_char(curr_char, 1);
                break;

            case 8:
                while(btns == 8){};
                decrement_char(curr_char, 1);
                break;

            default:
                break;
        }
    }
}

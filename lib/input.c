// input.c
// Part of the KTH course IS1500 Computer Organization and Components project
// Authors: Alice Heavey and Mauritz Zachrisson

#include "../headers/caesar.h"

/**
 *	Returns integer representation of state of toggle 
 *	switches where bit 3-0 represent switches 4-2. 
 *	1 is on, 0 off.
 */
int get_key(void) {

    // Get value from port D, shift to make 11-7
    // least significant bits, mask out unwanted bits
    return (PORTD >> 9) & 0x7;

}

/**
 *	Returns integer representation of state of toggle 
 *	switch 1 where 1 represents on, 0 off.
 */
int get_state(void) {

    // Get value from port D, shift to make bit 8
    // least significant bit, mask out unwanted bits
    return (PORTD >> 8) & 0x1;
}

/**
 *	Returns integer representation of state of buttons 
 *	where bit 3-0 represent buttons 4-1. 
 *	1 is on, 0 off.
 */
int get_btns(void) {

    // Get bits 7-5 from port D (buttos 4-2),
    // and bit 1 from port F (button 1),
    // shift to mask unwanted bits, combine
    return ((PORTD >> 4) & 0xe) | ((PORTF >> 1) & 0x1);

}

/**
 * Clear display line values
 */
void display_clear() {

    display_string(0, "");
    display_string(1, "");
    display_string(2, "");
    display_string(3, "");

}
// app.c
// Part of the KTH course IS1500 Computer Organization and Components project
// Authors: Alice Heavey and Mauritz Zachrisson

// Include header code for board and helper functions
#include "mipsfunc.h"

// Global constants
#define MSG_MAX_LEN 16

// Header definitions for lib/input.c
int get_key(void);
int get_state(void);
int get_btns(void);

// Header definitions for lib/message.c
void add_char(char *msg, int *msg_pos, int msg_max_size);
void increment_char(char *curr_char, int steps);
void decrement_char(char *curr_char, int steps);
void button_control(int *transmitting, char *message, char *curr_char, int *msg_pos, int msg_max_len);
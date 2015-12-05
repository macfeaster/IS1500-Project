/* mipslab.h
   Header file for the project.

   Written 2015 by Alice Heavey and Mauritz Zachrisson
   Lines 10-40 written 2015 by F Lundevall

   For copyright and licensing, see file COPYING */

/* Declare display-related functions from board/display.c */
void display_image(int x, const uint8_t *data);
void display_init(void);
void display_string(int line, char *s);
void display_update(void);
uint8_t spi_send_recv(uint8_t data);

/* Declare lab-related functions from kirchteiger.c */
char *itoaconv(int num);
void work(void);
void init(void);
void quicksleep(int cyc);

/* Declare display_debug - a function to help debugging.

   After calling display_debug,
   the two middle lines of the display show
   an address and its current contents.

   There's one parameter: the address to read and display.

   Note: When you use this function, you should comment out any
   repeated calls to display_image; display_image overwrites
   about half of the digits shown by display_debug.
*/
void display_debug( volatile int * const addr );

/* Declare bitmap array containing font */
extern const uint8_t const font[128*8];
/* Declare text buffer for display output */
extern char textbuffer[4][16];

/* Header definitions for lib/input.c */

int get_key(void);
int get_state(void);
int get_btns(void);

/* Header definitions for lib/message.c */
void add_char(char *message, int *msg_len, int msg_max_size);
void increment_char(char *curr_char, int steps);
void decrement_char(char *curr_char, int steps);

// cipher.c
// Part of the KTH course IS1500 Computer Organization and Components project
// Authors: Alice Heavey and Mauritz Zachrisson

// Bytes to chars
// Convert SPI data to C data structures

#include "../headers/caesar.h"

/**
 * Encrypts text message using Caecar cipher, 
 * where key determines how many steps each 
 * letter should be shifted (right)
 */
void encrypt(char *msg, int key, int msg_max_len) {
	int i;
	for (i = 0; i < msg_max_len; ++i) {
		if (msg[i] != ' ')
			increment_char(&msg[i], key);
	}
}

/**
 * Decrypts text message using Caecar cipher, 
 * where key determines how many steps each 
 * letter should be shifted (left)
 */
void decrypt(char *msg, int key, int msg_max_len) {
	int i;
	for (i = 0; i < msg_max_len; ++i) {
		if (msg[i] != ' ')
			decrement_char(&msg[i], key);
	}
}
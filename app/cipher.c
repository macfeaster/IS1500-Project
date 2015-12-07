// cipher.c
// Part of the KTH course IS1500 Computer Organization and Components project
// Authors: Alice Heavey and Mauritz Zachrisson

// Bytes to chars
// Convert SPI data to C data structures

// Encrypt
void encrypt(char *msg, int key, int msg_max_len) {
	int i;
	for (i = 0; i < msg_max_len; ++i)
	{
		increment_char(&msg[i], key);
	}
}

// Decrypt
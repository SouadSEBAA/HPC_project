#include "../lib/key_expansion.h"
#include "../lib/initializations.h"
#include "../lib/ctr.h"
#include "../lib/aes.h"
#include "../lib/utils.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define DEBUG true
#define PLAINTEXT_FILENAME "file"
#define CIPHERTEXT_FILENAME "enc"
#define KEY_FILENAME "key"
#define NONCE_FILENAME "nonce"

unsigned char *encrypt(unsigned char *plaintext, size_t size, unsigned char *key, unsigned char *counter, bool debug);
unsigned char *decrypt(unsigned char *ciphertext, size_t size, unsigned char *key, unsigned char *counter, bool debug);
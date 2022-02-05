#include "../lib/key_expansion.h"
#include "../lib/initializations.h"
#include "../lib/ctr.h"
#include "../lib/aes.h"
#include "../lib/utils.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define DEBUG false
#define PLAINTEXT_FILENAME "file"
#define CIPHERTEXT_FILENAME "enc"
#define KEY_FILENAME "key"
#define NONCE_FILENAME "nonce"


unsigned char *encrypt_cuda(unsigned char *plaintext, size_t size, unsigned char *key, unsigned char *counter, bool debug);
unsigned char *decrypt_cuda(unsigned char *ciphertext, size_t size, unsigned char *key, unsigned char *counter, bool debug);
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
#include <omp.h>

#define DEBUG false
#define PLAINTEXT_FILENAME "file"
#define CIPHERTEXT_FILENAME "enc"
#define KEY_FILENAME "key"
#define NONCE_FILENAME "nonce"
#define NUM_THREADS 8

unsigned char *encrypt(unsigned char *plaintext, size_t size, unsigned char *key, unsigned char *counter, bool debug);
unsigned char *decrypt(unsigned char *ciphertext, size_t size, unsigned char *key, unsigned char *counter, bool debug);
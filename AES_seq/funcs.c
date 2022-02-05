#include "funcs.h"

unsigned char *encrypt(unsigned char *plaintext, size_t size, unsigned char *key, unsigned char *counter, bool debug) {
    size_t nblocks;
    unsigned char *expansion, *ciphertext, *block;

    expansion = key_expansion(key, BLOCK_SIZE);
    if (DEBUG) {
        printf("Expanded key : ");
        print_data(expansion, BLOCK_SIZE*ROUNDS_NUMBER + 1);
        printf("Nonce : ");
        print_data(counter, BLOCK_SIZE); 
    }

    nblocks = size / BLOCK_SIZE + (size % BLOCK_SIZE != 0);

    ciphertext = (unsigned char*) malloc(nblocks * BLOCK_SIZE * sizeof(unsigned char));
    block = (unsigned char*) malloc(BLOCK_SIZE * sizeof(unsigned char));

    for (int i = 0; i < nblocks; i++) {
        get_ith_item(block, plaintext, i, BLOCK_SIZE);
        if (DEBUG) 
        {
            printf("Block before encryption/decryption i = %d : ",i); 
            print_data(block, BLOCK_SIZE);
        }

        encrypt_block(block, expansion, counter);
        if (DEBUG) 
        {
            printf("Encrypted/Decryption block : ");
            print_data(block, BLOCK_SIZE); 
        }

        memcpy(ciphertext + BLOCK_SIZE*i, block, BLOCK_SIZE);

        next_counter(counter);
        if (DEBUG) 
        {
            printf("Next counter : ");
            print_data(counter, BLOCK_SIZE); 
        }
    }

    free(block);
    block = NULL;

    return ciphertext;
}

unsigned char *decrypt(unsigned char *ciphertext, size_t size, unsigned char *key, unsigned char *counter, bool debug) {
    return encrypt(ciphertext, size, key, counter, debug);
}
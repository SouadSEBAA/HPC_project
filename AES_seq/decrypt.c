#include "functions.h"

#define PLAINTEXT_FILENAME "dec"

int main(int argc, char *argv[]) {
    //read key
    int l = 0;
    unsigned char * key = read_from_file(KEY_FILENAME, &l);
    if (l != BLOCK_SIZE) 
    {
        printf("The given key is %d bytes not %d bytes in length !\n", l, BLOCK_SIZE);
        exit(1);
    }

    //read nonce
    l = 0;
    unsigned char * counter = read_from_file(NONCE_FILENAME, &l);
    if (l != BLOCK_SIZE) 
    {
        printf("The given nonce is %d bytes not %d bytes in length !\n", l, BLOCK_SIZE);
        exit(1);
    }

    //read blocks
    int size = 0;
    unsigned char * ciphertext = read_from_file(CIPHERTEXT_FILENAME, &size);
    int nb = size / BLOCK_SIZE + (size % BLOCK_SIZE != 0);
    if (DEBUG) 
    {
        printf("Number of blocks of this file is %d blocks\n", nb);
        printf("Size of this file is %d bytes\n", size);
    }

    //decryption
    unsigned char * plaintext = decrypt(ciphertext, size, key, counter, DEBUG);
    write_to_file(PLAINTEXT_FILENAME, plaintext, size);
        
    free(key);
    key = NULL;
    free(ciphertext);
    ciphertext = NULL;
    free(plaintext);
    plaintext = NULL;

    return 0;
}
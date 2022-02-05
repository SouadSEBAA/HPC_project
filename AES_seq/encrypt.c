#include "funcs.h"

int main(int argc, char *argv[]) {
    //read key
    int l = 0;
    unsigned char * key = read_from_file(KEY_FILENAME, &l);
    if (l != BLOCK_SIZE) 
    {
        printf("The given key is %d bytes not %d bytes in length !\n", l, BLOCK_SIZE);
        exit(1);
    }

    //generate nonce
    unsigned char *counter = generate_initial_counter();
    write_to_file(NONCE_FILENAME, counter, BLOCK_SIZE); //keep track of the used nonce, to use it in decryption

    //read blocks
    int size = 0;
    unsigned char * plaintext = read_from_file(PLAINTEXT_FILENAME, &size);
    int nb = size / BLOCK_SIZE + (size % BLOCK_SIZE != 0);
    if (DEBUG) 
    {
        printf("Number of blocks of this file is %d blocks\n", nb);
        printf("Size of this file is %d bytes\n", size);
    }

    //encryption
    unsigned char * ciphertext = encrypt(plaintext, size, key, counter, DEBUG);
    write_to_file(CIPHERTEXT_FILENAME, ciphertext, nb*BLOCK_SIZE);
        
    free(key);
    key = NULL;
    free(plaintext);
    plaintext = NULL;
    free(ciphertext);
    ciphertext = NULL;

    return 0;
}
#include "funcs.h"

int main(int argc, char *argv[]) {
    struct timespec t1, t2;
    double elapsed;

    printf("AES-CTR encryption - CUDA version\n");

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
    printf("Number of blocks of this file is %d blocks\n", nb);
    printf("Size of this file is %d bytes\n", size);

    //encryption
    clock_gettime(CLOCK_REALTIME, &t1);
    unsigned char * ciphertext = encrypt_cuda(plaintext, size, key, counter, DEBUG);
    clock_gettime(CLOCK_REALTIME, &t2);
    elapsed = measure_time(t1, t2);
    printf("Time measured: %.3f seconds.\n", elapsed);

    write_to_file(CIPHERTEXT_FILENAME, ciphertext, size);
        
    free(key);
    key = NULL;
    free(plaintext);
    plaintext = NULL;
    free(ciphertext);
    ciphertext = NULL;

    return 0;
}
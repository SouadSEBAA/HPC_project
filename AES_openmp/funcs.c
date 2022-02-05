#include "funcs.h"

unsigned char *encrypt(unsigned char *plaintext, size_t size, unsigned char *key, unsigned char *counter, bool debug) {
    size_t nblocks;
    unsigned char *expansion, *ciphertext, *blockPtr;
    unsigned char **counters;
    int i;
    clock_t t1, t2;
    float timeInS;

    expansion = key_expansion(key, BLOCK_SIZE);
    if (DEBUG) {
        printf("Expanded key : ");
        print_data(expansion, BLOCK_SIZE*ROUNDS_NUMBER + 1);
        printf("Nonce : ");
        print_data(counter, BLOCK_SIZE); 
    }

    nblocks = size / BLOCK_SIZE + (size % BLOCK_SIZE != 0);

    ciphertext = (unsigned char*) malloc(nblocks * BLOCK_SIZE * sizeof(unsigned char));
    counters = (unsigned char**) malloc(nblocks * sizeof(unsigned char*));

    for (i = 0; i < nblocks; i++) {
        counters[i] = (unsigned char*) malloc(BLOCK_SIZE * sizeof(unsigned char));
        memcpy(counters[i], counter, BLOCK_SIZE);
        next_counter(counter);
    }

    t1 = clock();

    #pragma omp parallel private(i, blockPtr) shared(plaintext, expansion, counters, ciphertext) num_threads(NUM_THREADS)
    {
        #pragma omp for
        for (i = 0; i < nblocks; i++) {
            blockPtr = ciphertext + BLOCK_SIZE*i;

            get_ith_item(blockPtr, plaintext, i, BLOCK_SIZE);
            if (DEBUG) 
            {
                printf("Current counter : ");
                print_data(counters[i], BLOCK_SIZE); 
                printf("Block before encryption/decryption i = %d : ",i); 
                print_data(blockPtr, BLOCK_SIZE);
            }

            encrypt_block(blockPtr, expansion, counters[i]);
            if (DEBUG) 
            {
                printf("Encrypted/Decryption block : ");
                print_data(blockPtr, BLOCK_SIZE); 
            }

            free(counters[i]);
            counters[i] = NULL;
        }
    }

    t2 = clock();

    timeInS = (float)(t2-t1)/CLOCKS_PER_SEC;
    printf("time = %fs\n", timeInS);

    free(counters);
    counters = NULL;

    return ciphertext;
}

unsigned char *decrypt(unsigned char *ciphertext, size_t size, unsigned char *key, unsigned char *counter, bool debug) {
    return encrypt(ciphertext, size, key, counter, debug);
}
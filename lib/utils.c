#include "initializations.h"
#include <stdlib.h>

//to xor two blocks of BLOCK_SIZE bytes
unsigned char * xor(unsigned char *block1, unsigned char* block2)
{
    unsigned char *result = (unsigned char *) malloc(BLOCK_SIZE * sizeof(unsigned char));

    for (int i = 0; i < BLOCK_SIZE; i++)
        result[i] = block1[i] ^ block2[i];
    
    return result;
}

unsigned char * get_ith_subkey(unsigned char *expanded_key, int i)
{
    unsigned char *subkey = (unsigned char *) malloc(BLOCK_SIZE * sizeof(unsigned char));

    for (int j = 0; j < BLOCK_SIZE; j++)
        subkey[j] = expanded_key[i*BLOCK_SIZE + j];
    
    return subkey;
}
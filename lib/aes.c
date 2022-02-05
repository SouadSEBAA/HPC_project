#include "initializations.h"
#include "aes_steps.h"
#include "utils.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#if __NVCC__ 
__device__ 
#endif
unsigned char * F(unsigned char *block, unsigned char *expanded_key)
{
    int round = 0;

    //get copy of block in state variable
    unsigned char *state = (unsigned char *) malloc(BLOCK_SIZE * sizeof(unsigned char));
    memcpy(state, block, BLOCK_SIZE);

    //get first subkey from the expanded key
    unsigned char *subkey = (unsigned char *) malloc(BLOCK_SIZE * sizeof(unsigned char));
    get_ith_item(subkey, expanded_key, round, BLOCK_SIZE);

    addRoundKey(state, subkey);

    for (round = 1; round <= ROUNDS_NUMBER; round++)
    {
        subytes(state);
        shiftRows(state);
        if (round != ROUNDS_NUMBER) mixColumns(state);
        get_ith_item(subkey, expanded_key, round, BLOCK_SIZE);
        addRoundKey(state, subkey);
    }

    free(subkey); subkey = NULL;
    return state;
}

#if __NVCC__ 
__device__ 
#endif
//it will encrypt block using the expanded_key and counter, result will be in block
void encrypt_block(unsigned char *block, unsigned char *expanded_key, unsigned char *counter)
{
    unsigned char *p = F(counter, expanded_key);
    xor_blocks(block, p);

    free(p); p = NULL;
}
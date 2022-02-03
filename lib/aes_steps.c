#include "aes_steps.h"
#include "initializations.h"
#include <stdlib.h>
#include <stdio.h>

void subytes(unsigned char *block){

    for (int i = 0; i < BLOCK_SIZE; i++)
    {
        block[i] = sbox[block[i]];
    }
}


void addRoundKey(unsigned char *block, unsigned char *subkey){

    for (int i = 0; i < BLOCK_SIZE; i++)
    {
        block[i] ^= subkey[i];
    }
}


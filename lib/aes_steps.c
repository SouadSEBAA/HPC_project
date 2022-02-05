#include "aes_steps.h"
#include "initializations.h"
#include <stdlib.h>
#include <stdio.h>

#if __NVCC__ 
__device__
#endif
void subytes(unsigned char *block){

    for (int i = 0; i < BLOCK_SIZE; i++)
    {
        block[i] = sbox[block[i]];
    }
}

#if __NVCC__ 
__device__
#endif
void addRoundKey(unsigned char *block, unsigned char *subkey){

    for (int i = 0; i < BLOCK_SIZE; i++)
    {
        block[i] ^= subkey[i];
    }
}

#if __NVCC__ 
__device__
#endif
void shiftRows(unsigned char *block) {
    unsigned char tmp;

    tmp = block[1];
    block[1] = block[5];
    block[5] = block[9];
    block[9] = block[13];
    block[13] = tmp;

    tmp = block[10];
    block[10] = block[2];
    block[2] = tmp;

    tmp = block[14];
    block[14] = block[6];
    block[6] = tmp;

    tmp = block[3];
    block[3] = block[15];
    block[15] = block[11];
    block[11] = block[7];
    block[7] = tmp;
}

#if __NVCC__ 
__device__
#endif
void mixColumns(unsigned char *block) {
    unsigned char b[4];
    int i;

    for (i = 0; i < BLOCK_SIZE; i += 4) {
        b[0] = block[i];
        b[1] = block[i+1];
        b[2] = block[i+2];
        b[3] = block[i+3];

        block[i+0] = mixColMatrix[b[0]][0] ^ mixColMatrix[b[1]][1] ^ b[2] ^ b[3];
        block[i+1] = b[0] ^ mixColMatrix[b[1]][0] ^ mixColMatrix[b[2]][1] ^ b[3];
        block[i+2] = b[0] ^ b[1] ^ mixColMatrix[b[2]][0] ^ mixColMatrix[b[3]][1];
        block[i+3] = mixColMatrix[b[0]][1] ^ b[1] ^ b[2] ^ mixColMatrix[b[3]][0];
    }
}
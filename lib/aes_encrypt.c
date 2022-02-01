#include "initializations.h"
#include "aes_steps.h"
#include "utils.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

unsigned char * F(unsigned char *block, unsigned char *expanded_key)
{
    unsigned char *state = (unsigned char *) malloc(BLOCK_SIZE * sizeof(unsigned char));
    memcpy(state, block, BLOCK_SIZE);
    int round = 0;

    addRoundKey(state, get_ith_subkey(expanded_key, round));

    for (round = 1; round <= ROUNDS_NUMBER; round++)
    {
        subytes(state);
        //shift_rows
        //mix_columns
        if (round != ROUNDS_NUMBER) addRoundKey(state, get_ith_subkey(expanded_key, round));
    }

    return state;
}

unsigned char *encrypt_block(unsigned char *block, unsigned char *expanded_key, unsigned char *counter)
{
    return xor(block, F(counter, expanded_key));
}
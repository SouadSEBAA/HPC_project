#include "initializations.h"
#include <stdlib.h>
#include <stdio.h>


void rotword(unsigned char * tab){ //tab should be a word, thus it is 4 bytes in length
    unsigned char save = tab[0];
    int  i;
    for (i = 0; i < 4-1; i++)
        tab[i] = tab[i+1];

    tab[i] = save;
}

void subword(unsigned char * tab){ //tab should be a word, thus it is 4 bytes in length
    for (int i = 0; i < 4; i++)
        tab[i] = sbox[tab[i]];
}

unsigned char * key_expansion(unsigned char *key, int key_length){ //key_length in bytes
    int Nr = ROUNDS_NUMBER; //number of rounds
    int Nb = 4 ; //number of words in a block
    int Nk = key_length / 4; //number of words in key

    unsigned char *w = (unsigned char *) malloc(4*(Nr+1)*Nb * sizeof(unsigned char));

    //first subkey is the key itself
    for (int j = 0; j < BLOCK_SIZE; j++)
        w[j] = key[j];

    //compute next subkeys
    for (int i = Nk; i < Nb*(Nr+1); i++)
    {
        int k = (i - 1) * 4;
        unsigned char temp[4] = { w[k], w[k+1], w[k+2], w[k+3] }; //temp is equivalent to w[i-1]
        unsigned char c = 0;

        if (i % Nk == 0)
        {
            rotword(temp);
            subword(temp);
            c = rcon[i / Nk - 1];
        }
        else if (Nk > 6 && i % Nk == 4)
        {
            subword(temp);
        }

        for (int j = 0; j < 4; j++)
        {
            w[4*i + j] = w[4*(i-Nk) + j] ^ temp[j] ^ c;   //this operation is equivalent to w[i] = w[i-Nk] xor temp xor c
            c = 0;
        }      
        
    }

    return w;
}

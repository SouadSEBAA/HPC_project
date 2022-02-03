#include "initializations.h"
#include <stdlib.h>
#include <time.h>

unsigned char * generate_initial_counter()
{
    unsigned char *nonce = (unsigned char *) malloc(BLOCK_SIZE * sizeof(unsigned char));
    srand(time(0));

    for (int i = 0; i < BLOCK_SIZE; i++)
    {
        nonce[i] = rand() & 0xff;
    }

    return nonce;
}

void increment_counter(unsigned char *counter, int inc)
{
    int i = BLOCK_SIZE - 1;
    int stop = 0;
    while (i >= 0 && !stop)
    {
        if (counter[i] < 0xff)
        {
            counter[i] += inc;
            stop = 1;
        }
        else
        {
            counter[i] = 0;
            i--;
        }
    }
}

void next_counter(unsigned char *counter)
{
    increment_counter(counter, 1);
}
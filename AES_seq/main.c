#include "../lib/aes_steps.h"
#include "../lib/key_expansion.h"
#include "../lib/initializations.h"
#include "../lib/ctr.h"
#include "../lib/aes_encrypt.h"
#include "../lib/utils.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(){

    //read key
    int l = 0;
    unsigned char * key = read_from_file("key", &l);
    if (l != BLOCK_SIZE) 
    {
        printf("The given key is %d bytes not %d bytes in length !\n", l, BLOCK_SIZE);
        exit(1);
    }

    //expand key
    unsigned char *expansion = key_expansion(key, BLOCK_SIZE);    
    printf("Expanded key : ");
    print_data(expansion, BLOCK_SIZE*ROUNDS_NUMBER + 1);
    
    //generate nonce
    unsigned char *counter = generate_initial_counter();
    write_to_file("nonce", counter, BLOCK_SIZE); //keep track of the used nonce, to use it in decryption
    printf("Nonce : ");
    print_data(counter, BLOCK_SIZE); 

    //read blocks
    int size = 0;
    unsigned char * data = read_from_file("file", &size);
    int nb = size / BLOCK_SIZE;
    if (nb % BLOCK_SIZE != 0) nb ++;

    //start encryption
    unsigned char * enc = (unsigned char *) malloc(nb*BLOCK_SIZE * sizeof(unsigned char));
    unsigned char * block = (unsigned char *) malloc(BLOCK_SIZE * sizeof(unsigned char));

    for (int i = 0; i < nb; i++)
    {
        get_ith_item(block, data, i, BLOCK_SIZE);
        printf("Block before encryption i = %d : ",i);
        print_data(block, BLOCK_SIZE);

        encrypt_block(block, expansion, counter);
        printf("encrypted block : ");
        print_data(block, BLOCK_SIZE); 

        memcpy(enc + BLOCK_SIZE*i, block, BLOCK_SIZE);
        next_counter(counter);
         
        printf("next counter : ");
        print_data(counter, BLOCK_SIZE); 

    }

    write_to_file("enc", enc, nb*BLOCK_SIZE);
        
    free(key);
    free(data);
    free(enc);
    return 0;
}
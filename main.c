#include "lib/aes_steps.h"
#include "lib/key_expansion.h"
#include "lib/initializations.h"
#include "lib/ctr.h"
#include "lib/aes_encrypt.h"
#include "lib/utils.h"
#include <stdio.h>
#include <string.h>



int main(){
    unsigned char test_key[16] = {0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c};
    unsigned char block[16] = {0x32, 0x43, 0xf6, 0xa8, 0x88, 0x5a, 0x30, 0x8d, 0x31, 0x31, 0x98, 0xa2, 0xe0, 0x37, 0x07, 0x34 };

    /***** test add round key *****

    addRoundKey(block, test_key);
    print_data(block, BLOCK_SIZE);

    /***** test subytes *****

    subytes(block);
    print_data(block, BLOCK_SIZE);

    /***** test key expansion *****

    unsigned char *expansion;
    expansion = key_expansion(test_key, 16);    
    
    print_data(expansion, 16*11);

    /***** test nonce generation *****

    unsigned char *nonce;
    nonce = generate_initial_counter(); 
    print_data(nonce, 16);

    for (int i = 0; i < 25; i++)
    {   
        next_counter(nonce);
        print_data(nonce, 16);
    }

    /***** TO-DO : test encrypt_block *****
    // TO-DO : free pointers where they should be freed
    print_data(encrypt_block(block, expansion, nonce),BLOCK_SIZE);
    
    /***** test read file *****/
    int l = 0;
    unsigned char* data = read_from_file("test_file", &l);
    print_data(data, BLOCK_SIZE);

    /***********************/

    //read key
    //expand key
    //generate nonce
    //write the nonce
    //for
    //extract one block from file
    //encrypt it
    //write it



    return 0;
}
#include "initializations.h"
#include <stdlib.h>
#include <stdio.h>

//to xor two blocks of BLOCK_SIZE bytes
void xor(unsigned char *block1, unsigned char* block2)
{
    for (int i = 0; i < BLOCK_SIZE; i++)
        block1[i] ^= block2[i];
}

//get the ith block of size l in buffer, the result will be in dest
void get_ith_item(unsigned char *dest, unsigned char *buffer, int i, int l)
{
    for (int j = 0; j < l; j++)
        dest[j] = buffer[i*l + j];
}

void print_data(unsigned char *data, int length)
{
    for (int i = 0; i<length; i++)
        printf("%x ", data[i]);
    printf("\n");
}

//returns a buffer and writes the file size to file_size
unsigned char * read_from_file(char *file_name, int *file_size)
{
    FILE *f = fopen(file_name, "rb");
    unsigned char *buffer;

    //calculate size of file
    fseek(f, 0, SEEK_END);        
    *file_size = ftell(f);          
    rewind(f); 

    //TO-DO: accept files of a limited size

    //allocate memory and read the file
    long to_allocate = *file_size + (*file_size % BLOCK_SIZE);
    buffer = (unsigned char *)calloc(to_allocate, sizeof(unsigned char));
    fread(buffer, *file_size, 1, f); 
    fclose(f);

    return buffer;
}

void write_to_file(char *file_name, unsigned char *buffer, long n)
{
    FILE *f = fopen(file_name, "wb");

    fwrite(buffer, n, 1, f); 
    fclose(f);
}
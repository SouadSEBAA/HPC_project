#define BLOCK_SIZE 16 //in bytes
#define ROUNDS_NUMBER 10

void subytes(unsigned char *block);
void addRoundKey(unsigned char *block, unsigned char *subkey);

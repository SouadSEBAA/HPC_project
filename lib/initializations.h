#define BLOCK_SIZE 16 //in bytes
#define ROUNDS_NUMBER 10

extern const unsigned char rcon[ROUNDS_NUMBER];
extern const unsigned char sbox[BLOCK_SIZE*BLOCK_SIZE];
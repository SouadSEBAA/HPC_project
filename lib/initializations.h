#define BLOCK_SIZE 16 //in bytes
#define ROUNDS_NUMBER 10


extern const unsigned char rcon[ROUNDS_NUMBER];

#if __NVCC__ 
__device__ 
#endif
extern const unsigned char sbox[BLOCK_SIZE*BLOCK_SIZE];

#if __NVCC__ 
__device__ 
#endif
extern const unsigned char mixColMatrix[BLOCK_SIZE*BLOCK_SIZE][6];
#if __NVCC__ 
__device__ 
#endif
void encrypt_block(unsigned char *block, unsigned char *expanded_key, unsigned char *counter);
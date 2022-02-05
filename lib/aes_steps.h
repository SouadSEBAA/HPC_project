#if __NVCC__ 
__device__
#endif
void subytes(unsigned char *block);

#if __NVCC__
__device__
#endif
void addRoundKey(unsigned char *block, unsigned char *subkey);

#if __NVCC__ 
__device__
#endif
void shiftRows(unsigned char *block);

#if __NVCC__ 
__device__
#endif
void mixColumns(unsigned char *block);
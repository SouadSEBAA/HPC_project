unsigned char * generate_initial_counter();

#if __NVCC__ 
__device__ 
#endif
void next_counter(unsigned char *counter);

#if __NVCC__ 
__device__ 
#endif
void increment_counter(unsigned char *counter, int inc);
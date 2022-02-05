#include <time.h>

#if __NVCC__ 
__device__
#endif
void xor_blocks(unsigned char *block1, unsigned char* block2);

#if __NVCC__ 
__device__ __host__
#endif
void get_ith_item(unsigned char *dest, unsigned char *buffer, int i, int l);

#if __NVCC__ 
__device__ __host__
#endif
void print_data(unsigned char *data, int length);

unsigned char * read_from_file(char *file_name, int *file_size);
void write_to_file(char *file_name, unsigned char *buffer, long n);
double measure_time(struct timespec begin, struct timespec end);
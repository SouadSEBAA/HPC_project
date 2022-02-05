#include "funcs.h"

#define THREAD_PER_BLOCK 512
#define NB_BLOCKS 1

__global__ void device_encrypt (unsigned char *plaintext , unsigned char *ciphertext , unsigned char *nonce, unsigned char *expansion, size_t N)
{
    int i = threadIdx.x;
    unsigned char* block = (unsigned char*) malloc(BLOCK_SIZE * sizeof(unsigned char));
    unsigned char* counter = (unsigned char*) malloc(BLOCK_SIZE * sizeof(unsigned char));
    memcpy(counter, nonce, BLOCK_SIZE);

    if (i < N && i < THREAD_PER_BLOCK)
    {
        get_ith_item(block, plaintext, i, BLOCK_SIZE);
        if (DEBUG) 
        {
            printf("Block before encryption/decryption i = %d : ",i); 
            print_data(block, BLOCK_SIZE);
        }

        increment_counter(counter, i);
        if (DEBUG) 
        {
            printf("Counter : ");
            print_data(counter, BLOCK_SIZE); 
        }

        encrypt_block(block, expansion, counter);
        if (DEBUG) 
        {
            printf("Encrypted/Decryption block : ");
            print_data(block, BLOCK_SIZE); 
        }

        memcpy(ciphertext + BLOCK_SIZE*i, block, BLOCK_SIZE);

    }

    free(block);
    block = NULL;
    free(counter);
    counter = NULL;

}

void kernel_encrypt_wrapper(unsigned char *plaintext , unsigned char *ciphertext , unsigned char *nonce, unsigned char *expansion, size_t N)
{
    unsigned char *gpu_expansion , *gpu_ciphertext , *gpu_plaintext, *gpu_nonce;
    cudaEvent_t start, stop;
    float elapsedTime;

    //allocate memory in the device
    int size_data = N * BLOCK_SIZE * sizeof(unsigned char);
    int size_expansion = 4*(ROUNDS_NUMBER+1)*4 * sizeof(unsigned char);
    cudaMalloc ((void**) &gpu_ciphertext, size_data);
    cudaMalloc ((void**) &gpu_plaintext, size_data);
    cudaMalloc ((void**) &gpu_nonce, BLOCK_SIZE);
    cudaMalloc ((void**) &gpu_expansion, size_expansion);

    //copy data 
    cudaMemcpy(gpu_plaintext, plaintext, size_data, cudaMemcpyHostToDevice);
    cudaMemcpy(gpu_nonce, nonce, BLOCK_SIZE, cudaMemcpyHostToDevice);
    cudaMemcpy(gpu_expansion, expansion, size_expansion, cudaMemcpyHostToDevice);

    //for time
    cudaEventCreate(&start);
    cudaEventRecord(start,0);
    cudaEventCreate(&stop);

    //execute on device
    device_encrypt <<<NB_BLOCKS,THREAD_PER_BLOCK>>> (gpu_plaintext, gpu_ciphertext, gpu_nonce, gpu_expansion, N);

    //copy results
    cudaMemcpy(ciphertext, gpu_ciphertext, size_data, cudaMemcpyDeviceToHost);

    //calculate time
    cudaEventRecord(stop,0);
    cudaEventSynchronize(stop);
    cudaEventElapsedTime(&elapsedTime, start,stop);

    printf("time = %f ms\n" ,elapsedTime);

    cudaFree(gpu_ciphertext);
    cudaFree(gpu_plaintext);
    cudaFree(gpu_nonce);
    cudaFree(gpu_expansion);
}


unsigned char *encrypt_cuda(unsigned char *plaintext, size_t size, unsigned char *key, unsigned char *counter, bool debug) {
    size_t nblocks;
    unsigned char *expansion, *ciphertext;

    expansion = key_expansion(key, BLOCK_SIZE);
    if (DEBUG) {
        printf("Expanded key : ");
        print_data(expansion, BLOCK_SIZE*ROUNDS_NUMBER + 1);
        printf("Nonce : ");
        print_data(counter, BLOCK_SIZE); 
    }

    nblocks = size / BLOCK_SIZE + (size % BLOCK_SIZE != 0);

    ciphertext = (unsigned char*) malloc(nblocks * BLOCK_SIZE * sizeof(unsigned char));
   
    kernel_encrypt_wrapper(plaintext, ciphertext, counter, expansion, nblocks);

    return ciphertext;
}

unsigned char *decrypt_cuda(unsigned char *ciphertext, size_t size, unsigned char *key, unsigned char *counter, bool debug) {
    return encrypt_cuda(ciphertext, size, key, counter, debug);
}
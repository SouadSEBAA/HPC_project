void xor(unsigned char *block1, unsigned char* block2);
void get_ith_item(unsigned char *dest, unsigned char *buffer, int i, int l);
void print_data(unsigned char *data, int length);
unsigned char * read_from_file(char *file_name, int *file_size);
void write_to_file(char *file_name, unsigned char *buffer, long n);
void subytes(unsigned char *block);
void addRoundKey(unsigned char *block, unsigned char *subkey);
void shiftRows(unsigned char *block);
void mixColumns(unsigned char *block);
CC=gcc
CFLAGS=
SOURCE_FILES=funcs.c ../lib/*.c
SOURCE_ENC=encrypt.c
OUTFILE_ENC=encrypt
SOURCE_DEC=decrypt.c
OUTFILE_DEC=decrypt

all: encrypt decrypt

encrypt: $(SOURCE_ENC)
	$(CC) $(CFLAGS) -D BuiltWithMake -o $(OUTFILE_ENC) $(SOURCE_ENC) $(SOURCE_FILES)
	chmod +x $(OUTFILE_ENC)

decrypt: $(SOURCE_DEC)
	$(CC) $(CFLAGS) -D BuiltWithMake -o $(OUTFILE_DEC) $(SOURCE_DEC) $(SOURCE_FILES)
	chmod +x $(OUTFILE_DEC)

clean:
	rm encrypt decrypt

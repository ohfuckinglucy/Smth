#ifndef CIPHER_H
#define CIPHER_H

void read_file_content(const char *filename, char **content);
void sort_columns(char *key, int key_len, int rows, char **arr, int *original_index);
void decrypt_columns(char *key, int key_len, int rows, char **arr, int *original_index);

#endif


// gcc -c main.c
// gcc -c -fPIC encrypt_decrypt.c

// gcc -shared -o libpointd.so encrypt_decrypt.o

// gcc -o main main.o -L. -lpointd -Wl,-rpath,.

// ./dyn
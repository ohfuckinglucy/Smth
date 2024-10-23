// прототип функции encrypt_decrypt

void encrypt_decrypt(char *text, char *key, int text_length, int key_length);

// gcc -c main.c
// gcc -c -fPIC encrypt_decrypt.c

// gcc -shared -o libpointd.so encrypt_decrypt.o

// gcc -o dyn main.o -L. -lpointd -Wl,-rpath,.

// ./dyn
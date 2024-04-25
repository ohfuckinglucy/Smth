#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

void encrypt_decrypt(char *text, char *key, int text_length, int key_length) {
    for (int i = 0; i < text_length; ++i) {
        text[i] = text[i] ^ key[i % key_length];
    }
}
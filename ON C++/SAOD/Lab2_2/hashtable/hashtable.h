#include <iostream>
#include <string.h>
#include <sys/time.h>

#define HASH_SIZE 128
#define HASHTAB_SIZE 5051

struct listnode{
char *key;
int value;

struct listnode *next;
};

struct listnode *hashtab[HASHTAB_SIZE];

unsigned int KRHash(char *s){
    unsigned int h = 0, hash_mul = 31;
    while (*s)
        h = h * hash_mul + (unsigned int)*s++;
    return h % HASH_SIZE;
}
void hashtab_init(struct listnode **hashtab){
    int i;

    for (i = 0; i < HASHTAB_SIZE; i++)
        hashtab[i] = NULL;
}
void hashtab_add(struct listnode **hashtab, char *key, int value){
    struct listnode *node;

    int index = KRHash(key);
    node = (listnode*)malloc(sizeof(*node));
    if (node != NULL) {
        node->key = key;
        node->value = value;
        node->next = hashtab[index];
        hashtab[index] = node;
    }
}
struct listnode *hashtab_lookup(struct listnode **hashtab, char *key){
    struct listnode *node;

    int index = KRHash(key);
    for (node = hashtab[index]; node != NULL; node = node->next) {
        if (0 == strcmp(node->key, key))
            return node;
    }
    return NULL;
}
void hashtab_delete(struct listnode **hashtab, char *key){
    struct listnode *node, *prev = NULL;
    int index = KRHash(key);
    for (node = hashtab[index]; node != NULL; node = node->next) {
        if (0 == strcmp(node->key, key)) {
            if (prev == NULL)
                hashtab[index] = node->next;
            else
                prev->next = node->next;
        free(node);
        return;
        }
        prev = node;
    }
}

double wtime(){
    struct timeval t;
    gettimeofday(&t, NULL);
    return (double)t.tv_sec + (double)t.tv_usec * 1E-6;
}
int getrand(char min, char max){
    return (double)rand() / (RAND_MAX + 1.0) * (max - min) + min;
}
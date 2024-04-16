#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include "hashmap.h"

typedef struct _hash_map_entry_t{
    char *key;
    long value;
} hash_map_entry_t;

struct _hash_map_t{
    hash_map_entry_t *entries;
    size_t size;
};

hash_map_t *hash_map_create(size_t size){
    hash_map_t *map = malloc(sizeof(hash_map_t));
    assert(map != NULL);

    map -> size = size;
    map -> entries = calloc(map->size, sizeof(hash_map_entry_t));

    assert(map -> entries != NULL);
    return map;
}

hash_map_t *hash_map_insert(hash_map_t *map, const char *key, long value){
    assert(map != NULL);
    assert(key != NULL);

    size_t idx = hash(key) % map -> size;

    while (map -> entries[idx].key != NULL){
        idx += 1;

        if (idx == map -> size){
            /* TODO: expand hash map */
        }
    }

    map -> entries[idx].key = calloc(strlen(key)+ 1, sizeof(char));
    map -> entries[idx].value = value;

    assert(map -> entries[idx].key != NULL);
    strcpy(map -> entries[idx].key, key);

    return map;
};

bool hash_map_has_key(hash_map_t *map, const char *key){
    assert(map != NULL);
    assert(key != NULL);

    for (size_t idx = hash(key) % map -> size; idx < map -> size; idx ++){
        char *current = map -> entries[idx].key;

        if (current == NULL){
            continue;
        }

        if (!strcmp(current, key)){
            return true;
        }
    }
    return false;
}
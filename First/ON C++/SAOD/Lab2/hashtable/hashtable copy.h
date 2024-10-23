#include <iostream>
#include <string>
#include <vector>
#include <sys/time.h>
#include <chrono>

using namespace std;

struct ListNode {
    string key;
    uint32_t value;
    ListNode* next;

    ListNode(const string& k, uint32_t v) : key(k), value(v), next(nullptr) {}
};

using HashTable = vector<ListNode*>;

uint32_t hashtab_hash(const string& key, uint32_t table_size) {
    uint32_t hashval = 0;
    for (char c : key) {
        hashval = hashval * 37 + c;
    }
    return hashval % table_size;
}

void hashtab_init(HashTable& hashtab, uint32_t table_size) {
    hashtab.resize(table_size, nullptr);
}

void hashtab_add(HashTable& hashtab, const string& key, uint32_t value) {
    uint32_t index = hashtab_hash(key, hashtab.size());
    ListNode* newNode = new ListNode(key, value);
    
    if (hashtab[index] == nullptr) {
        hashtab[index] = newNode;
    } else {
        ListNode* current = hashtab[index];
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newNode;
    }
}


ListNode* hashtab_lookup(const HashTable& hashtab, const string& key) {
    uint32_t index = hashtab_hash(key, hashtab.size());
    ListNode* currentNode = hashtab[index];
    while (currentNode != nullptr) {
        if (currentNode->key == key) {
            return currentNode;
        }
        currentNode = currentNode->next;
    }
    return nullptr;
}

void hashtab_delete(HashTable& hashtab, const string& key) {
    uint32_t index = hashtab_hash(key, hashtab.size());
    ListNode* prevNode = nullptr;
    ListNode* currentNode = hashtab[index];
    while (currentNode != nullptr) {
        if (currentNode->key == key) {
            if (prevNode == nullptr) {
                hashtab[index] = currentNode->next;
            } else {
                prevNode->next = currentNode->next;
            }
            delete currentNode;
            return;
        }
        prevNode = currentNode;
        currentNode = currentNode->next;
    }
    cerr << "Element with key '" << key << "' not found for deletion." << endl;
}

int getrand(int min, int max) {
    return (double)rand() / (RAND_MAX + 1.0) * (max - min) + min;
}

double wtime() {
    auto now = std::chrono::high_resolution_clock::now();
    auto duration = now.time_since_epoch();
    return std::chrono::duration_cast<std::chrono::duration<double>>(duration).count();
}

uint32_t kr_hash(const string& key, uint32_t table_size) {
    uint32_t hashval = 0;
    for (char ch : key) {
        hashval = (hashval * 131) + ch;
    }
    return hashval % table_size;
}

uint32_t djb_hash(const string& key, uint32_t table_size) {
    uint32_t hashval = 5381;
    for (char c : key) {
        hashval = ((hashval << 5) + hashval) + c;
    }
    return hashval % table_size;
}


double measure_time(HashTable& hashtab, const string& key, uint32_t (*hash_func)(const string&, uint32_t)) {
    double start_time = wtime();

    hashtab_lookup(hashtab, key);

    return wtime() - start_time;
}


void choosehashtab_add(HashTable& hashtab, const string& key, uint32_t value, uint32_t (*hash_func)(const string&, uint32_t), uint32_t& collisions) {
    uint32_t index = hash_func(key, hashtab.size());
    
    if (hashtab[index] != nullptr) {
        // Цепочка уже существует, добавляем узел в конец цепочки
        ListNode* current = hashtab[index];
        while (current->next != nullptr) {
            if (current->key == key) {
                collisions++;
                return; // Уже существует узел с таким ключом, ничего не делаем
            }
            current = current->next;
        }
        current->next = new ListNode(key, value);
    } else {
        // Создаем новую цепочку
        hashtab[index] = new ListNode(key, value);
    }
}


uint32_t count_collisions(const HashTable& hashtab) {
    uint32_t collisions = 0;
    for (const auto& node : hashtab) {
        ListNode* current = node;
        while (current != nullptr) {
            if (current->next != nullptr) {
                collisions++;
            }
            current = current->next;
        }
    }
    return collisions;
}

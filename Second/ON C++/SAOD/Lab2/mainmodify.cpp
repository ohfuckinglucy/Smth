#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

struct TrieNode {
    char value;
    bool isEndOfWord;
    string data;  // Значение для упорядоченного словаря
    TrieNode* children[26];
};


struct Trie {
    TrieNode* root;
};

TrieNode* trie_create_node() {
    TrieNode* node = new TrieNode();
    node->isEndOfWord = false;
    for (int i = 0; i < 26; i++) {
        node->children[i] = nullptr;
    }
    return node;
}

Trie* trie_create() {
    Trie* trie = new Trie();
    trie->root = trie_create_node();
    return trie;
}


void trie_insert(Trie* trie, const string& key, const string& value) {
    TrieNode* node = trie->root;
    for (char c : key) {
        int index = c - 'a';
        if (node->children[index] == nullptr) {
            node->children[index] = trie_create_node();
        }
        node = node->children[index];
    }
    node->isEndOfWord = true;
    node->data = value;  // Сохранение значения
} 

TrieNode* trie_lookup(Trie* trie, const string& key) {
    TrieNode* node = trie->root;
    for (char c : key) {
        int index = c - 'a';
        if (node->children[index] == nullptr) {
            return nullptr;
        }
        node = node->children[index];
    }
    return (node != nullptr && node->isEndOfWord) ? node : nullptr;
}

bool trie_delete_helper(TrieNode* node, const string& key, int depth = 0) {
    if (node == nullptr) {
        return false;
    }

    if (depth == key.size()) {
        if (node->isEndOfWord) {
            node->isEndOfWord = false;
            return true;
        }
        return false;
    }

    int index = key[depth] - 'a';
    if (trie_delete_helper(node->children[index], key, depth + 1)) {
        delete node->children[index];
        node->children[index] = nullptr;
        return !node->isEndOfWord && all_of(begin(node->children), end(node->children), [](TrieNode* n) { return n == nullptr; });
    }
    return false;
}

void trie_delete(Trie* trie, const string& key) {
    trie_delete_helper(trie->root, key);
}

void trie_print_helper(TrieNode* node, const std::string& prefix, int level) {
    if (node->isEndOfWord) {
        std::cout << "Слово: " << prefix << ", Значение: " << node->data << "\n";
    }
    for (int i = 0; i < 26; i++) {
        if (node->children[i] != nullptr) {
            trie_print_helper(node->children[i], prefix + char(i + 'a'), level + 1);
        }
    }
}

void trie_print(Trie* trie) {
    trie_print_helper(trie->root, "", 0);
}


int main() {
    // Создаем trie и вставляем несколько ключей для примера
    Trie* trie = trie_create();

    trie_insert(trie, "apple", "fruit");
    trie_insert(trie, "banana", "fruit");
    trie_insert(trie, "strawberry", "berry");

    // Печатаем содержимое trie
    cout << "Содержимое trie:\n";
    trie_print(trie);

    // Поиск ключей
    string search_key = "banana";
    if (trie_lookup(trie, search_key)) {
        cout << search_key << " найдено в trie.\n";
    } else {
        cout << search_key << " не найдено в trie.\n";
    }

    // Удаление ключа
    trie_delete(trie, "banana");
    cout << "После удаления 'banana':\n";
    trie_print(trie);

    return 0;
}

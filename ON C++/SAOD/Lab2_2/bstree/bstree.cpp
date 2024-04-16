#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <cstring>
#include "bstree.h"

using namespace std;

int main() {
    int w;
    double t;
    ifstream file("words.txt");
    if (!file.is_open()) {
        cerr << "Failed to open file." << endl;
        return 1;
    }

    vector<char*> words;
    string word;
    file >> word; // Прочитать первое слово
    char* word_cstr = new char[word.size() + 1];
    strcpy(word_cstr, word.c_str());
    words.push_back(word_cstr); // Добавить первое слово в вектор
    bstree* tree = new bstree(0, word_cstr); // Создать дерево с первым словом
    while (file >> word) {
        word_cstr = new char[word.size() + 1];
        strcpy(word_cstr, word.c_str());
        words.push_back(word_cstr); // Добавить остальные слова в вектор
        tree->bstree_add(tree, 0, word_cstr); // Добавить слово в дерево
    }
    file.close();

    for (int i = 2; i < 200000; i++) {
        if (i % 10000 == 0) {
            w = getrand(0, i - 1); // Получить случайное число
            t = wtime();
            bstree* node = tree->bstree_lookup(tree, words[w]); // Найти слово в дереве по индексу
            t = wtime() - t;
            cout << "n = " << i - 1 << "; time = " << t << endl;
        }
    }

    // Освобождаем память, выделенную под каждое слово
    for (auto word_ptr : words) {
        delete[] word_ptr;
    }
    delete tree; // Освободить память, выделенную под дерево
    return 0;
}

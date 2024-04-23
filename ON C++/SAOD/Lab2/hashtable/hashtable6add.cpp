#include <iostream>
#include <fstream>
#include <vector>
#include <sys/time.h>
#include "hashtable.h"

using namespace std;

int main() {
    ifstream file("words.txt");
    if (!file.is_open()) {
        cerr << "Failed to open file." << endl;
        return 1;
    }

    HashTable hashtab_kr, hashtab_add;
    uint32_t table_size = 200000;

    vector<string> words;
    string word;
    while (file >> word) {
        words.push_back(word);
    }
    file.close();
    
    hashtab_init(hashtab_kr, table_size); // Инициализация хэш-таблицы для kr_hash
    hashtab_init(hashtab_add, table_size); // Инициализация хэш-таблицы для add_hash

    for (int i = 0; i < 200000; ++i) {
        uint32_t collisions_kr = 0, collisions_add = 0;
        choosehashtab_add(hashtab_kr, words[i], i, kr_hash, collisions_kr); // Добавление слова в хэш-таблицу для kr_hash
        choosehashtab_add(hashtab_add, words[i], i, add_hash, collisions_add); // Добавление слова в хэш-таблицу для add_hash
        if ((i + 1) % 10000 == 0) {
            string w;
            if (i > 0) {
                w = words[getrand(0, i - 1)];
            } else {
                w = words[0];
            }

            double t_kr = 0.0, t_add = 0.0;

            t_kr = measure_time(hashtab_kr, w, kr_hash); // Измерение времени для kr_hash
            t_add = measure_time(hashtab_add, w, add_hash); // Измерение времени для add_hash

            // collisions_kr = count_collisions(hashtab_kr); // Подсчет коллизий для kr_hash
            // collisions_add = count_collisions(hashtab_add); // Подсчет коллизий для add_hash

            cout << i + 1 << "\t\t\t" << t_kr << "\t\t\t" << collisions_add << "\t\t\t" << t_add << "\t\t\t" << collisions_add << endl;
        }
    }

    return 0;
}
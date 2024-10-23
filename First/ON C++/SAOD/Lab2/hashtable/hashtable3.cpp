#include <iostream>
#include <vector>
#include <fstream>
#include <sys/time.h>
#include "hashtable.h"
#include <iomanip>

using namespace std;

int main() {
    ifstream file("words.txt");
    if (!file.is_open()) {
        cerr << "Failed to open file." << endl;
        return 1;
    }
    uint32_t max_n = 200000;
    HashTable hashtab;

    vector<string> words;
    string word;
    while (file >> word) {
        words.push_back(word);
    }
    file.close();

    hashtab_init(hashtab, max_n);

    cout << "Количество элементов в словаре\tВремя выполнения функции hashtab_lookup, с" << endl;

    for (uint32_t i = 1; i <= max_n; ++i) {
        // string w = words[getrand(0, words.size() - 1)];
        string w = "aaaa";
        hashtab_add(hashtab, w, i);

        if (i % 10000 == 0){
            double time = measure_time(hashtab, w, hashtab_hash);
            cout << fixed << setprecision(10) << time << endl;
        }
    }
    return 0;
}
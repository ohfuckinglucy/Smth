#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include "hashtable.h"

using namespace std;


int main() {
    ifstream file("words.txt");
    if (!file.is_open()) {
        cerr << "Failed to open file." << endl;
        return 1;
    }

    HashTable hashtab;
    uint32_t table_size = 200000;

    hashtab_init(hashtab, table_size);

    vector<string> words;
    string word;
    while (file >> word) {
        words.push_back(word);
    }
    file.close();

    for (int i = 0; i < 200000; ++i) {
        hashtab_add(hashtab, words[i], i);
        
        if ((i + 1) % 10000 == 0) {
            string w = words[getrand(0, i)];
            double t = wtime();
            ListNode* node = hashtab_lookup(hashtab, w);
            t = wtime() - t;

            cout << setw(5) << i+1 << " "<< fixed << setprecision(10) << t << endl;
        }
    }

    return 0;
}
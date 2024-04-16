#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <sys/time.h>
#include <iomanip>
#include "bstree.h"

using namespace std;

int main() {
    ifstream file("words.txt");
    if (!file.is_open()) {
        cerr << "Failed to open file." << endl;
        return 1;
    }

    vector<string> words;
    string word;
    while (file >> word) {
        words.push_back(word);
    }
    file.close();

    Node* tree = nullptr;

    for (int i = 1; i <= 200000; ++i) {
        if(tree == nullptr) {
            tree = new Node(words[i - 1], i - 1);
        } else {
            tree->add(tree, words[i - 1], i - 1);
        }

        if (i % 10000 == 0) {
            string w = words[getRand(0, i - 1)];
            double t = wtime();
            Node* node = tree->LookUp(tree, w);
            t = wtime() - t;

            cout << setw(5) << i << " "<< fixed << setprecision(10) <<  t << endl;
        }
    }

    return 0;
}
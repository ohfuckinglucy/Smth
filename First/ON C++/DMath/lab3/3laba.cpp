#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <initializer_list>

using namespace std;

void printVector(const vector<int>& vec) {
    for (int i = 0; i < vec.size(); ++i) {
        cout << vec[i] << " ";
    }
    cout << endl;
}

int findK(const vector<int>& perm) {
    int k = perm.size() - 2;
    while (k >= 0 && perm[k] >= perm[k + 1]) {
        k--;
    }
    return k;
}

void swapNextLargest(vector<int>& perm, int k) {
    int n = perm.size();
    for (int i = n - 1; i > k; --i) {
        if (perm[i] > perm[k]) {
            swap(perm[i], perm[k]);
            break;
        }
    }
}

void reverseSuffix(vector<int>& perm, int k) {
    int n = perm.size();
    reverse(perm.begin() + k + 1, perm.end());
}

void generatePermutations(const vector<int>& elements, ofstream& outFile) {
    vector<int> perm = elements;
    int count = 1;
    int n = perm.size();

    sort(perm.begin(), perm.end());

    printVector(perm);
    outFile << "Permutation " << count++ << ": ";
    for (int i = 0; i < n; ++i) {
        outFile << perm[i] << " ";
    }
    outFile << endl;

    while (true) {
        int k = findK(perm);
        if (k == -1) {
            break;
        }

        swapNextLargest(perm, k);
        reverseSuffix(perm, k);

        printVector(perm);
        outFile << "Permutation " << count++ << ": ";
        for (int i = 0; i < n; ++i) {
            outFile << perm[i] << " ";
        }
        outFile << endl;
    }
}

int main() {
    vector<int> elements;
    for (int i = 0; i < 4; i ++){
        elements.push_back(1 + i);
    }

    ofstream outFile("permutations.txt");
    if (!outFile.is_open()) {
        cerr << "Unable to open the file" << endl;
        return 1;
    }

    generatePermutations(elements, outFile);

    outFile.close();

    cout << "Permutations generated successfully and saved to 'permutations.txt'" << endl;

    return 0;
}

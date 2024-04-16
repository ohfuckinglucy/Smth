#include <vector>
#include <iostream>

using namespace std;

#define SIZE 100

int wordToNumber(const std::string& word) {
    int result = 0;
    for (char c : word) {
        result = result * 100 + static_cast<int>(c);
    }
    return result % SIZE;
}

void sethisbitch(int a[], string word, int value){
    int hashword = wordToNumber(word);
    a[hashword] = value;
}

void showmebitch(int a[], string word){
    int hashword = wordToNumber(word);
    cout << a[hashword] << endl;
}

int main(){
    int a[SIZE];

    sethisbitch(a, "bitch", 6);

    showmebitch(a, "bitch");    
    
}
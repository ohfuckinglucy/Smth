#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include <ctime>

std::string generateWord() {
    static const char alphabet[] = "abcdefghijklmnopqrstuvwxyz";
    static std::mt19937 rng(std::time(nullptr));
    static std::uniform_int_distribution<int> dist(3, 10);

    int length = dist(rng);
    std::string word;
    for (int i = 0; i < length; ++i) {
        word += alphabet[dist(rng) % (sizeof(alphabet) - 1)];
    }
    return word;
}

void generateDocument(int numWords) {
    std::ofstream file("words.date");
    if (!file.is_open()) {
        std::cerr << "Failed to open file." << std::endl;
        return;
    }

    for (int i = 0; i < numWords; ++i) {
        file << generateWord() << " ";
    }

    file.close();
}

int main() {
    generateDocument(400000);
    std::cout << "File generated successfully." << std::endl;
    return 0;
}

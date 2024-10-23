#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include "header.h" // Включаем заголовочный файл с реализованными функциями

using namespace std;

int main() {
    rbtree *root = nullptr;

    // Вставляем 50000 элементов, отсортированных по возрастанию
    cout << "Вставка элементов по возрастанию..." << endl;
    for (int i = 1; i <= 50000; ++i) {
        char value[20];
        sprintf(value, "value%d", i);
        root = rbtree_add(root, i, value);
    }

    // Измеряем высоту дерева
    int height = tree_height(root);
    cout << "Высота дерева после вставки 50,000 элементов по возрастанию: " << height << endl;

    // Поиск нескольких ключей для демонстрации логарифмической зависимости
    cout << "Проверка поиска ключей..." << endl;
    int test_keys[] = {1, 10000, 25000, 40000, 50000};
    for (int key : test_keys) {
        rbtree *found = rbtree_lookup(root, key);
        if (found) {
            cout << "Ключ " << key << " найден, значение: " << found->value << endl;
        } else {
            cout << "Ключ " << key << " не найден" << endl;
        }
    }

    // Тестирование удаления
    cout << "Удаление ключей..." << endl;
    for (int i = 1; i <= 5000; ++i) {
        root = rbtree_delete(root, i); // Удаляем первые 5000 элементов
    }
    
    height = tree_height(root);
    cout << "Высота дерева после удаления 5000 элементов: " << height << endl;

    // Очистка памяти
    rbtree_free(root);

    return 0;
}

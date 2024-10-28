#include <iostream>
#include <cmath>
#include <limits>
#include <vector>
#include <string>

using namespace std;

struct FibNode {
    int key;
    string value;
    int degree;
    bool mark;
    FibNode* parent;
    FibNode* child;
    FibNode* left;
    FibNode* right;

    FibNode(int k, string val) : key(k), value(val), degree(0), mark(false),
                                  parent(nullptr), child(nullptr), left(this), right(this) {}
};

struct FibHeap {
    FibNode* min;
    int nnodes;

    FibHeap() : min(nullptr), nnodes(0) {}
};

// Прототипы
void fibheap_consolidate(FibHeap* heap);
void fibheap_link(FibHeap* heap, FibNode* y, FibNode* x);
void fibheap_cut(FibHeap* heap, FibNode* x, FibNode* y);
void fibheap_cascading_cut(FibHeap* heap, FibNode* y);
void fibheap_add_node_to_root_list(FibNode* node, FibHeap* heap);

// Добавление узла в список корней
void fibheap_add_node_to_root_list(FibNode* node, FibHeap* heap) {
    if (heap->min == nullptr) {
        heap->min = node;
    } else {
        // Добавляем узел в список корней
        node->left = heap->min->left;
        node->right = heap->min;
        heap->min->left->right = node;
        heap->min->left = node;
        // Обновляем минимальный элемент, если необходимо
        if (node->key < heap->min->key) {
            heap->min = node;
        }
    }
}

// Добавление узла в кучу (Insert)
FibHeap* fibheap_insert(FibHeap* heap, int key, string value) {
    FibNode* node = new FibNode(key, value);
    fibheap_add_node_to_root_list(node, heap);
    heap->nnodes++;
    return heap;
}

// Поиск минимального узла (Min)
FibNode* fibheap_min(FibHeap* heap) {
    return heap->min;
}

// Слияние двух списков корней
void fibheap_link_lists(FibNode* heap1, FibNode* heap2) {
    if (heap1 == nullptr || heap2 == nullptr) {
        return;
    }
    FibNode* left1 = heap1->left;
    FibNode* left2 = heap2->left;
    left1->right = heap2;
    heap2->left = left1;
    heap1->left = left2;
    left2->right = heap1;
}

// Слияние фибоначчиевых куч (Union)
FibHeap* fibheap_union(FibHeap* heap1, FibHeap* heap2) {
    FibHeap* heap = new FibHeap();
    heap->min = heap1->min;
    fibheap_link_lists(heap1->min, heap2->min);
    if (heap1->min == nullptr || (heap2->min != nullptr && heap2->min->key < heap->min->key)) {
        heap->min = heap2->min;
    }
    heap->nnodes = heap1->nnodes + heap2->nnodes;
    delete heap1;
    delete heap2;
    return heap;
}

// Удаление минимального узла (DeleteMin)
FibNode* fibheap_delete_min(FibHeap* heap) {
    FibNode* z = heap->min;
    if (z != nullptr) {
        // Перенос дочерних узлов z в список корней
        FibNode* x = z->child;
        if (x != nullptr) {
            do {
                FibNode* next = x->right;
                fibheap_add_node_to_root_list(x, heap);
                x->parent = nullptr;
                x = next;
            } while (x != z->child);
        }
        // Удаление z из списка корней
        if (z->right == z) {
            heap->min = nullptr;
        } else {
            z->left->right = z->right;
            z->right->left = z->left;
            heap->min = z->right; // Обновляем минимум
            fibheap_consolidate(heap);
        }
        heap->nnodes--;
    }
    return z;
}

// Уплотнение списка корней (Consolidate)
void fibheap_consolidate(FibHeap* heap) {
    int D = log2(heap->nnodes) + 1;
    vector<FibNode*> A(D, nullptr);

    // Цикл по всем узлам списка корней
    FibNode* w = heap->min;
    do {
        FibNode* x = w;
        int d = x->degree;
        while (A[d] != nullptr) {
            FibNode* y = A[d];
            if (x->key > y->key) {
                swap(x, y);
            }
            fibheap_link(heap, y, x);
            A[d] = nullptr;
            d++;
        }
        A[d] = x;
        w = w->right;
    } while (w != heap->min);

    // Поиск нового минимального узла
    heap->min = nullptr;
    for (FibNode* node : A) {
        if (node != nullptr) {
            if (heap->min == nullptr || node->key < heap->min->key) {
                heap->min = node;
            }
        }
    }
}

// Связывание узлов (Link)
void fibheap_link(FibHeap* heap, FibNode* y, FibNode* x) {
    // Удаление y из списка корней
    if (y->right == y) {
        y->left->right = y->right;
        y->right->left = y->left;
    } else {
        y->left->right = y->right;
        y->right->left = y->left;
    }
    y->parent = x;
    y->mark = false;
    if (x->child == nullptr) {
        x->child = y;
    } else {
        fibheap_add_node_to_root_list(y, heap);
    }
    x->degree++;
}

// Уменьшение ключа (DecreaseKey)
void fibheap_decrease_key(FibHeap* heap, FibNode* x, int newkey) {
    if (newkey > x->key) {
        return;
    }
    x->key = newkey;
    FibNode* y = x->parent;
    if (y != nullptr && x->key < y->key) {
        fibheap_cut(heap, x, y);
        fibheap_cascading_cut(heap, y);
    }
    if (x->key < heap->min->key) {
        heap->min = x;
    }
}

// Обрезка узла (Cut)
void fibheap_cut(FibHeap* heap, FibNode* x, FibNode* y) {
    // Удаление x из списка дочерних узлов y
    if (y->child == x) {
        if (x->right == x) {
            y->child = nullptr;
        } else {
            y->child = x->right;
        }
    }
    x->left->right = x->right;
    x->right->left = x->left;
    y->degree--;
    fibheap_add_node_to_root_list(x, heap);
    x->parent = nullptr;
    x->mark = false;
}

// Каскадная обрезка (CascadingCut)
void fibheap_cascading_cut(FibHeap* heap, FibNode* y) {
    FibNode* z = y->parent;
    if (z != nullptr) {
        if (!y->mark) {
            y->mark = true;
        } else {
            fibheap_cut(heap, y, z);
            fibheap_cascading_cut(heap, z);
        }
    }
}

// Удаление заданного узла (Delete)
void fibheap_delete(FibHeap* heap, FibNode* x) {
    fibheap_decrease_key(heap, x, numeric_limits<int>::min());
    fibheap_delete_min(heap);
}

int main() {
    // Создание фибоначчиевой кучи
    FibHeap* heap1 = new FibHeap();

    // Добавление узлов в первую кучу
    fibheap_insert(heap1, 10, "node10");
    fibheap_insert(heap1, 5, "node5");
    fibheap_insert(heap1, 20, "node20");

    std::cout << "Минимальный элемент в первой куче: " << fibheap_min(heap1)->key << " (" << fibheap_min(heap1)->value << ")" << std::endl;

    // Создание второй кучи и добавление узлов
    FibHeap* heap2 = new FibHeap();
    fibheap_insert(heap2, 15, "node15");
    fibheap_insert(heap2, 7, "node7");

    // Слияние двух куч
    FibHeap* heap = fibheap_union(heap1, heap2);
    std::cout << "Минимальный элемент после слияния: " << fibheap_min(heap)->key << " (" << fibheap_min(heap)->value << ")" << std::endl;

    // Уменьшение ключа одного из узлов
    FibNode* node20 = heap->min->right->right; // Находим узел со значением 20
    fibheap_decrease_key(heap, node20, 3);
    std::cout << "Минимальный элемент после уменьшения ключа: " << fibheap_min(heap)->key << " (" << fibheap_min(heap)->value << ")" << std::endl;

    // Удаление минимального элемента
    FibNode* minNode = fibheap_delete_min(heap);
    std::cout << "Удаленный минимальный элемент: " << minNode->key << " (" << minNode->value << ")" << std::endl;
    delete minNode;
    std::cout << "Новый минимальный элемент: " << fibheap_min(heap)->key << " (" << fibheap_min(heap)->value << ")" << std::endl;

    // Удаление заданного узла (например, узла с ключом 7)
    FibNode* node7 = heap->min->right; // Предположим, это узел с ключом 7
    fibheap_delete(heap, node7);
    std::cout << "Минимальный элемент после удаления узла с ключом 7: " << fibheap_min(heap)->key << " (" << fibheap_min(heap)->value << ")" << std::endl;

    // Освобождение памяти для оставшихся узлов и кучи
    delete heap;

    return 0;
}

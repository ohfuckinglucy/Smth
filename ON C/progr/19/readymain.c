#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BOOKS 100
#define MAX_STRING_LENGTH 100

// Структура для хранения информации о книге
typedef struct {
    char udc[MAX_STRING_LENGTH];
    char author[MAX_STRING_LENGTH];
    char title[MAX_STRING_LENGTH];
    int year;
    int quantity;
} Book;

// Глобальный массив книг
Book library[MAX_BOOKS];
int bookCount = 0;

// Функция для сравнения двух книг по году издания (для сортировки)
int compareBooks(const void* a, const void* b) {
    return ((Book*)a)->year - ((Book*)b)->year;
}

// Функция для начального формирования данных о книгах в библиотеке
void initializeLibrary() {
    // Пример начального заполнения данных
    strcpy(library[0].udc, "123.45");
    strcpy(library[0].author, "Иванов И.И.");
    strcpy(library[0].title, "Программирование на C");
    library[0].year = 2020;
    library[0].quantity = 5;

    strcpy(library[1].udc, "234.56");
    strcpy(library[1].author, "Петров П.П.");
    strcpy(library[1].title, "Структуры данных");
    library[1].year = 2019;
    library[1].quantity = 3;

    bookCount = 2;

    // Сортировка массива по годам издания
    qsort(library, bookCount, sizeof(Book), compareBooks);
}

// Функция для добавления новой книги в библиотеку
void addBook(const char* udc, const char* author, const char* title, int year, int quantity) {
    if (bookCount < MAX_BOOKS) {
        strcpy(library[bookCount].udc, udc);
        strcpy(library[bookCount].author, author);
        strcpy(library[bookCount].title, title);
        library[bookCount].year = year;
        library[bookCount].quantity = quantity;
        bookCount++;

        // Сортировка массива после добавления
        qsort(library, bookCount, sizeof(Book), compareBooks);

        printf("Книга успешно добавлена.\n");
    } else {
        printf("Ошибка: превышено максимальное количество книг.\n");
    }
}

// Функция для удаления книги из библиотеки
void removeBook(const char* title) {
    int i;
    for (i = 0; i < bookCount; i++) {
        if (strcmp(library[i].title, title) == 0) {
            // Удаляем книгу путем сдвига всех книг справа от нее на одну позицию влево
            for (int j = i; j < bookCount - 1; j++) {
                library[j] = library[j + 1];
            }
            bookCount--;
            printf("Книга успешно удалена.\n");
            return;
        }
    }
    printf("Ошибка: книга не найдена.\n");
}

// Функция для поиска книги по названию
void searchBook(const char* title) {
    int i;
    for (i = 0; i < bookCount; i++) {
        if (strcmp(library[i].title, title) == 0) {
            printf("Найдена книга:\n");
            printf("УДК: %s\n", library[i].udc);
            printf("Автор: %s\n", library[i].author);
            printf("Год издания: %d\n", library[i].year);
            printf("Количество экземпляров: %d\n", library[i].quantity);
            return;
        }
    }
    printf("Книга с таким названием не найдена.\n");
}

int main() {
    initializeLibrary();

    addBook("345.67", "Сидоров С.С.", "Алгоритмы и структуры данных", 2022, 10);
    removeBook("Программирование на C");
    searchBook("Структуры данных");

    return 0;
}

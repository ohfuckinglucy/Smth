#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 100
#define PHONE_LENGTH 20

// Структура для хранения данных абонента
typedef struct {
    char name[MAX_NAME_LENGTH];
    char phone[PHONE_LENGTH];
} Abonent;

// Функция для добавления абонента в файл
void addAbonent() {
    FILE *file = fopen("ABONENT.dat", "ab");
    if (file == NULL) {
        printf("Ошибка при открытии файла\n");
        exit(1);
    }

    Abonent abonent;
    printf("Введите ФИО абонента: ");
    fgets(abonent.name, MAX_NAME_LENGTH, stdin);
    abonent.name[strcspn(abonent.name, "\n")] = '\0'; // Удаление символа новой строки

    printf("Введите номер телефона: ");
    fgets(abonent.phone, PHONE_LENGTH, stdin);
    abonent.phone[strcspn(abonent.phone, "\n")] = '\0'; // Удаление символа новой строки

    fwrite(&abonent, sizeof(Abonent), 1, file);

    fclose(file);
    printf("Абонент успешно добавлен.\n");
}

// Функция для поиска абонента по имени
void findAbonent() {
    FILE *file = fopen("ABONENT.dat", "rb");
    if (file == NULL) {
        perror("Ошибка при открытии файла");
        exit(1);
    }

    char searchName[MAX_NAME_LENGTH];
    printf("Введите ФИО абонента: ");
    fgets(searchName, MAX_NAME_LENGTH, stdin);
    searchName[strcspn(searchName, "\n")] = '\0'; // Удаление символа новой строки

    Abonent temp;
    int found = 0;

    while (fread(&temp, sizeof(Abonent), 1, file)) {
        if (strcmp(temp.name, searchName) == 0) {
            printf("Номер телефона: %s\n", temp.phone);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Абонент не найден\n");
    }

    fclose(file);
}

int main() {
    int choice;

    do {
        printf("Выберите действие:\n");
        printf("1. Добавить абонента\n");
        printf("2. Найти абонента по ФИО\n");
        printf("3. Выйти\n");
        printf("Ваш выбор: ");
        scanf("%d", &choice);
        getchar(); // Чтение символа новой строки после ввода числа

        switch (choice) {
            case 1:
                addAbonent();
                break;
            case 2:
                findAbonent();
                break;
            case 3:
                printf("Выход из программы.\n");
                break;
            default:
                printf("Неверный выбор. Попробуйте снова.\n");
        }
    } while (choice != 3);

    return 0;
}
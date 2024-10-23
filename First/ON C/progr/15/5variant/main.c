#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LEN 50
#define FILE_NAME "Wedomost.dat"

typedef struct {
    char name[MAX_NAME_LEN];
    int group;
    int grades[3];
} Student;

void addStudent();
void findStudentsWithLowGrades();
void searchStudent();
void menu();

int main() {
    menu();
    return 0;
}

void addStudent() {
    FILE *file = fopen(FILE_NAME, "ab");
    if (file == NULL) {
        perror("Не удается открыть файл");
        exit(EXIT_FAILURE);
    }

    Student student;
    printf("Введите фамилию и инициалы студента: ");
    getchar(); // Чтобы поглотить символ новой строки, оставшийся после предыдущего ввода
    fgets(student.name, MAX_NAME_LEN, stdin);
    student.name[strcspn(student.name, "\n")] = 0; // Удалить символ новой строки, добавленный fgets
    printf("Введите номер группы: ");
    scanf("%d", &student.group);
    printf("Введите оценки по трем предметам: ");
    for (int i = 0; i < 3; i++) {
        scanf("%d", &student.grades[i]);
    }

    fwrite(&student, sizeof(Student), 1, file);
    fclose(file);
    printf("Студент успешно добавлен.\n");
}

void findStudentsWithLowGrades() {
    FILE *file = fopen(FILE_NAME, "rb");
    if (file == NULL) {
        perror("Не удается открыть файл");
        exit(EXIT_FAILURE);
    }

    Student student;
    int found = 0;
    while (fread(&student, sizeof(Student), 1, file)) {
        for (int i = 0; i < 3; i++) {
            if (student.grades[i] == 2) {
                printf("Студент %s из группы %d имеет оценку 2.\n", student.name, student.group);
                found = 1;
                break;
            }
        }
    }

    if (!found) {
        printf("Студентов с оценкой 2 не найдено.\n");
    }
    fclose(file);
}

void searchStudent() {
    FILE *file = fopen(FILE_NAME, "rb");
    if (file == NULL) {
        perror("Не удается открыть файл");
        exit(EXIT_FAILURE);
    }

    char searchName[MAX_NAME_LEN];
    printf("Введите фамилию и инициалы студента для поиска: ");
    getchar(); // Чтобы поглотить символ новой строки, оставшийся после предыдущего ввода
    fgets(searchName, MAX_NAME_LEN, stdin);
    searchName[strcspn(searchName, "\n")] = 0; // Удалить символ новой строки, добавленный fgets

    Student student;
    int found = 0;
    while (fread(&student, sizeof(Student), 1, file)) {
        if (strcmp(student.name, searchName) == 0) {
            printf("Студент найден: %s, Группа: %d, Оценки: %d, %d, %d\n", student.name, student.group, student.grades[0], student.grades[1], student.grades[2]);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Студент не найден.\n");
    }
    fclose(file);
}

void menu() {
    int choice;
    while (1) {
        printf("\nМеню:\n");
        printf("1. Добавить студента\n");
        printf("2. Найти студентов с оценкой 2\n");
        printf("3. Поиск студента\n");
        printf("4. Выход\n");
        printf("Введите ваш выбор: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                findStudentsWithLowGrades();
                break;
            case 3:
                searchStudent();
                break;
            case 4:
                exit(0);
                break;
            default:
                printf("Неверный выбор. Попробуйте еще раз.\n");
        }
    }
}

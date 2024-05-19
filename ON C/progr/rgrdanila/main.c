#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_SUBJECTS 4
#define MAX_NAME_LENGTH 50

// Определение структуры для хранения данных студента
typedef struct {
    char subject[MAX_NAME_LENGTH];
    int grade;
} Subject;

typedef struct Student {
    char lastName[MAX_NAME_LENGTH];
    char firstName[MAX_NAME_LENGTH];
    char middleName[MAX_NAME_LENGTH];
    Subject subjects[NUM_SUBJECTS];
    struct Student* next;
} Student;

// Функция для создания нового студента
Student* createStudent(char* lastName, char* firstName, char* middleName, Subject* subjects) {
    Student* newStudent = (Student*)malloc(sizeof(Student));
    strcpy(newStudent->lastName, lastName);
    strcpy(newStudent->firstName, firstName);
    strcpy(newStudent->middleName, middleName);
    memcpy(newStudent->subjects, subjects, NUM_SUBJECTS * sizeof(Subject));
    newStudent->next = NULL;
    return newStudent;
}

// Функция для добавления нового студента в начало списка
void addStudent(Student** head, Student* newStudent) {
    newStudent->next = *head;
    *head = newStudent;
}

// Функция для удаления студентов с неудовлетворительными оценками
void removeFailingStudents(Student** head) {
    Student* current = *head;
    Student* prev = NULL;

    while (current != NULL) {
        int failCount = 0;
        for (int i = 0; i < NUM_SUBJECTS; i++) {
            if (current->subjects[i].grade < 4) {
                failCount++;
            }
        }

        if (failCount >= 3) {
            if (prev == NULL) {
                *head = current->next;
            } else {
                prev->next = current->next;
            }
            Student* temp = current;
            current = current->next;
            free(temp);
        } else {
            prev = current;
            current = current->next;
        }
    }
}

// Функция для поиска студента по фамилии
Student* findStudentByLastName(Student* head, char* lastName) {
    Student* current = head;
    while (current != NULL) {
        if (strcmp(current->lastName, lastName) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

// Функция для изменения оценок студента
void updateGrades(Student* student, Subject* newSubjects) {
    if (student != NULL) {
        memcpy(student->subjects, newSubjects, NUM_SUBJECTS * sizeof(Subject));
    }
}

// Функция для печати списка студентов
void printStudents(Student* head) {
    Student* current = head;
    while (current != NULL) {
        printf("ФИО: %s %s %s\n", current->lastName, current->firstName, current->middleName);
        for (int i = 0; i < NUM_SUBJECTS; i++) {
            printf("  Предмет: %s, Оценка: %d\n", current->subjects[i].subject, current->subjects[i].grade);
        }
        printf("\n");
        current = current->next;
    }
}

int main() {
    Student* students = NULL;

    // Создание нескольких студентов
    Subject subjects1[NUM_SUBJECTS] = {{"Математика", 5}, {"Физика", 4}, {"Химия", 3}, {"Биология", 2}};
    Student* student1 = createStudent("Иванов", "Иван", "Иванович", subjects1);
    addStudent(&students, student1);

    Subject subjects2[NUM_SUBJECTS] = {{"Математика", 3}, {"Физика", 2}, {"Химия", 4}, {"Биология", 5}};
    Student* student2 = createStudent("Петров", "Петр", "Петрович", subjects2);
    addStudent(&students, student2);

    // Печать списка студентов
    printf("Список студентов:\n");
    printStudents(students);

    // Удаление студентов с неудовлетворительными оценками
    removeFailingStudents(&students);
    printf("Список студентов после удаления неудовлетворительных:\n");
    printStudents(students);

    // Поиск студента по фамилии и изменение его оценок
    char lastNameToFind[MAX_NAME_LENGTH] = "Петров";
    Student* foundStudent = findStudentByLastName(students, lastNameToFind);
    if (foundStudent) {
        Subject newSubjects[NUM_SUBJECTS] = {{"Математика", 5}, {"Физика", 5}, {"Химия", 5}, {"Биология", 5}};
        updateGrades(foundStudent, newSubjects);
    }

    // Печать обновленного списка студентов
    printf("Список студентов после изменения оценок:\n");
    printStudents(students);

    return 0;
}

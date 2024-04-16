#include <stdio.h>

#define WINTER 0
#define SPRING 1
#define SUMMER 2
#define AUTUMN 3

#define SECONDS_IN_MINUTE 60
#define MINUTES_IN_HOUR 60
#define HOURS_IN_DAY 24

int daysInMonth(int month, int year) {
    switch (month) {
        case 2:
            if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
                return 29;
            else
                return 28;
        case 4:
        case 6:
        case 9:
        case 11:
            return 30;
        default:
            return 31;
    }
}

int daysFromStartOfYear(int day, int month, int year) {
    int days = day;
    for (int i = 1; i < month; ++i) {
        days += daysInMonth(i, year);
    }
    return days;
}

long long int secondsBetweenDates(int day1, int month1, int year1, int day2, int month2, int year2) {
    long long int seconds = 0;
    for (int y = year1; y < year2; ++y) {
        if ((y % 4 == 0 && y % 100 != 0) || y % 400 == 0)
            seconds += 366 * 24 * 60 * 60;
        else
            seconds += 365 * 24 * 60 * 60;
    }
    seconds += (daysFromStartOfYear(day2, month2, year2) - daysFromStartOfYear(day1, month1, year1)) * 24 * 60 * 60;

    seconds += (day2 - day1) * 24 * 60 * 60;
    return seconds;
}

int getSeason(int month) {
    switch (month) {
        case 1:
        case 2:
        case 12:
            return WINTER;
        case 3:
        case 4:
        case 5:
            return SPRING;
        case 6:
        case 7:
        case 8:
            return SUMMER;
        case 9:
        case 10:
        case 11:
            return AUTUMN;
        default:
            return -1;
    }
}

int main() {
    int day1, month1, year1;
    int day2, month2, year2;
    int season1, season2;

    printf("Введите первую дату (день месяц год): ");
    scanf("%d %d %d", &day1, &month1, &year1);
    printf("Введите вторую дату (день месяц год): ");
    scanf("%d %d %d", &day2, &month2, &year2);

    long long int seconds = secondsBetweenDates(day1, month1, year1, day2, month2, year2);
    printf("Разница между датами %lld секунд\n", seconds);

    season1 = getSeason(month1);
    season2 = getSeason(month2);

    printf("Первая дата: ");
    switch (season1) {
        case WINTER:
            printf("\033[0;33mЗима\033[0m");
            break;
        case SPRING:
            printf("\033[0;32mВесна\033[0m");
            break;
        case SUMMER:
            printf("\033[0;36mЛето\033[0m");
            break;
        case AUTUMN:
            printf("\033[0;31mОсень\033[0m");
            break;
        default:
            printf("Ошибка: некорректный месяц");
    }
    printf("\n");

    printf("Вторая дата: ");
    switch (season2) {
        case WINTER:
            printf("\033[0;33mЗима\033[0m");
            break;
        case SPRING:
            printf("\033[0;32mВесна\033[0m");
            break;
        case SUMMER:
            printf("\033[0;36mЛето\033[0m");
            break;
        case AUTUMN:
            printf("\033[0;31mОсень\033[0m");
            break;
        default:
            printf("Ошибка: некорректный месяц");
    }
    printf("\n");

    return 0;
}

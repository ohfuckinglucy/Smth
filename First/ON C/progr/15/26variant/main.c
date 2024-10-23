#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 100

typedef struct {
    char start_point[MAX_LENGTH];
    char end_point[MAX_LENGTH];
    int route_number;
} RouteInfo;

void writeRouteInfoToFile(FILE *file, RouteInfo route) {
    fprintf(file, "%s %s %d\n", route.start_point, route.end_point, route.route_number);
}

RouteInfo readRouteInfoFromFile(FILE *file) {
    RouteInfo route;
    fscanf(file, "%s %s %d", route.start_point, route.end_point, &route.route_number);
    return route;
}

int main() {
    FILE *file;
    RouteInfo route;
    int search_route_number;
    int found = 0;

    file = fopen("Spravka.dat", "w");
    if (file == NULL) {
        printf("Ошибка при создании файла.\n");
        return 1;
    }

    printf("Введите информацию о маршрутах (название начального пункта, название конечного пункта, номер маршрута):\n");
    while (1) {
        printf("Введите название начального пункта (или 'end' для завершения ввода): ");
        scanf("%s", route.start_point);
        if (strcmp(route.start_point, "end") == 0) {
            break;
        }
        printf("Введите название конечного пункта: ");
        scanf("%s", route.end_point);
        printf("Введите номер маршрута: ");
        scanf("%d", &route.route_number);

        writeRouteInfoToFile(file, route);
    }

    fclose(file);

    file = fopen("Spravka.dat", "r");
    if (file == NULL) {
        printf("Ошибка при открытии файла.\n");
        return 1;
    }

    printf("\nВведите номер маршрута для поиска: ");
    scanf("%d", &search_route_number);

    printf("\nРезультаты поиска:\n");
    while (!feof(file)) {
        RouteInfo current_route = readRouteInfoFromFile(file);
        if (current_route.route_number == search_route_number) {
            printf("Найден маршрут: %s - %s, номер маршрута: %d\n", current_route.start_point, current_route.end_point, current_route.route_number);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Маршрут с номером %d не найден.\n", search_route_number);
    }

    fclose(file);

    return 0;
}

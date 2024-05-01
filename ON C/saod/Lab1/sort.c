#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Bubble Sort
void bubbleSort(uint32_t* array, int size)
{
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (array[j] > array[j + 1]) {
                uint32_t temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }
}

// Merge Sort
void merge(uint32_t* array, int left, int middle, int right)
{
    int i, j, k;
    int n1 = middle - left + 1;
    int n2 = right - middle;

    uint32_t L[n1], R[n2];

    for (i = 0; i < n1; i++)
        L[i] = array[left + i];
    for (j = 0; j < n2; j++)
        R[j] = array[middle + 1 + j];

    i = 0;
    j = 0;
    k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            array[k] = L[i];
            i++;
        } else {
            array[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        array[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        array[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(uint32_t* array, int left, int right)
{
    if (left < right) {
        int middle = left + (right - left) / 2;
        mergeSort(array, left, middle);
        mergeSort(array, middle + 1, right);
        merge(array, left, middle, right);
    }
}

// Counting Sort
void countingSort(uint32_t* array, int size)
{
    int max = 100000; // Максимальное значение в массиве
    uint32_t* count = (uint32_t*)calloc(max, sizeof(uint32_t));
    uint32_t* sortedArray = (uint32_t*)malloc(size * sizeof(uint32_t));

    for (int i = 0; i < size; i++) {
        count[array[i]]++;
    }

    for (int i = 1; i < max; i++) {
        count[i] += count[i - 1];
    }

    for (int i = size - 1; i >= 0; i--) {
        sortedArray[count[array[i]] - 1] = array[i];
        count[array[i]]--;
    }

    for (int i = 0; i < size; i++) {
        array[i] = sortedArray[i];
    }

    free(count);
    free(sortedArray);
}

// Генерация случайного массива
void generateRandomArray(uint32_t* array, int size)
{
    for (int i = 0; i < size; i++) {
        array[i] = rand() % 100001; // случайное число от 0 до 100000
    }
}

// Измерение времени выполнения для сортировки
double measureSortingTime(
        void (*sortFunction)(uint32_t*, int), uint32_t* array, int size)
{
    clock_t start, end;
    start = clock();
    sortFunction(array, size);
    end = clock();
    return ((double)(end - start)) / CLOCKS_PER_SEC;
}

int main()
{
    int sizes[] = {
            50000,  100000, 150000, 200000, 250000, 300000, 350000,
            400000, 450000, 500000, 550000, 600000, 650000, 700000,
            750000, 800000, 850000, 900000, 950000, 1000000}; // разные размеры
                                                              // массивов для
                                                              // измерения
                                                              // времени
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);

    printf("Size\tBubble Sort\tMerge Sort\tCounting Sort\n");
    for (int i = 0; i < num_sizes; i++) {
        int size = sizes[i];
        uint32_t* array = (uint32_t*)malloc(size * sizeof(uint32_t));

        generateRandomArray(array, size);

        double bubbleTime = measureSortingTime(bubbleSort, array, size);
        double mergeTime = measureSortingTime(mergeSort, array, size);
        double countingTime = measureSortingTime(countingSort, array, size);

        printf("%d\t%.6f\t%.6f\t%.6f\n",
               size,
               bubbleTime,
               mergeTime,
               countingTime);

        free(array);
    }

    return 0;
}

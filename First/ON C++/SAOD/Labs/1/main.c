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

// Heap Sort
void heapify(uint32_t* array, int n, int i)
{
    int largest = i; //
    int left = 2 * i + 1;
    int right = 2 * i + 2; 

    if (left < n && array[left] > array[largest]) {
        largest = left;
    }

    if (right < n && array[right] > array[largest]) {
        largest = right;
    }

    if (largest != i) {

        uint32_t temp = array[i];
        array[i] = array[largest];
        array[largest] = temp;

        heapify(array, n, largest);
    }
}

// Сортировка кучей
void heapSort(uint32_t* array, int size){
    for (int i = size / 2 - 1; i >= 0; i--) {
        heapify(array, size, i);
    }

    for (int i = size - 1; i >= 0; i--) {
        uint32_t temp = array[0];
        array[0] = array[i];
        array[i] = temp;

        heapify(array, i, 0);
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

    printf("Size\tHeap Sort\tCounting Sort\tBubble Sort\n");
    for (int i = 0; i < num_sizes; i++) {
        int size = sizes[i];
        uint32_t* array = (uint32_t*)malloc(size * sizeof(uint32_t));

        generateRandomArray(array, size);

        double bubbleTime = measureSortingTime(bubbleSort, array, size);
        double heapTime = measureSortingTime(heapSort, array, size);
        double countingTime = measureSortingTime(countingSort, array, size);

        printf("%d\t%.6f\t%.6f\t%.6f\n",
               size,
               heapTime,
               countingTime,
               bubbleTime);

        free(array);
    }

    return 0;
}

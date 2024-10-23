extern int comparisonsShell, swapsShell;
extern int comparisonsInsertion, swapsInsertion;
extern int comparisonsBubble, swapsBubble;
extern int comparisonsCounting, swapsCounting;

void BubbleSort(int a[], int n, int *comparisons, int *swaps);
void insertionSort(int arr[], int n, int *comparisons, int *swaps);
void ShellSort(int a[], int n, int *comparisons, int *swaps);
void CountingSort(int arr[], int n, int *comparisons, int *swaps);
void swap(int *a, int *b);
int TypeOfCompletion(int choise, int n, int arr[], int arr2[], int arr3[], int arr4[]);
void showmas(int arr[], int n);
void generateDecreasingArray(int arr[], int n);
void generateRandomArray(int arr[], int n);
void generateIncreasingArray(int arr[], int n);
int ChooseSort(int arr[], int n, int choose);
/*
LIST OF COMMON SORTING AND COUNTING ALGORITHMS 

HEADER FILE

CREATED BY DANIEL MCCORMACK - JULY 2024
*/
void shuffle(int A[], int n);

void insertionSort(int A[], int n);

void mergeFunction(int A[], int p, int q, int r);

void mergeSort(int A[], int p, int r);

void bubbleSort(int A[], int n);

int heapParent(int i);

int heapLeft(int i);

int heapRight(int i);

void maxHeapify(int A[], int n, int i);

void buildMaxHeap(int A[], int n);

void heapSort(int A[], int n);

int partition(int A[], int p, int r);

void quickSort(int A[], int p, int r);

void shellSort(int A[], int n);

void countingSort(int A[], int n, int k);

int getMaximum(int A[], int n);

void radixCountingSort(int A[], int n, int digit);

void radixSort(int A[], int n);

void bogoSort(int A[], int originalA[], int n);

/*
LIST OF COMMON SORTING AND COUNTING ALGORITHMS 

IMPLEMENTATION FILE

CREATED BY DANIEL MCCORMACK - JULY 2024
*/
#include <stdlib.h>
#include <time.h>

void shuffle(int A[], int n)   //Fisher-Yates Shuffle 
{
    srand(time(NULL));

    int j, tempVar;
    for(int i = (n - 1); i >= 1; i--)
    {
        j = rand() % (i + 1);       //good use of the modulo op here, limits how high index num can go
        
        tempVar = A[j];
        A[j] = A[i];
        A[i] = tempVar;
    }
}

void insertionSort(int A[], int n)
{
    for(int i = 1; i < n; i++)
    {
        int tempHoldVar = A[i];
        int j = i - 1;

        while(j >= 0 && A[j] > tempHoldVar)
        {
            A[j + 1] = A[j];
            j--;
        }

        A[j + 1] = tempHoldVar;
    }
}

void mergeFunction(int A[], int p, int q, int r)
{        // Used in mergeSort
    int lengthOfLeft = q - p + 1;
    int lengthOfRight = r - q; 

    int leftArray[lengthOfLeft];
    int rightArray[lengthOfRight];

    for(int i = 0; i < lengthOfLeft; i++)
    {
        leftArray[i] = A[p + i];
    }

    for(int j = 0; j < lengthOfRight; j++)
    {
        rightArray[j] = A[q + j + 1];
    }

    int smallestLeft = 0;
    int smallestRight = 0;
    int fillLocation = p;

    while(smallestLeft < lengthOfLeft && smallestRight < lengthOfRight)
    {
        if(leftArray[smallestLeft] <= rightArray[smallestRight])
        {
            A[fillLocation] = leftArray[smallestLeft];
            smallestLeft++;
        }
        else 
        {
            A[fillLocation] = rightArray[smallestRight];
            smallestRight++;
        }

        fillLocation++;
    }

    while(smallestLeft < lengthOfLeft)
    {
        A[fillLocation] = leftArray[smallestLeft];
        smallestLeft++;
        fillLocation++;
    }

    while(smallestRight < lengthOfRight)
    {
        A[fillLocation] = rightArray[smallestRight];
        smallestRight++;
        fillLocation++;
    }
}

void mergeSort(int A[], int p, int r)
{
    if(p >= r){return;}

    int q = ((p + r ) / 2);

    mergeSort(A, p, q);
    mergeSort(A, q + 1, r);
    mergeFunction(A, p, q, r);
}

void bubbleSort(int A[], int n)
{
    int tempVar;
    for(int i = 0; i < n - 1; i++)
    {
        for(int j = n - 1; j > i; j--)
        {
            if(A[j] < A[j - 1])
            {
                tempVar = A[j];
                A[j] = A[j - 1];
                A[j - 1] = tempVar;
            }
        }
    }
}

int heapParent(int i){return i/2;}

int heapLeft(int i){return 2*i;}

int heapRight(int i){return 2*i + 1;}

void maxHeapify(int A[], int n, int i)
{
    int l = heapLeft(i);
    int r = heapRight(i);

    int largest, tempVar;
    

    if(l < n && A[l] > A[i])
    {
        largest = l;
    } 
    else
    {
        largest = i;
    }

    if(r < n && A[r] > A[largest])
    {
        largest = r; 
    }

    if(largest != i)
    {
        tempVar = A[largest];
        A[largest] = A[i];
        A[i] = tempVar;

        maxHeapify(A, n, largest);
    }
}

void buildMaxHeap(int A[], int n)
{
    for(int i = n / 2 - 1; i >= 0; i--)
    {
        maxHeapify(A, n, i);
    }
}

void heapSort(int A[], int n)
{   
    int tempVar;

    buildMaxHeap(A, n);

    for(int i = n - 1; i >= 0; i--)
    {
        tempVar = A[i];
        A[i] = A[0];
        A[0] = tempVar;

        maxHeapify(A, i, 0);
    }
}

int partition(int A[], int p, int r)
{
    int x = A[r];
    int i = p - 1;
    int tempVar;

    for(int j = p; j < r; j++)
    {
        if(A[j] <= x)
        {
            i++;

            tempVar = A[i];
            A[i] = A[j];
            A[j] = tempVar;
        }
    }

    tempVar = A[i + 1];
    A[i + 1] = A[r];
    A[r] = tempVar; 

    return i + 1;
}

void quickSort(int A[], int p, int r)
{
    if(p < r)
    {
        int q = partition(A, p, r);
        quickSort(A, p, q - 1);
        quickSort(A, q + 1, r);
    }
}

void shellSort(int A[], int n) 
{
  int gap, i, j, tempVar;

  for (int gap = n / 2; gap > 0; gap /= 2) 
  {
    for (int i = gap; i < n; i++) 
    {
      tempVar = A[i];

      for (j = i; j >= gap && A[j - gap] > tempVar; j -= gap) 
      {
        A[j] = A[j - gap];
      }

      A[j] = tempVar;
    }
  }
}

void copyArray(int A[], int B[], int n)
{
    for(int i = 0; i < n; i++)
    {
        B[i] = A[i];
    }
}

void countingSort(int A[], int n, int k)
{
    int B[n];
    int C[k + 1];

    copyArray(A, B, n);

    for(int i = 0; i <= k; i++)
    {
        C[i] = 0;
    }

    for(int j = 0; j < n; j++)
    {
        C[B[j]] = C[B[j]] + 1;
    }

    for(int l = 1; l <= k; l++)
    {
        C[l] = C[l] + C[l - 1];
    }

    for(int m = n - 1; m >= 0; m--)
    {
        A[C[B[m]] - 1] = B[m];
        C[B[m]] = C[B[m]] - 1;
    }
}

int getMaximum(int A[], int n)
{
    int max = A[0];

    for(int i = 1; i < n; i++)
    {
        if(A[i] > max)
        {
            max = A[i];
        }
    }

    return max;
}

void radixCountingSort(int A[], int n, int digit)
{
    int B[n];
    int C[10] = { 0 };

    for(int j = 0; j < n; j++)
    {
        C[(A[j] / digit) % 10] = C[(A[j] / digit) % 10] + 1;
    }

    for(int l = 1; l < 10; l++)
    {
        C[l] = C[l] + C[l - 1];
    }

    for(int m = n - 1; m >= 0; m--)
    {
        B[C[(A[m] / digit) % 10] - 1]= A[m];
        C[(A[m] / digit) % 10] = C[(A[m] / digit) % 10] - 1;
    }

    for(int i = 0; i < n; i++)
    {
        A[i] = B[i];
    }
}

void radixSort(int A[], int n)
{
    int radixMax = getMaximum(A, n);

    for(int i = 1; radixMax / i > 0; i *= 10)
    {
        radixCountingSort(A, n, i);
    }
}

void bogoSort(int A[], int originalA[], int n)
{
    while(A != originalA)
    {
        shuffle(A, n);
    }
}

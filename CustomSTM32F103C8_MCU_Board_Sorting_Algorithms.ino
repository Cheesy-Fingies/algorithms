#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <stdlib.h>
#include <time.h>

//Analog-to-Digital Converter(ADC) Pins
#define ADC_CHANNEL_1 PA0  //LEFT CHANNEL
#define ADC_CHANNEL_2 PA2  //RIGHT CHANNEL
#define ADC_RESOLUTION 12  //n-bit ADC, based upon hardware; The bluepill has a 12-bit ADC
#define VCC_VOLTAGE 3.3   // Bluepill is set for 3.30V logic level; Change as necessary per each alternative devices necessities

//Front Buttons Declarations
#define LEFT_BUTTON PB7
#define RIGHT_BUTTON PA1

//DIP Switch Declarations 
#define DIP_SWITCH_1 PB6
#define DIP_SWITCH_2 PB5
#define DIP_SWITCH_3 PB4
#define DIP_SWITCH_4 PB3

//GPIO Pinout
#define GPIO_PIN_1 PB15   //  TIMER1 | CHANNEL3N  | DIGITAL PIN
#define GPIO_PIN_2 PA8    //  TIMER1 | CHANNEL1   | USART1 - CK1  | MICROCONTROLLER CLOCK OUTPUT(MCO)
#define GPIO_PIN_3 PA9    //  TIMER1 | CHANNEL2   | USART1 - TX1
#define GPIO_PIN_4 PA10   //  TIMER1 | CHANNEL3   | USART1 - RX1
#define GPIO_PIN_5 PA11   //  TIMER1 | CHANNEL4   | USART1 - CTS1  | CANRX  | USB-  
#define GPIO_PIN_6 PA12   //  TIMER1 EXTERNAL TRIGGER | USART 1 - RTS1  | CANTX | USB+
#define GPIO_PIN_7 PA15   //  DIGITAL PIN | RED BUILTIN POWER LED PIN

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for SSD1306 display connected using software SPI (default case). Do not change the declarations!
#define MOSI_PIN   PA7
#define CLK_PIN    PA5
#define DC_PIN     PA6
#define CS_PIN    PB0
#define RST_PIN  PA4                                                    

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT,
  MOSI_PIN, CLK_PIN, DC_PIN, RST_PIN, CS_PIN);

//Cases for DIP switch, switch cases
#define INSERTION_SORT 0
#define MERGE_SORT 1
#define BUBBLE_SORT 2
#define HEAP_SORT 3
#define QUICK_SORT 4
#define SHELL_SORT 5
#define COUNTING_SORT 6
#define RADIX_SORT 7
#define BOGO_SORT 15

//--------------------ARRAY INFORMATION-------------------------------------------------  //Change size of array to suit needs. sortingArray is for actual shuffling,
int sortingArray[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19,  //STATIC_ARRAY is to maintain an image of the original array at all times.
    20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40,   //Make sure both arrays are the same size and same order when in the sorted form!!!
    41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 
    61, 62, 63, 64};

static int STATIC_ARRAY[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 
  20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 
  41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 
  61, 62, 63, 64};

#define ARRAY_SIZE  *(&sortingArray + 1) - sortingArray
//--------------------------------------------------------------------------------------

//--------------------PRINTING AND UTILITY FUNCTIONS------------------------------------
void swapElements(int A[], int m, int n)
{
  int storage;

  storage = A[m];
  A[m] = A[n];
  A[n] = storage;
}

void copyArray(int A[], int B[], int n)
{
    for(int i = 0; i < n; i++)
    {
        B[i] = A[i];
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

void writeToScreen(char C[])
{
  display.setCursor(0, 0);     // Start at top-left corner
  display.println(C);
  display.display();
}

void drawToScreen(int A[], int arraySize)
{
  for(int i = 0; i < arraySize; i++)
  {
    display.drawLine(2*i, SCREEN_HEIGHT - 1, 2*i, 0, SSD1306_BLACK);    //Draw black line to cover previous write, then draw new data
    display.drawLine(2*i + 1, SCREEN_HEIGHT - 1, 2*i + 1, 0, SSD1306_BLACK);
    display.drawLine(2*i, SCREEN_HEIGHT - 1, 2*i, arraySize - A[i], SSD1306_WHITE);    
    display.drawLine(2*i + 1, SCREEN_HEIGHT - 1, 2*i + 1, arraySize - A[i], SSD1306_WHITE);
    display.display();
    delayMicroseconds(1);
  }
  delayMicroseconds(1);
}

int algorithmCode(void)
{
  int fourBitDipInput;
  bitWrite(fourBitDipInput, 0, digitalRead(DIP_SWITCH_4));
  bitWrite(fourBitDipInput, 1, digitalRead(DIP_SWITCH_3));
  bitWrite(fourBitDipInput, 2, digitalRead(DIP_SWITCH_2));
  bitWrite(fourBitDipInput, 3, digitalRead(DIP_SWITCH_1));
  return fourBitDipInput; 
}
//--------------------------------------------------------------------------------------

//----------------------ALGORITHMS------------------------------------------------------
//---FISHER-YATES SHUFFLE------
void shuffle(int A[], int n)  
{
    srand(time(NULL));

    int j, tempVar;
    for(int i = (n - 1); i >= 1; i--)
    {
        j = rand() % (i + 1);       //good use of the modulo op here, limits how high index num can go
        
        swapElements(A, i, j);
    }
}
//-----------------------------

//---INSERTION SORT------------
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
          drawToScreen(sortingArray, ARRAY_SIZE);
        }

        A[j + 1] = tempHoldVar;
        drawToScreen(sortingArray, ARRAY_SIZE);
    }
}
//-----------------------------

//---MERGE SORT----------------
void mergeFunction(int A[], int p, int q, int r)
{        // Used in mergeSort
    int lengthOfLeft = q - p + 1;
    int lengthOfRight = r - q; 
    int arraySize = r - p + 1;

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

  drawToScreen(sortingArray, ARRAY_SIZE);
}

void mergeSort(int A[], int p, int r)
{
    if(p >= r){return;}

    int q = ((p + r ) / 2);

    mergeSort(A, p, q);
    mergeSort(A, q + 1, r);
    mergeFunction(A, p, q, r);
}
//-----------------------------

//---BUBBLE SORT---------------
void bubbleSort(int A[], int n)
{
    int tempVar;
    for(int i = 0; i < n - 1; i++)
    {
        for(int j = n - 1; j > i; j--)
        {
            if(A[j] < A[j - 1])
            {
              swapElements(A, j, j - 1);
              drawToScreen(sortingArray, ARRAY_SIZE);
            }
        }
    }
}
//-----------------------------

//---HEAP SORT-----------------
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
        swapElements(A, i, largest);

        drawToScreen(sortingArray, ARRAY_SIZE);

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
    buildMaxHeap(A, n);

    for(int i = n - 1; i >= 0; i--)
    {
        swapElements(A, 0, i);

        drawToScreen(sortingArray, ARRAY_SIZE);

        maxHeapify(A, i, 0);
    }
}
//-----------------------------

//---QUICK SORT----------------
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

            swapElements(A, i, j);

            drawToScreen(sortingArray, ARRAY_SIZE);
        }
    }

    swapElements(A, i + 1, r);

    drawToScreen(sortingArray, ARRAY_SIZE);

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
//-----------------------------

//---SHELL SORT----------------
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
        drawToScreen(sortingArray, ARRAY_SIZE);
      }

      A[j] = tempVar;
      drawToScreen(sortingArray, ARRAY_SIZE);
    }
  }
}
//-----------------------------

//---COUNTING SORT-------------
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
        drawToScreen(sortingArray, ARRAY_SIZE);
        C[B[m]] = C[B[m]] - 1;
    }
}
//-----------------------------

//---RADIX SORT----------------
void radixCountingSort(int A[], int n, int digit)
{
    int B[n];
    int C[10] = { 0 };

    copyArray(A, B, n);

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
        drawToScreen(B, ARRAY_SIZE);
        C[(A[m] / digit) % 10] = C[(A[m] / digit) % 10] - 1;
    }

    for(int i = 0; i < n; i++)
    {
        A[i] = B[i];
    }

    drawToScreen(sortingArray, ARRAY_SIZE);
}

void radixSort(int A[], int n)
{
    int radixMax = getMaximum(A, n);

    for(int i = 1; radixMax / i > 0; i *= 10)
    {
        radixCountingSort(A, n, i);
    }
}
//-----------------------------

//---BOGO SORT--(LOL!!)--------
void bogoSort(int A[], int originalA[], int n)
{
  while(A != originalA)
    {
        shuffle(A, n);
        drawToScreen(sortingArray, ARRAY_SIZE);
        delayMicroseconds(1);
    }
}
//-----------------------------
//--------------------------------------------------------------------------------------

//---MAIN-------------------------------------------------------------------------------
void setup() 
{
  // Initialize serial communication
  Serial.begin(115200);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  //Switch from a default 10-bit ADC to the built-in 12-bit ADC
  analogReadResolution(12);
  
  //Initialize Front Buttons and Switches
  pinMode(LEFT_BUTTON, INPUT_PULLDOWN);
  pinMode(RIGHT_BUTTON, INPUT_PULLDOWN);
  pinMode(DIP_SWITCH_1, INPUT_PULLDOWN);
  pinMode(DIP_SWITCH_2, INPUT_PULLDOWN);
  pinMode(DIP_SWITCH_3, INPUT_PULLDOWN);
  pinMode(DIP_SWITCH_4, INPUT_PULLDOWN);

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  display.display();
  delay(2000);
  // Clear the buffer
  display.clearDisplay();
  digitalWrite(LED_BUILTIN, HIGH);

  display.setTextSize(1);             // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE);        // Draw white text
}

void loop() 
{
    int shuffleButton = 0;      //Control variables for various menus and button commands
    int lastShuffleButton = 0;
    int sortButton = 0;
    int lastSortButton = 0;
    int dipState = 0;
    int lastDipState = 0;
    bool isShuffled = false; 
    drawToScreen(sortingArray, ARRAY_SIZE);

    while(1)
    {
      dipState = algorithmCode();     //Checks dip switch state, clears OLED buffer if the chosen algorithm changes 
      if(lastDipState != dipState)
      {
        display.clearDisplay();
        drawToScreen(sortingArray, ARRAY_SIZE);
      }
      lastDipState = dipState; 

      shuffleButton = digitalRead(LEFT_BUTTON);

      if(shuffleButton != lastShuffleButton)
      {
        if(shuffleButton == HIGH)
        {
          shuffle(sortingArray, ARRAY_SIZE);
          display.clearDisplay();
          drawToScreen(sortingArray, ARRAY_SIZE);
          isShuffled = true;
        }
        lastShuffleButton = shuffleButton;
      }

      switch(dipState)
      {
        case INSERTION_SORT:
          if(isShuffled == false){writeToScreen("INSERTION SORT");}   // Control statement to prevent text overflow and incorrect printing 

          sortButton = digitalRead(RIGHT_BUTTON);
          
          if(sortButton != lastSortButton)
          {
            if(sortButton == HIGH)
            {
              if(isShuffled == true)
              {
                insertionSort(sortingArray, ARRAY_SIZE);
                isShuffled = false;
              }
            }
            lastSortButton = sortButton;
          }
          else
          {
            continue;
          }
        break;
        case MERGE_SORT:
          if(isShuffled == false){writeToScreen("MERGE SORT");}

          sortButton = digitalRead(RIGHT_BUTTON);
          
          if(sortButton != lastSortButton)
          {
            if(sortButton == HIGH)
            {
              if(isShuffled == true)
              {
                mergeSort(sortingArray, 0, ARRAY_SIZE - 1);
                isShuffled = false;
              }
            }
            lastSortButton = sortButton;
          }
          else
          {
            continue;
          }
        break;
        case BUBBLE_SORT:
          if(isShuffled == false){writeToScreen("BUBBLE SORT");}

          sortButton = digitalRead(RIGHT_BUTTON);
          
          if(sortButton != lastSortButton)
          {
            if(sortButton == HIGH)
            {
              if(isShuffled == true)
              {
                bubbleSort(sortingArray, ARRAY_SIZE);
                isShuffled = false;
              }
            }
            lastSortButton = sortButton;
          }
          else
          {
            continue;
          }
        break;
        case HEAP_SORT:
          if(isShuffled == false){writeToScreen("HEAP SORT");}

          sortButton = digitalRead(RIGHT_BUTTON);

          if(sortButton != lastSortButton)
          {
            if(sortButton == HIGH)
            {
              if(isShuffled == true)
              {
                heapSort(sortingArray, ARRAY_SIZE);
                isShuffled = false;
              }
            }
            lastSortButton = sortButton;
          }
          else
          {
            continue;
          }
        break;
        case QUICK_SORT:
          if(isShuffled == false){writeToScreen("QUICK SORT");}

          sortButton = digitalRead(RIGHT_BUTTON);

          if(sortButton != lastSortButton)
          {
            if(sortButton == HIGH)
            {
              if(isShuffled == true)
              {
                quickSort(sortingArray, 0, ARRAY_SIZE - 1);
                isShuffled = false;
              }
            }
            lastSortButton = sortButton;
          }
          else
          {
            continue;
          }
        break;
        case SHELL_SORT:
          if(isShuffled == false){writeToScreen("SHELL SORT");}

          sortButton = digitalRead(RIGHT_BUTTON);

          if(sortButton != lastSortButton)
          {
            if(sortButton == HIGH)
            {
              if(isShuffled == true)
              {
                shellSort(sortingArray, ARRAY_SIZE);
                isShuffled = false;
              }
            }
            lastSortButton = sortButton;
          }
          else
          {
            continue;
          }
        break;
        case COUNTING_SORT:
          if(isShuffled == false){writeToScreen("COUNTING SORT");}

          sortButton = digitalRead(RIGHT_BUTTON);

          if(sortButton != lastSortButton)
          {
            if(sortButton == HIGH)
            {
              if(isShuffled == true)
              {
                countingSort(sortingArray, ARRAY_SIZE, STATIC_ARRAY[ARRAY_SIZE - 1]);
                isShuffled = false;
              }
            }
            lastSortButton = sortButton;
          }
          else
          {
            continue;
          }
        break;
        case RADIX_SORT:
          if(isShuffled == false){writeToScreen("RADIX SORT");}

          sortButton = digitalRead(RIGHT_BUTTON);

          if(sortButton != lastSortButton)
          {
            if(sortButton == HIGH)
            {
              if(isShuffled == true)
              {
                radixSort(sortingArray, ARRAY_SIZE);
                isShuffled = false;
              }
            }
            lastSortButton = sortButton;
          }
          else
          {
            continue;
          }
        break;
        case BOGO_SORT:
          if(isShuffled == false){writeToScreen("BOGO SORT");}

          sortButton = digitalRead(RIGHT_BUTTON);

          if(sortButton != lastSortButton)
          {
            if(sortButton == HIGH)
            {
              if(isShuffled == true)
              {
                bogoSort(sortingArray, STATIC_ARRAY, ARRAY_SIZE);
                isShuffled = false;
              }
            }
            lastSortButton = sortButton;
          }
          else
          {
            continue;
          }
        break;
      }
    }
}

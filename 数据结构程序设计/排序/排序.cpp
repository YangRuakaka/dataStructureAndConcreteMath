/****************************************************************
 * Project Name:  排序
 * File Name:     排序.cpp
 * File Function: Problem solution
 * Update Date:   2023/11/3
 ****************************************************************/

/****************************************************************
 * Problem Description
 ****************************************************************/


//随机函数产生10000个随机数，用快速排序，直接插入排序，冒泡排序，
//选择排序的排序方法排序，并统计每种排序所花费的排序时间和交换次数。
//其中，随机数的个数由用户定义，系统产生随机书。并且显示他们的比较次数。


/****************************************************************
 * Problem Solution
 ****************************************************************/

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <conio.h>

 /***************************************************************************
  Function Name:pause
  Function:To wait for the space to continue
  Input Parameters:void
  Return Value:void
  Documentation：
 ****************************************************************************/
void pause()
{
    while (_getch() != '\r')
        ;
    std::cout << std::endl;
}

 /***************************************************************************
   Function Name:MenuDisplay
   Function:To display the menu
   Input Parameters:void
   Return Value:void
   Documentation：
  ****************************************************************************/
void menuDisplay()
{
    std::cout << "            排序算法比较            " << std::endl;
    std::cout << "====================================" << std::endl;
    std::cout << "  *         1---冒泡排序         *  " << std::endl;
    std::cout << "  *         2---选择排序         *  " << std::endl;
    std::cout << "  *         3---直接插入排序     *  " << std::endl;
    std::cout << "  *         4---希尔排序         *  " << std::endl;
    std::cout << "  *         5---快速排序         *  " << std::endl;
    std::cout << "  *         6---堆排序           *  " << std::endl;
    std::cout << "  *         7---归并排序         *  " << std::endl;
    std::cout << "  *         8---基数排序         *  " << std::endl;
    std::cout << "  *         9---退出程序         *  " << std::endl;
    std::cout << "====================================" << std::endl;
}

/***************************************************************************
  Function Name:shellSort
  Function:To sort array by shellSort
  Input Parameters:array to sort,size of array,comparisons,swaps
  Return Value:void
  Documentation：
 ****************************************************************************/
void shellSort(int arr[], int size, int& comparisons, int& swaps)
{
    //Gap from size/2 to 1
    for (int gap = size / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < size; i++) {
            int key = arr[i];//Store the element
            int j = i;//record the index

            //Insert sort
            while (j >= gap && arr[j - gap] > key) {
                comparisons++;
                arr[j] = arr[j - gap];
                swaps++;
                j -= gap;
            }

            arr[j] = key;
        }
    }
}

/***************************************************************************
  Function Name:heapify
  Function:To make the number which the index of i is pointing is the largest number of its child
  Input Parameters:array to sort,size of array,index i,comparisons,swaps
  Return Value:void
  Documentation：
 ****************************************************************************/
void heapify(int arr[], int size, int i, int& comparisons, int& swaps) 
{
    int largest = i;//Parent index
    int left = 2 * i + 1;//Left child index
    int right = 2 * i + 2;//Right child index

    //To maket the parent index is pointing to the largest number of its child
    if (left < size && arr[left] > arr[largest]) {
        comparisons++;
        largest = left;
    }
    if (right < size && arr[right] > arr[largest]) {
        comparisons++;
        largest = right;
    }

    //If the largest number is already in the place,quit
    if (largest != i) {
        std::swap(arr[i], arr[largest]);//Swap the largest number to the i position
        swaps++;
        heapify(arr, size, largest, comparisons, swaps);//In case after switch,the largest position's number is not the largest number of its child
    }
}

/***************************************************************************
  Function Name:heapSort
  Function:To sort array by heapSort
  Input Parameters:array to sort,size of array,comparisons,swaps
  Return Value:void
  Documentation：
 ****************************************************************************/
void heapSort(int arr[], int size, int& comparisons, int& swaps) 
{
    //0 1 2 3 4 5 6 7 8 9(index)
    //4 is the parent of 9
    //3 is the parent of 7 8
    //2 is the parent of 5 6
    //1 is the parent of 3 4
    //0 is the parent of 1 2
    //Form the bottom to the top
    for (int i = size / 2 - 1; i >= 0; i--) {
        heapify(arr, size, i, comparisons, swaps);
    }

    //Make the Last element the largest number,and 
    for (int i = size - 1; i >= 0; i--) {
        //arr[0]is the largest number,arr[i]is the last number of the unordered array
        std::swap(arr[0], arr[i]);
        swaps++;
        heapify(arr, i, 0, comparisons, swaps);//Make the arr[0] the largest number
    }
}

/***************************************************************************
  Function Name:merge
  Function:To merge two parts
  Input Parameters:array to sort,three index,comparisons,swaps
  Return Value:void
  Documentation：
 ****************************************************************************/
void merge(int arr[], int left, int mid, int right, int& comparisons, int& swaps) 
{

    int n1 = mid - left + 1;//Left part size
    int n2 = right - mid;//Right part size

    //To store the two parts
    int* L = new int[n1];//Left part
    int* R = new int[n2];//Right part
   
    //Replicate the two parts
    for (int i = 0; i < n1; i++) {
        L[i] = arr[left + i];
    }
    for (int j = 0; j < n2; j++) {
        R[j] = arr[mid + 1 + j];
    }

    int i = 0, j = 0, k = left;//Initialize three index

    //If the index is in place
    while (i < n1 && j < n2) {
        //Choose the number that is smaller and move it to the right place in the array
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        swaps++;
        comparisons++;
        k++;
    }

    //If the right part has been checked over,Push all the left part
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
        swaps++;
    }
    //If the left part has been checked over,Push all the right part
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
        swaps++;
    }
}

/***************************************************************************
  Function Name:mergeSort
  Function:To sort array by mergeSort
  Input Parameters:array to sort,left right index,comparisons,swaps
  Return Value:void
  Documentation：
 ****************************************************************************/
void mergeSort(int arr[], int left, int right, int& comparisons, int& swaps) 
{
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid, comparisons, swaps);//Sort left part
        mergeSort(arr, mid + 1, right, comparisons, swaps);//Sort right part
        merge(arr, left, mid, right, comparisons, swaps);//Merge the two part into an ordered array
    }
}



/***************************************************************************
  Function Name:getMax
  Function:To get the max number of the array
  Input Parameters:array,size
  Return Value:void
  Documentation：
 ****************************************************************************/
int getMax(int arr[], int size)
{
    int max = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}

/***************************************************************************
  Function Name:countSort
  Function:To sort array by countSort in exp
  Input Parameters:array to sort,size of array,exp,comparisons,swaps
  Return Value:void
  Documentation：
 ****************************************************************************/
void countSort(int arr[],int size, int exp, int& comparisons, int& swaps)
{
    int* output = new int[size];//New a output array
    int count[10] = { 0 };//There are ten position from 0 to 9 for all the numbers

    for (int i = 0; i < size; i++) {
        count[(arr[i] / exp) % 10]++;//(arr[i] / exp) % 10 is the key 
    }

    //If count[1] is 10,and count[2] is 5
    //So the first element in count[2] will be stored in array[14](5+10-1=14)
    //Sum the count,as it will be used as an index 
    for (int i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }

    for (int i = size - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];//Push the smallest number into the output
        count[(arr[i] / exp) % 10]--;//Count--
    }

    for (int i = 0; i < size; i++) {
        arr[i] = output[i];//Replicate to the array
        swaps++;
    }
}

/***************************************************************************
  Function Name:radixSort
  Function:To sort array by radixSort
  Input Parameters:array to sort,size of array,comparisons,swaps
  Return Value:void
  Documentation：
 ****************************************************************************/
void radixSort(int arr[], int size, int& comparisons, int& swaps) 
{
    int max = getMax(arr, size);//Get the max

    //Exp is the exponential,from 1 to the max / exp(highest exp of all number)
    //Sort from unit's digit,ten's digit,hundred's digit...
    for (int exp = 1; max / exp > 0; exp *= 10) {
        countSort(arr, size, exp, comparisons, swaps);
    }
}

/***************************************************************************
  Function Name:generateRandomNumbers
  Function:To generate random numbers
  Input Parameters:array to sort,size of array
  Return Value:void
  Documentation：
 ****************************************************************************/
void generateRandomNumbers(int arr[], int size)
{
    for (int i = 0; i < size; ++i) {
        arr[i] = rand();
    }
}

/***************************************************************************
  Function Name:quickSort
  Function:To sort array by quicksort
  Input Parameters:array to sort,left index,right index,comparisons,swaps
  Return Value:void
  Documentation：
 ****************************************************************************/
void quickSort(int arr[], int left, int right, int& comparisons, int& swaps) 
{
    int i = left, j = right;//I,j for left and right index
    int pivot = arr[(left + right) / 2];//Set the middle number as the pivot

    //If the left index is smaller than right index
    while (i <= j) {

        //The left index is to find the number that is greater than pivot
        //From the left to the right
        while (arr[i] < pivot) {
            comparisons++;//Record every comparison
            i++;//Move the index
        }

        //The left index is to find the number that is smaller than pivot
        //From the right to the left
        while (arr[j] > pivot) {
            comparisons++;//Record every comparison
            j--;//Move the index
        }

        //If the left index is smaller or equal to the right index after moving
        if (i <= j) {
            std::swap(arr[i], arr[j]);//Swap two number as we want the bigger in the right,smaller in the left
            swaps++;//Record the swap
            i++;//Move two indexes
            j--;
        }
    }

    //If the left(start index) is smaller than right index
    if (left < j) 
        quickSort(arr, left, j, comparisons, swaps);//Go in to the left part
    //If the right(start index) is bigger than left index
    if (i < right) 
        quickSort(arr, i, right, comparisons, swaps);//Go in to the right part
    
}

/***************************************************************************
  Function Name:insertionSort
  Function:To sort array by insertionSort
  Input Parameters:array to sort,size of array,comparisons,swaps
  Return Value:void
  Documentation：
 ****************************************************************************/
void insertionSort(int arr[], int size, int& comparisons, int& swaps) 
{

    for (int i = 1; i < size; ++i) {

        int key = arr[i];//Set the number we are checking as the key(from the second number in the array)
        int j = i - 1;//Set j next to i(we want to check all the number that is left to the key)

        //Check all the number left to key until we find one that is smaller than the key
        while (j >= 0 && arr[j] > key) {
            comparisons++;//Record every comparison
            arr[j + 1] = arr[j];//Move the number to the right(one step)
            swaps++;//Record every swap
            j--;//j index move to the left(one step)
        }

        arr[j + 1] = key;//arr[j] is smaller than the key and the arr[j + 1] is the former place for the number bigger than the key
        //Insert the key to the right position                                                         
    }

}

/***************************************************************************
  Function Name:bubbleSort
  Function:To sort array by bubbleSort
  Input Parameters:array to sort,size of array,comparisons,swaps
  Return Value:void
  Documentation：
 ****************************************************************************/
void bubbleSort(int arr[], int size, int& comparisons, int& swaps) 
{

    for (int i = 0; i < size - 1; ++i) {//Sort until end
        for (int j = 0; j < size - i - 1; ++j) {//Sort until the number we are checking
            comparisons++;//Record every comparison
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);//Greater in the right
                swaps++;//Record every swap
            }
        }
    }
}

/***************************************************************************
  Function Name:selectionSort
  Function:To sort array by bubbleSort
  Input Parameters:array to sort,size of array,comparisons,swaps
  Return Value:void
  Documentation：
 ****************************************************************************/
void selectionSort(int arr[], int size, int& comparisons, int& swaps) 
{
    for (int i = 0; i < size - 1; ++i) {
        int minIndex = i;//Set the minindex as itself
        for (int j = i + 1; j < size; ++j) {
            comparisons++;//Record every comparisons
            if (arr[j] < arr[minIndex]) 
                minIndex = j;//Upgrade the minindex
        }
        std::swap(arr[i], arr[minIndex]);//Always let the position store the minimun of all the number right to it
        swaps++;//Record every swap
    }
}

void bubbleCalculate(int arr[], int size, int& comparisons, int& swaps)
{
    auto start = std::chrono::high_resolution_clock::now();
    bubbleSort(arr, size, comparisons, swaps);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    std::cout << "冒泡排序比较次数: " << comparisons << std::endl;
    std::cout << "冒泡排序交换次数: " << swaps << std::endl;
    std::cout << "冒泡排序所需时间: " << duration.count() << " 毫秒" << std::endl;
}
void selectionCalculate(int arr[], int size, int& comparisons, int& swaps)
{
    auto start = std::chrono::high_resolution_clock::now();
    selectionSort(arr, size, comparisons, swaps);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    std::cout << "选择排序比较次数: " << comparisons << std::endl;
    std::cout << "选择排序交换次数: " << swaps << std::endl;
    std::cout << "选择排序所需时间: " << duration.count() << " 毫秒" << std::endl;
}

void insertionCalculate(int arr[], int size, int& comparisons, int& swaps)
{
    auto start = std::chrono::high_resolution_clock::now();
    insertionSort(arr, size, comparisons, swaps);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    std::cout << "插入排序比较次数: " << comparisons << std::endl;
    std::cout << "插入排序交换次数: " << swaps << std::endl;
    std::cout << "插入排序所需时间: " << duration.count() << " 毫秒" << std::endl;
}

void shellCalculate(int arr[], int size, int& comparisons, int& swaps)
{
    auto start = std::chrono::high_resolution_clock::now();
    shellSort(arr, size, comparisons, swaps);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    std::cout << "希尔排序比较次数: " << comparisons << std::endl;
    std::cout << "希尔排序交换次数: " << swaps << std::endl;
    std::cout << "希尔排序所需时间: " << duration.count() << " 毫秒" << std::endl;
}

void quickCalculate(int arr[], int size, int& comparisons, int& swaps)
{
    auto start = std::chrono::high_resolution_clock::now();
    quickSort(arr, 0, size - 1, comparisons, swaps);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    std::cout << "快速排序比较次数: " << comparisons << std::endl;
    std::cout << "快速排序交换次数: " << swaps << std::endl;
    std::cout << "快速排序所需时间: " << duration.count() << " 毫秒" << std::endl;
}

void heapCalculate(int arr[], int size, int& comparisons, int& swaps)
{
    auto start = std::chrono::high_resolution_clock::now();
    heapSort(arr, size, comparisons, swaps);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    std::cout << "堆排序比较次数: " << comparisons << std::endl;
    std::cout << "堆排序交换次数: " << swaps << std::endl;
    std::cout << "堆排序所需时间: " << duration.count() << " 毫秒" << std::endl;
}

void mergeCalculate(int arr[], int size, int& comparisons, int& swaps)
{
    auto start = std::chrono::high_resolution_clock::now();
    mergeSort(arr, 0, size - 1, comparisons, swaps);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    std::cout << "归并排序比较次数: " << comparisons << std::endl;
    std::cout << "归并排序交换次数: " << swaps << std::endl;
    std::cout << "归并排序所需时间: " << duration.count() << " 毫秒" << std::endl;
}

void radixCalculate(int arr[], int size, int& comparisons, int& swaps)
{
    auto start = std::chrono::high_resolution_clock::now();
    radixSort(arr, size, comparisons, swaps);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    std::cout << "基数排序比较次数: " << comparisons << std::endl;
    std::cout << "基数排序交换次数: " << swaps << std::endl;
    std::cout << "基数排序所需时间: " << duration.count() << " 毫秒" << std::endl;
}
int main()
{
 
   //The loop can let the user execute the process repeatedly
    while (true) {

        const int size = 10000;
        int arr[size];

        srand(static_cast<unsigned>(time(0)));
        generateRandomNumbers(arr, size);

        int comparisons = 0, swaps = 0;

        
        //Clear our screen
        system("cls");

        //Display our list
        menuDisplay();

        char controller;//Create a variable to hold the choice we input
        while (true) {
            controller = _getch();//_getch can avoid displaying undesired input on the screen

            if (controller >= '1' && controller <= '9') {
                std::cout << controller << std::endl;//Display the choice on the screen
                
                switch (controller)
                {
                    case '1':
                        bubbleCalculate(arr, size, comparisons, swaps);
                        std::cout << "操作完成，按回车继续..." << std::endl;
                        pause();
                        break;
                    case '2':
                        selectionCalculate(arr, size, comparisons, swaps);
                        std::cout << "操作完成，按回车继续..." << std::endl;
                        pause();
                        break;
                    case '3':
                        insertionCalculate(arr, size, comparisons, swaps);
                        std::cout << "操作完成，按回车继续..." << std::endl;
                        pause();
                        break;
                    case '4':
                        shellCalculate(arr, size, comparisons, swaps);
                        std::cout << "操作完成，按回车继续..." << std::endl;
                        pause();
                        break;
                    case '5':
                        quickCalculate(arr, size, comparisons, swaps);
                        std::cout << "操作完成，按回车继续..." << std::endl;
                        pause();
                        break;
                    case '6':
                        heapCalculate(arr, size, comparisons, swaps);
                        std::cout << "操作完成，按回车继续..." << std::endl;
                        pause();
                        break;
                    case '7':
                        mergeCalculate(arr, size, comparisons, swaps);
                        std::cout << "操作完成，按回车继续..." << std::endl;
                        pause();
                        break;
                    case '8':
                        radixCalculate(arr, size, comparisons, swaps);
                        std::cout << "操作完成，按回车继续..." << std::endl;
                        pause();
                        break;
                    case '9':
                        std::cout << "程序结束！" << std::endl;
                        return 0;
                    default:
                        continue;
                }
                break;
            }//end of if
        }//end of while


    }//end of while

    return 0;
}

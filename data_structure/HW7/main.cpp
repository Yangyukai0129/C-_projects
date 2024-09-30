#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <fstream>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

// 創建大小為size的整數陣列
int *generateArray(int size) { return new int[size]; }

// 讀取檔案資料，並存入新創建的陣列中
// 第一個int *(指向整數陣列的指標)用來儲存從檔案中讀取的數據；第二個int用來獲取陣列大小
void getRawArray(std::vector<std::pair<int *, int>> &arraySets)
{
    // 創建ifstream物件，嘗試打開input.txt檔案，用來讀取檔案資料
    std::ifstream file("input.txt", std::ifstream::in);
    // 站存每次從檔案讀取到的陣列大小
    int n;
    while (file >> n)
    {
        int *arr = generateArray(n);
        for (int i = 0; i < n; i++)
            // 每次讀取一個整數，存入 arr[i]
            file >> arr[i];
        // 將已讀取並存儲好的陣列和它的大小 n 組成一個 pair，然後加入到 arraySets 向量中。
        // 這個 pair 讓我們可以同時存儲陣列的內容和它的大小。
        arraySets.push_back(std::make_pair(arr, n));
    }
    // 關閉檔案，釋放檔案相關資源
    file.close();
}

// 將排序結果和排序時間輸出到檔案中
void outputResult(std::string sortingAlgorithm, int *arr, int size, float deltaTime)
{
    std::ofstream outputFile(sortingAlgorithm + std::to_string(size) + ".txt", std::ofstream::out);
    outputFile << "The total time is " << deltaTime << " seconds\n";
    for (auto i = 0; i < size; i++)
        outputFile << arr[i] << std::endl;
    outputFile.close();
}

void insertionSort(int *arr, int n)
{
    int j;
    int currentVal;
    for (int i = 1; i < n; i++)
    {
        currentVal = arr[i];
        for (j = i - 1; j >= 0 && arr[j] > currentVal; j--)
            arr[j + 1] = arr[j];
        arr[j + 1] = currentVal;
    }
}

void merge(int *arr, int front, int tail, int middle)
{
    int leftSize = middle - front + 1, rightize = tail - middle;
    int *leftSubArray = new int[leftSize], *rightSubArray = new int[rightize];
    // 需#include cstring，将原数组的对应部分复制到临时数组中
    // memcpy(目标地址的指针,指向要复制数据的源地址(即数据从这里开始复制),从源地址复制到目标地址的数据量（以字节为单位）)
    std::memcpy(leftSubArray, arr + front, leftSize * sizeof(int));
    std::memcpy(rightSubArray, arr + middle + 1, rightize * sizeof(int));

    // i指向左子數組的第一個元素,j指向右子數組的第一個元素,k指向目標數組(原數組)的起始位置
    int i = 0, j = 0, k = front;
    // 進行排序
    while (i < leftSize && j < rightize)
    {
        if (leftSubArray[i] <= rightSubArray[j])
            arr[k++] = leftSubArray[i++];
        else
            arr[k++] = rightSubArray[j++];
    }

    // 如果左數組或右數組還有剩餘沒有進行排序，則加回原數組
    while (i < leftSize)
        arr[k++] = leftSubArray[i++];
    while (j < rightize)
        arr[k++] = rightSubArray[j++];

    delete[] leftSubArray;
    delete[] rightSubArray;
}

void mergeSort(int *arr, int front, int tail)
{
    if (front < tail)
    {
        int middle = (front + tail) / 2;
        mergeSort(arr, front, middle);
        mergeSort(arr, middle + 1, tail);
        merge(arr, front, tail, middle);
    }
}

void swap(int a, int b)
{
    int temp = a;
    a = b;
    b = temp;
}

void quickSort(int *arr, int left, int right)
{
    if (left >= right)
        return;
    int i = left, j = right + 1;
    int pivot = arr[left];
    do
    {
        do
            i++;
        while (i <= right && arr[i] < pivot);
        do
        {
            j--;
        } while (j >= left && arr[j] > pivot);
        if (i < j)
            swap(arr[i], arr[j]);
    } while (i < j);
    swap(arr[left], arr[j]);

    quickSort(arr, left, j - 1);
    quickSort(arr, j + 1, right);
}

// qsort(需#include cstdlib)
int compareOfqSsort(const void *a, const void *b)
{
    long int val1 = *(const long int *)a;
    long int val2 = *(const long int *)b;
    if (val1 < val2)
        return -1;
    if (val1 > val2)
        return 1;
    return 0;
}

int main()
{
    std::vector<std::pair<int *, int>> arraySets;
    int modeSelection = 0;
    // 需include <ctime>
    clock_t deltaTime;
    getRawArray(arraySets);
    std::cout << "read file done" << std::endl;

    std::cout << "choose 1-5 to sort list: ";
    std::cin >> modeSelection;
    switch (modeSelection)
    {
    case 1:
        std::cout << "insertion Sort" << std::endl;
        for (auto arrayIndex : arraySets)
        {
            deltaTime = clock();
            // arrayIndex.second - 1是為了要得到最後一個有效索引
            insertionSort(arrayIndex.first, arrayIndex.second);
            deltaTime = clock() - deltaTime;
            float elapsedTime = ((float)deltaTime) / CLOCKS_PER_SEC;
            // outputResult(std::string("insertion Sort"), arrayIndex.first, arrayIndex.second, elapsedTime);
            if (elapsedTime > 300)
            {
                std::cout << "Execution time exceeded limit (TLE)" << std::endl;
            }
            else
                std::cout << "The total time is " << elapsedTime << " seconds\n";
        }
        break;
    case 2:
        std::cout << "merge Sort" << std::endl;
        for (auto arrayIndex : arraySets)
        {
            deltaTime = clock();
            mergeSort(arrayIndex.first, 0, arrayIndex.second - 1);
            deltaTime = clock() - deltaTime;
            float elapsedTime = ((float)deltaTime) / CLOCKS_PER_SEC;
            // outputResult(std::string("merge Sort"), arrayIndex.first, arrayIndex.second, elapsedTime);
            if (elapsedTime > 300)
            {
                std::cout << "Execution time exceeded limit (TLE)" << std::endl;
            }
            else
                std::cout << "The total time is " << elapsedTime << " seconds\n";
        }
        break;
    case 3:
        std::cout << "quick Sort" << std::endl;
        for (auto arrayIndex : arraySets)
        {
            deltaTime = clock();
            quickSort(arrayIndex.first, 0, arrayIndex.second - 1);
            deltaTime = clock() - deltaTime;
            float elapsedTime = ((float)deltaTime) / CLOCKS_PER_SEC;
            // outputResult(std::string("quick Sort"), arrayIndex.first, arrayIndex.second, elapsedTime);
            if (elapsedTime > 300)
            {
                std::cout << "Execution time exceeded limit (TLE)" << std::endl;
            }
            else
                std::cout << "The total time is " << elapsedTime << " seconds\n";
        }
        break;
    case 4:
        std::cout << "stdlib qSort" << std::endl;
        for (auto arrayIndex : arraySets)
        {
            deltaTime = clock();
            // qsort(指向要排序的數組的指標,數組中元素的數量,單個元素的大小（以字節為單位）,指向比較函數的指標。該函數用於比較數組中的兩個元素，並決定它們的排序順序)
            qsort(arrayIndex.first, arrayIndex.second, sizeof(int), compareOfqSsort);
            deltaTime = clock() - deltaTime;
            float elapsedTime = ((float)deltaTime) / CLOCKS_PER_SEC;
            // outputResult(std::string("qSort Sort"), arrayIndex.first, arrayIndex.second, elapsedTime);
            if (elapsedTime > 300)
            {
                std::cout << "Execution time exceeded limit (TLE)" << std::endl;
            }
            else
                std::cout << "The total time is " << elapsedTime << " seconds\n";
        }
        break;
    case 5:
        std::cout << "STL Sort" << std::endl;
        for (auto arrayIndex : arraySets)
        {
            deltaTime = clock();
            // 需#include algorithm
            // sort(指向要排序的區間的起始位置,指向要排序的區間的結束位置（該位置本身不包含在排序區間內）)
            std::sort(arrayIndex.first, arrayIndex.first + arrayIndex.second);
            deltaTime = clock() - deltaTime;
            float elapsedTime = ((float)deltaTime) / CLOCKS_PER_SEC;
            // outputResult(std::string("STL Sort"), arrayIndex.first, arrayIndex.second, elapsedTime);
            if (elapsedTime > 300)
            {
                std::cout << "Execution time exceeded limit (TLE)" << std::endl;
            }
            else
                std::cout << "The total time is " << elapsedTime << " seconds\n";
        }
        break;

    default:
        break;

        return 0;
    }
}
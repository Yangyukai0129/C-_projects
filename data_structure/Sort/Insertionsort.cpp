#include <iostream>
#include <vector>

using namespace std;

template <class T>
void insertionsort(vector<T> &a);

int main()
{
    vector<float> floatArray = {5.3, 2.1, 3.0, 1.0, 4.0, 7.0};
    insertionsort(floatArray);

    for (const auto &elem : floatArray)
    {
        cout << elem << " ";
    }
    cout << endl;

    return 0;
}

template <class T>
void insertionsort(vector<T> &a)
{
    int size = a.size();
    int j;
    T currentVal;
    for (int i = 1; i < size; i++)
    {
        currentVal = a[i];
        for (j = i - 1; j >= 0 && a[j] > currentVal; j--)
        {
            a[j + 1] = a[j];
        }
        // 會是j--後的值，因此會跟for迴圈的j的值不一樣
        a[j + 1] = currentVal;
    }
}

void merge(int *arr, int front, int tail, int middle)
{
    int leftSize = middle - front + 1, rightSize = tail - middle;

    int *leftSubArray = new int[leftSize], *rightSubArray = new int[rightSize];

    memcpy(leftSubArray, arr + front, leftSize * sizeof(int));
    memcpy(rightSubArray, arr + middle + 1, rightSize * sizeof(int));

    int i = 0, j = 0, k = front;
    while (i < leftSize && j < rightSize)
    {
        if (leftSubArray[i] <= rightSubArray[j])
            arr[k++] = leftSubArray[i++];
        else
            arr[k++] = rightSubArray[j++];
    }
    while (i < leftSize) // still have element in leftSubArray
        arr[k++] = leftSubArray[i++];
    while (j < rightSize)
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
}
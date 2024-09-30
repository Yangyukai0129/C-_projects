#include <iostream>
#include <cstring>
#include <vector>

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

int main()
{
    std::vector<int> IntArray = {5, 2, 3, 1, 4, 7};
    mergeSort(IntArray.data(), 0, IntArray.size() - 1);

    for (const auto &elem : IntArray)
    {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
    return 0;
}
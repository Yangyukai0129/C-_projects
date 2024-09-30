#include <iostream>
#include <vector>
#include <algorithm>

template <class T>
void Merge(T *initList, T *resultList, int leftStart, int leftEnd, int rightEnd)
{
    int rightStart = leftEnd + 1;
    int left = leftStart;
    int right = rightStart;
    int tempIndex = leftStart;

    // 合并两个子数组
    while (left <= leftEnd && right <= rightEnd)
    {
        if (initList[left] <= initList[right])
            resultList[tempIndex++] = initList[left++];
        else
            resultList[tempIndex++] = initList[right++];
    }

    // 复制左侧剩余元素
    while (left <= leftEnd)
        resultList[tempIndex++] = initList[left++];

    // 复制右侧剩余元素
    while (right <= rightEnd)
        resultList[tempIndex++] = initList[right++];
}

// 执行实际排序操作的地方
template <class T>
void MergePass(T *initList, T *resultList, const int n, const int s)
{
    int i;
    // 为了确保在合并操作中处理相邻的子数组，所以步长是2*s
    for (i = 0; i < n - 2 * s; i += 2 * s)
        // i：当前要归并的第一个子数组的起始索引。
        // i + s - 1：当前要归并的第一个子数组的结束索引。
        // i + 2 * s - 1：当前要归并的第二个子数组的结束索引。
        Merge(initList, resultList, i, i + s - 1, i + 2 * s - 1);
    // 当遍历到数组的尾部时，可能存在未完全合并的子数组的情况
    // 处理剩余的部分
    if (i + s < n)
        // i + s - 1 是当前子数组的结束索引。
        // n 是数组的总长度。
        // 如果 i + s 小于 n，则说明当前子数组（从索引 i 到 i + s - 1）完全在数组范围内，可以安全地将其与下一个子数组进行合并。
        Merge(initList, resultList, i, i + s - 1, n - 1);
    // 处理剩余未合并的元素
    else
        std::copy(initList + i, initList + n, resultList + i);
}

// MergeSort 函数通过调用 MergePass 来逐步增大已排序的子数组的大小
template <class T>
void MergeSort(T *a, const int n)
{
    // 在排序过程中存储临时的归并结果，避免在原始数组中直接操作
    T *tempList = new T[n + 1];
    // 循环控制子数组的长度
    for (int l = 1; l < n; l *= 2)
    {
        MergePass(a, tempList, n, l);
        l *= 2;
        MergePass(tempList, a, n, l);
    }
    // 例子:
    /*第一次 MergePass（MergePass(a, tempList, n, l)）：

此时 l = 1，意味着每个子数组的大小为 1。也就是说，每个元素都是一个独立的子数组。
在 MergePass 中：
每两个相邻的元素进行比较和合并，结果存储在 tempList 中。
例如，[5.3] 和 [2.1] 被合并为 [2.1, 5.3]，[3.0] 和 [1.0] 被合并为 [1.0, 3.0]，依此类推。
子数组长度翻倍：

l *= 2，子数组的大小变为 2。
第二次 MergePass（MergePass(tempList, a, n, l)）：

此时 l = 2，每个子数组的大小为 2。
在 MergePass 中：
每四个元素被分成两组，每两组进行比较和合并，结果存储回原始数组 a 中。
例如，[2.1, 5.3] 和 [1.0, 3.0] 被合并为 [1.0, 2.1, 3.0, 5.3]。*/
    delete[] tempList;
}

int main()
{
    std::vector<float> floatArray = {5.3, 2.1, 3.0, 1.0, 4.0, 7.0};
    MergeSort(floatArray.data(), floatArray.size());

    for (const auto &elem : floatArray)
    {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
    return 0;
}
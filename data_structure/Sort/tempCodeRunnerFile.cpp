#include <iostream>
#include <vector>

template <class T>
void swap(T &a, T &b)
{
    T temp = a;
    a = b;
    b = temp;
}

template <class T>
void Adjust(T *a, const int root, const int n)
{
    T e = a[root];
    int j;
    // 遍歷跟節點的左子節點(2n)
    for (j = 2 * root; j <= n; j *= 2)
    {
        // j指向左子節點，如果 j 小於 n 且左子節點小於右子節點，則將 j 增加 1，使其指向右子節點。這樣可以確保比較時使用的是較大的子節點
        if (j < n && a[j] < a[j + 1])
            j++;
        // 如果根節點的值大於等於較大子節點的值，則調整完成，跳出迴圈。
        if (e >= a[j])
            break;
        // 否則，將較大的子節點的值上移到根節點的位置，並繼續向下調整。
        a[j / 2] = a[j];
    }

    a[j / 2] = e;
}

template <class T>
void HeapSort(T *a, const int n)
{
    // 從最後有包含子節點的parent開始往前Adjust
    for (int i = n / 2; i >= 1; i--)
        Adjust(a, i, n);

    // 排序
    for (int i = n - 1; i >= 1; i--)
    {
        // 把第一個(最大)和最後進行swap
        swap(a[1], a[i + 1]);
        Adjust(a, 1, i);
    }
}

int main()
{
    std::vector<int> IntArray = {5, 2, 3, 1, 4, 7};
    HeapSort(IntArray.data(), IntArray.size());

    for (const auto &elem : IntArray)
    {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
    return 0;
}
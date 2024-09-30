#include <iostream>
#include <vector>

template <class T>
void quicksort(std::vector<T> &a, const int left, const int right);

template <class T>
void swap(T &a, T &b);

int main()
{
    std::vector<float> floatArray = {5.3, 2.1, 3.0, 1.0, 4.0, 7.0};
    quicksort(floatArray, 0, floatArray.size() - 1);

    for (const auto &elem : floatArray)
    {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
    return 0;
}

template <class T>
void quicksort(std::vector<T> &a, const int left, const int right)
{
    if (left >= right)
        return;

    int i = left, j = right + 1;
    T pivot = a[left];
    do
    {
        // 判斷左邊資料是否有小於pivot
        do
            i++;
        while (i <= right && a[i] < pivot);
        // 判斷右邊資料是否有小於pivot
        do
            j--;
        while (j >= left && a[j] > pivot);
        // 都找到後進行swap，讓左邊資料皆小於pivot，右邊資料皆大於pivot
        if (i < j)
            swap(a[i], a[j]);
    } while (i < j);
    // 全部完成後讓pivot放到中間(因為j會停留在交換前pivot的左側，所以要用j交換)
    swap(a[left], a[j]);

    // 接續做左邊及右邊的整理
    quicksort(a, left, j - 1);
    quicksort(a, j + 1, right);
}

template <class T>
void swap(T &a, T &b)
{
    T temp = a;
    a = b;
    b = temp;
}

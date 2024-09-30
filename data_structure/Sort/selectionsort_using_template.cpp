// 使用template方式，並使用vector減少更改data type時需調整的代碼數量

#include <iostream>
#include <vector>

template <class T>
void selectionsort(std::vector<T> &a);

template <class T>
void swap(T &a, T &b);

int main()
{
    // 使用 float 类型的数组进行排序
    std::vector<float> floatArray = {5.3, 2.1, 3.0, 1.0, 4.0, 7.0};
    selectionsort(floatArray);

    // 使用auto可自動推導elem類型
    for (const auto &elem : floatArray)
    {
        std::cout << elem << " ";
    }
    std::cout << std::endl;

    // 使用 int 类型的数组进行排序
    std::vector<int> intArray = {5, 2, 3, 1, 4, 7};
    selectionsort(intArray);

    for (const auto &elem : intArray)
    {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
    return 0;
}

template <class T>
void selectionsort(std::vector<T> &a)
{
    int size = a.size();
    for (int i = 0; i < size; i++)
    {
        int lowest = i;
        for (int j = i + 1; j < size; j++)
        {
            if (a[j] < a[lowest])
            {
                lowest = j;
            }
        }
        swap(a[i], a[lowest]);
    }
}
template <class T>
void swap(T &a, T &b)
{
    T temp;
    temp = a;
    a = b;
    b = temp;
}
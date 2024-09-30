#include <iostream>

int binarysearch(int arr[], int size, int elem);

int main()
{
    int arr[] = {1, 4, 5, 7, 9, 10, 12, 15};
    int size = sizeof(arr) / sizeof(arr[0]);
    int ans = binarysearch(arr, size, 5);
    std::cout << ans;
    return 0;
}

int binarysearch(int arr[], int size, int elem)
{
    int start = 0;
    int end = size - 1;
    int middle = (start + end) / 2;
    while (arr[middle] != elem && start <= end)
    {
        if (elem < arr[middle])
        {
            end = middle - 1;
        }
        else if (elem > arr[middle])
        {
            start = middle + 1;
        }
        middle = (start + end) / 2;
    }
    return arr[middle] == elem ? middle : -1;
}
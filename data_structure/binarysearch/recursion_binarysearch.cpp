#include <iostream>

int binarysearch(int arr[], int elem, int start, int end);

int main()
{
    int arr[] = {1, 4, 5, 7, 9, 10, 12, 15};
    int size = sizeof(arr) / sizeof(arr[0]);
    int start = 0;
    int end = size - 1;
    int target = 5;
    int ans = binarysearch(arr, target, start, end);
    std::cout << ans;
    return 0;
}

int binarysearch(int arr[], int elem, int start, int end)
{

    int middle = (start + end) / 2;
    if (start <= end)
    {
        if (elem < arr[middle])
        {
            return binarysearch(arr, elem, start, middle - 1);
        }
        else if (elem > arr[middle])
        {
            return binarysearch(arr, elem, middle + 1, end);
        }
        else
            return middle;
    }
    return -1;
}
#include <iostream>

void bubbleSort(int array[], int size);

int main()
{
    int array[] = {10, 1, 9, 2, 8, 3, 7, 4, 6};
    int size = sizeof(array) / sizeof(int);

    bubbleSort(array, size);

    for (int i = 0; i < size; i++)
    {
        std::cout << array[i] << '\n';
    }

    return 0;
}

void bubbleSort(int array[], int size)
{
    for (int i = size; i > 0; i--)
    {
        for (int j = 0; j < i - 1; j++)
        {
            if (array[j] > array[j + 1])
            {
                int temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }
}
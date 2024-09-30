#include <iostream>

void Permutation(char arr[], int k, int m);
void swap(char arr[], int start, int end);

int main()
{
    char arr[] = {'a', 'b', 'c', 'd', 'e', 'f'};
    int n = 3;
    Permutation(arr, 0, n - 1);

    return 0;
}

void Permutation(char arr[], int k, int m)
{
    if (k == m)
    {
        for (int i = 0; i <= m; i++)
        {
            std::cout << arr[i] << " ";
        }
        std::cout << std::endl;
    }
    else
    {
        for (int i = k; i <= m; i++)
        {
            // 將第一個值和指定的值進行swap做階層運算
            swap(arr, k, i);
            // 往下一直到最後的階層
            Permutation(arr, k + 1, m);
            // 把值swap回來為下一次的swap做準備
            swap(arr, k, i);

            // a b c d，a和b swap成b a c d
            // a c d接續進行permutation，直到最後的階層
            // swap回原來的位置a b c d為下一次的swap做準備
        }
    }
}

void swap(char arr[], int start, int end)
{
    char temp = arr[start];
    arr[start] = arr[end];
    arr[end] = temp;
}
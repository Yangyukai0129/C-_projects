#include <iostream>

int factorial(int num);

int main()
{
    std::cout << factorial(10);

    return 0;
}

// Recursive
// int factorial(int num)
// {
//     if (num > 1)
//     {
//         return num * factorial(num - 1);
//     }
//     else
//     {
//         return 1;
//     }
// }

// Iterative
int factorial(int num)
{
    int result = 1;
    for (int i = 1; i <= num; i++)
    {
        result = result * i;
    }
    return result;
}
#include <iostream>

int fib(int n);

int main()
{
    int n;
    std::cout << "Enter a number: " << std::endl;
    std::cin >> n;
    int ans = fib(n);
    std::cout << "The Fibonacci number of " << n << " is " << ans << std::endl;

    return 0;
}

int fib(int n)
{
    if (n == 0)
        return 0;
    else if (n == 1)
        return 1;
    else
        return (fib(n - 1) + fib(n - 2));
}
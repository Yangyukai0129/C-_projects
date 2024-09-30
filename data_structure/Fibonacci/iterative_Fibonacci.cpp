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
    int x, lofib, hifib;
    if (n <= 1)
        return n;
    lofib = 0;
    hifib = 1;
    // i是對照循環次數，因為fib(0)=0、fib(1)=1是已知初始值，不需要計算，所以循環變量i從2開始，即從第三個fib(2)開始計算
    for (int i = 2; i <= n; i++)
    {
        x = lofib;
        lofib = hifib;
        hifib = x + lofib;
    }

    return hifib;
}
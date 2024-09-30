#include <iostream>
using namespace std;

#define size 10000

void factorial(int n);
int fact(int x, int ar[], int ar_size);

int main()
{
    int n;

    cout << "Enter an integer number: ";
    cin >> n;

    factorial(n);

    return 0;
}

void factorial(int n)
{
    int ar[size];
    ar[0] = 1;
    int ar_size = 1;

    for (int x = 1; x <= n; x++)
    {
        ar_size = fact(x, ar, ar_size);

        // 打印每個階層的結果
        cout << x << "! = ";
        for (int i = ar_size - 1; i >= 0; i--)
            cout << ar[i];
        cout << endl;
    }
}

// x:當前要計算階層的數字
// ar[]:用來儲存階層結果的數組
// ar_size:數組ar[]中當前有效的位數
int fact(int x, int ar[], int ar_size)
{
    // c 代表进位，初始化为 0。每次乘法运算可能会产生一个进位（比如 9 * 9 = 81，进位是 8），这个变量就是用来处理这种情况的。
    int c = 0;
    for (int i = 0; i < ar_size; i++)
    {
        int p = ar[i] * x + c;
        ar[i] = p % 10;
        c = p / 10;
    }

    while (c)
    {
        ar[ar_size] = c % 10;
        c = c / 10;
        ar_size++;
    }
    return ar_size;
}

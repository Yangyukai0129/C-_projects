#include <iostream>

void towers(int n, char A, char B, char C);

int main()
{
    int n;
    std::cout << "Enter number: ";
    std::cin >> n;
    towers(n, 'A', 'B', 'C');
    return 0;
}

void towers(int n, char A, char B, char C)
{
    if (n == 1)
    {
        std::cout << "move disk 1 from peg " << A << " to peg " << C << std::endl;
        return;
    }
    towers(n - 1, A, C, B);
    std::cout << "move disk " << n << " from peg " << A << " to peg " << C << std::endl;
    towers(n - 1, B, A, C);
}
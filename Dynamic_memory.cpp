#include <iostream>

int main()
{
    // 範例一
    // int *pNum = NULL;

    // pNum = new int;

    // *pNum = 21;

    // std::cout << "address: " << pNum << '\n';
    // std::cout << "value: " << *pNum << '\n';

    // delete pNum;

    char *pGrades = nullptr;
    int size;

    std::cout << "How many grades to enter in?: ";
    std::cin >> size;

    pGrades = new char[size];

    for (int i = 0; i < size; i++)
    {
        std::cout << "Enter grade #:" << i + 1 << "\n";
        std::cin >> pGrades[i];
    }

    for (int i = 0; i < size; i++)
    {
        std::cout << pGrades[i] << " ";
    }

    delete[] pGrades;

    return 0;
}
#include <iostream>

int main()
{
    char **prowclumn = nullptr;
    int size;
    do
    {
        std::cout << "Enter a odd number: ";
        std::cin >> size;
    } while (size % 2 == 0);

    // 動態分配二維陣列
    prowclumn = new char *[size];
    for (int i = 0; i < size; ++i)
    {
        prowclumn[i] = new char[size]();
    }

    int first = size / 2;
    int key = 1;
    int row = 0, col = size / 2;
    prowclumn[row][col] = key;

    while (key < size * size)
    {
        int newRow = (row - 1 + size) % size; // 向上移動
        int newCol = (col - 1 + size) % size; // 向左移動

        if (prowclumn[newRow][newCol] != 0)
        { // 已被佔據
            row = (row + 1) % size;
        }
        else
        {
            row = newRow;
            col = newCol;
        }

        prowclumn[row][col] = ++key;
    }

    // 打印魔方陣
    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            std::cout << static_cast<int>(prowclumn[i][j]) << " ";
        }
        std::cout << std::endl;
    }

    // 釋放動態分配的記憶體
    for (int i = 0; i < size; ++i)
    {
        delete[] prowclumn[i];
    }

    delete[] prowclumn;

    return 0;
}
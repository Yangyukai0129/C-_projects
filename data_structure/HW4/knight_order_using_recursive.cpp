#include <iostream>
#include <iomanip>

using namespace std;

// 骑士的8个可能移动方向
const int dx[8] = {2, 1, -1, -2, -2, -1, 1, 2};
const int dy[8] = {1, 2, 2, 1, -1, -2, -2, -1};

bool isValid(int **board, int n, int x, int y)
{
    return (x >= 0 && x < n && y >= 0 && y < n && board[x][y] == -1);
}

void printBoard(int **board, int n)
{
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            cout << setw(2) << board[i][j] << " ";
        }
        cout << endl; // 在這裡換行，確保一行的所有元素打印在同一行
    }
}

// 判斷是否能完全走過所有棋盤
bool knightTour(int **board, int n, int x, int y, int moveCount)
{
    if (n == 1)
    {
        board[0][0] = 1; // 设置为 1，表示唯一的位置已经被访问
        return true;
    }

    // 如果已經達到最大步數，返回 true
    if (moveCount == n * n + 1)
    {
        return true;
    }

    for (int i = 0; i < 8; i++)
    {
        int newX = x + dx[i];
        int newY = y + dy[i];
        if (isValid(board, n, newX, newY))
        {
            board[newX][newY] = moveCount;
            if (knightTour(board, n, newX, newY, moveCount + 1))
                return true;
            // 回溯
            board[newX][newY] = -1;
        }
    }
    return false;
}

int main()
{
    int n;
    cout << "Enter a number: ";
    cin >> n;

    // 初始化行
    int **board = new int *[n];
    for (int i = 0; i < n; i++)
    {
        // 初始化列
        board[i] = new int[n];
        for (int j = 0; j < n; j++)
        {
            // 將行列資料初始化為-1
            board[i][j] = -1;
        }
    }

    // 初始化起始位置
    board[0][0] = 1;

    if (knightTour(board, n, 0, 0, 2)) // 起始位置设为(0, 0)，初始步数设为2
    {
        printBoard(board, n);
    }
    else
    {
        cout << "no solution" << endl;
    }

    // 释放内存
    for (int i = 0; i < n; ++i)
    {
        delete[] board[i];
    }
    delete[] board;

    return 0;
}

#include <iostream>
#include <stack>
#include <iomanip> // 为了设置输出格式

using namespace std;

template <class T>
class Stack
{
private:
    T *stack;
    int top;
    int capacity;

public:
    Stack(int stackCapacity);
    ~Stack() { delete[] stack; }
    bool IsEmpty() const;
    T &Top();
    void Push(const T &item);
    void Pop();
};

template <class T>
Stack<T>::Stack(int stackCapacity) : capacity(stackCapacity)
{
    stack = new T[capacity];
    top = -1;
}

template <class T>
inline bool Stack<T>::IsEmpty() const
{
    return top == -1;
}

template <class T>
inline T &Stack<T>::Top()
{
    if (IsEmpty())
        throw "Stack is empty";
    return stack[top];
}

template <class T>
void Stack<T>::Push(const T &x)
{
    if (top == capacity - 1)
        throw "Stack overflows";
    stack[++top] = x;
}

template <class T>
void Stack<T>::Pop()
{
    if (IsEmpty())
        throw "Stack is empty. Cannot delete";
    top--;
}

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
        cout << endl;
    }
}

// 判斷是否能完全走過所有棋盤
bool knightTour(int **board, int n, int startX = 0, int startY = 0)
{
    if (n == 1)
    {
        board[0][0] = 1; // 设置为 1，表示唯一的位置已经被访问
        return true;
    }

    // 初始化棧
    Stack<pair<int, int>> path(n * n);
    // 在還沒踏出第一步時預設為1，因此在最後判斷是否走完棋盤時要減1
    int moveCount = 1;

    // 用來判斷位置使用幾個方向
    int **tried = new int *[n];
    for (int i = 0; i < n; ++i)
    {
        tried[i] = new int[n];
        for (int j = 0; j < n; ++j)
        {
            tried[i][j] = 0;
        }
    }

    // 將起始位置放入棧中並標記
    path.Push({startX, startY});
    board[startX][startY] = moveCount++;

    while (!path.IsEmpty())
    {
        auto [x, y] = path.Top();
        bool moved = false;

        for (int i = tried[x][y]; i < 8; i++)
        {
            int newX = x + dx[i];
            int newY = y + dy[i];

            if (isValid(board, n, newX, newY))
            {
                path.Push({newX, newY});
                board[newX][newY] = moveCount++;
                tried[x][y] = i + 1;
                moved = true;
                break; // 跳出for循環進行下一次while
            }
        }

        if (!moved)
        {
            tried[x][y] = 0;
            board[x][y] = -1;
            moveCount--;
            path.Pop();
            // 不需要break，因为 if 语句执行完后，程序会自动继续执行 while 循环的下一次迭代
        }
        // 因為在還沒踏出第一步的時候moveCount就為1，所以跨出第一步moveCount=2，會多1，所以最終判斷是否完全走過時moveCount-1
        if (moveCount - 1 == n * n)
        {
            for (int i = 0; i < n; ++i)
            {
                delete[] tried[i];
            }
            delete[] tried;
            return true;
        }
    }

    for (int i = 0; i < n; ++i)
    {
        delete[] tried[i];
    }
    delete[] tried;
    return false;
}

int main()
{
    int n;
    cout << "Please enter a number: ";
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

    if (knightTour(board, n))
    {
        printBoard(board, n);
    }
    else
    {
        cout << "no solution" << endl;
    }

    // 释放棋盘内存
    for (int i = 0; i < n; ++i)
    {
        delete[] board[i];
    }
    delete[] board;

    return 0;
}

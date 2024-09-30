#include <iostream>
#include <vector>
#include <algorithm>
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

class Position
{
    friend class Term;
    friend class Matrix;

private:
    int row;
    int col;
    int times;

public:
    Position(int r = 0, int c = 0, int t = 0) : row(r), col(c), times(t) {}
    int getRow() const { return row; }
    int getCol() const { return col; }
    int getTimes() const { return times; }
    void setRow(int r) { row = r; }
    void setCol(int c) { col = c; }
    void setTimes(int t) { times = t; }
};

class Term
{
private:
    vector<Position> terms;
    Stack<Position> positionStack;
    int totalSteps;

public:
    Term(int stackCapacity, int totalSteps) : positionStack(stackCapacity), totalSteps(totalSteps) {}

    void addTerm(int r, int c, int t)
    {
        terms.emplace_back(r, c, t);
    }

    void removeTerm(int r, int c)
    {
        terms.erase(
            remove_if(terms.begin(), terms.end(), [r, c](const Position &term)
                      { return term.getRow() == r && term.getCol() == c; }),
            terms.end());
    }

    bool isPositionValid(int r, int c, int n) const
    {
        if (r < 0 || c < 0 || r >= n || c >= n)
            return false;
        for (const auto &term : terms)
        {
            if (term.getRow() == r && term.getCol() == c)
                return false;
        }
        return true;
    }

    bool move(int r, int c, int t, int n, int **prowclumn)
    {
        addTerm(r, c, t);
        positionStack.Push(Position(r, c, t));
        prowclumn[r][c] = t;

        if (t == totalSteps)
            return true; // All positions have been filled successfully

        vector<pair<int, int>> positionsToTest = {
            {r - 2, c + 1}, {r - 1, c + 2}, {r + 1, c + 2}, {r + 2, c + 1}, {r + 2, c - 1}, {r + 1, c - 2}, {r - 1, c - 2}, {r - 2, c - 1}};

        for (const auto &pos : positionsToTest)
        {
            int newRow = pos.first;
            int newCol = pos.second;
            if (isPositionValid(newRow, newCol, n))
            {
                if (move(newRow, newCol, t + 1, n, prowclumn))
                    return true;
            }
        }

        // Backtracking
        prowclumn[r][c] = 0;
        positionStack.Pop();
        removeTerm(r, c);
        return false;
    }
};

class Matrix
{
private:
    int n;
    int **prowclumn;
    Term term;

public:
    Matrix(int size, int stackCapacity) : n(size), term(stackCapacity, size * size)
    {
        prowclumn = new int *[n];
        for (int i = 0; i < n; ++i)
        {
            prowclumn[i] = new int[n];
            fill(prowclumn[i], prowclumn[i] + n, 0);
        }
    }

    ~Matrix()
    {
        for (int i = 0; i < n; ++i)
        {
            delete[] prowclumn[i];
        }
        delete[] prowclumn;
    }

    void move()
    {
        if (!term.move(0, 0, 1, n, prowclumn))
        {
            cout << "No solution" << endl;
        }
        else
        {
            display();
        }
    }

    void display()
    {
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                cout << setw(2) << prowclumn[i][j] << " ";
            }
            cout << endl;
        }
    }
};

int main()
{
    int n;
    cout << "Enter a number: ";
    cin >> n;

    Matrix matrix(n, n * n);
    matrix.move();

    return 0;
}

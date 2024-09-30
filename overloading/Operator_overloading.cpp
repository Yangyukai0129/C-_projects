#include <iostream>
#include <cstdlib>
using namespace std;

class MyVector
{
private:
    const int n;
    double *m;

public:
    // constructor
    MyVector();
    MyVector(int dim, double v[]);
    // copy constructor
    MyVector(const MyVector &v);
    // destructor
    ~MyVector();
    void print() const;
    bool operator==(const MyVector &v) const;
    bool operator<(const MyVector &v) const;
    bool operator!=(const MyVector &v) const;
    bool operator>(const MyVector &v) const;
    double operator[](int i) const;
    double &operator[](int i);
};
// 默认构造函数实现
MyVector::MyVector() : n(0)
{
    m = nullptr;
}
// 带参数的构造函数实现
MyVector::MyVector(int dim, double v[]) : n(dim)
{
    m = new double[dim];
    for (int i = 0; i < n; i++)
    {
        m[i] = v[i];
    }
}
// destructor
MyVector::~MyVector()
{
    delete[] m;
}
// copy constructor(deep copy)
MyVector::MyVector(const MyVector &v) : n(v.n)
{
    m = new double[v.n];
    for (int i = 0; i < v.n; i++)
    {
        m[i] = v.m[i];
    }
}
void MyVector::print() const
{
    cout << "(";
    for (int i = 0; i < n - 1; i++)
    {
        cout << m[i] << ",";
    }
    cout << m[n - 1] << ")\n";
}

bool MyVector::operator==(const MyVector &v) const
{
    if (this->n != v.n)
        return false;
    else
    {
        for (int i = 0; i < n; i++)
        {
            if (this->m[i] != v.m[i])
            {
                return false;
            }
        }
        return true;
    }
}

bool MyVector::operator<(const MyVector &v) const
{
    if (this->n != v.n)
        return false;
    else
    {
        for (int i = 0; i < n; i++)
        {
            if (this->m[i] >= v.m[i])
                return false;
        }
    }
    return true;
}

bool MyVector::operator!=(const MyVector &v) const
{
    if (*this == v)
        return false;
    else
        return true;
}

bool MyVector::operator>(const MyVector &v) const
{
    if (*this < v)
        return false;
    else
        return true;
}
double MyVector::operator[](int i) const
{
    if (i < 0 || i >= n)
        exit(1);
    return m[i];
}
double &MyVector::operator[](int i)
{
    if (i < 0 || i >= n)
        exit(1);
    return m[i];
}

int main()
{
    double d1[5] = {1, 2, 3, 4, 5};
    MyVector a1(5, d1);

    double d2[4] = {1, 2, 3, 4};
    MyVector a2(4, d2);
    // copy constructor
    const MyVector a3(a1);

    cout << (a1 == a2 ? "Y" : "N");
    cout << "\n";
    cout << (a1 == a3 ? "Y" : "N");
    cout << "\n";

    a2[0] = 999;
    if (a1 == a3)
        cout << a2[0] << " " << a3[0];

    return 0;
}
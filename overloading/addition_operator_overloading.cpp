#include <iostream>
#include <cstdlib>
using namespace std;

class MyVector
{
private:
    int n;
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
    MyVector &operator+=(const MyVector &v);
    const MyVector operator+(const MyVector &v);
    const MyVector operator+(double d);
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
MyVector &MyVector::operator+=(const MyVector &v)
{
    if (this->n == v.n)
    {
        for (int i = 0; i < n; i++) // 每個 element copy
            this->m[i] += v.m[i];
    }
    return *this;
}
const MyVector MyVector::operator+(const MyVector &v)
{
    MyVector sum(*this); // Create a copy of the current object
    sum += v;            // Use the += operator to add elements
    return sum;
}

const MyVector MyVector::operator+(double d)
{
    MyVector result(*this); // Create a copy of the current object
    for (int i = 0; i < n; i++)
        result.m[i] += d; // Add scalar to each element
    return result;
}

int main()
{
    double d1[5] = {1, 2, 3};
    MyVector a1(3, d1);
    MyVector a2(3, d1);

    a1 = a1 + a2;
    a1.print();
    a1 = a2 + 4.2;
    a1.print();

    return 0;
}
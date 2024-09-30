#include <algorithm>
#include <iostream>
using namespace std;

class CharArray
{
private:
    char data[256];

public:
    CharArray();
    CharArray(const CharArray &v);
    ~CharArray();
    CharArray operator+(const CharArray &v) const;
    CharArray operator*(const CharArray &v) const;
    CharArray operator-(const CharArray &v) const;
    bool operator>=(const int &q) const;
    friend ostream &operator<<(ostream &out, const CharArray &v);
    friend istream &operator>>(istream &in, CharArray &v);
};
// constructor
CharArray::CharArray()
{
    for (int i = 0; i < 256; i++)
    {
        data[i] = '\0';
    }
};
// copy constructor(deep copy)
CharArray::CharArray(const CharArray &v)
{
    for (int i = 0; i < 256; i++)
    {
        data[i] = v.data[i];
    }
}
CharArray::~CharArray()
{
    delete[] data;
}
CharArray CharArray::operator+(const CharArray &v) const
{
    CharArray result(*this); // Copy the current object into result
    int pos = 0;

    // Find the position of the first null character in result.data
    while (pos < 256 && result.data[pos] != '\0')
    {
        pos++;
    }

    // Append characters from v.data to result.data, ensuring no duplicates
    for (int i = 0; i < 256 && v.data[i] != '\0'; i++)
    {
        bool alreadyInResult = false;
        for (int j = 0; j < pos; j++)
        {
            if (result.data[j] == v.data[i])
            {
                alreadyInResult = true;
                break;
            }
        }
        if (!alreadyInResult && pos < 256)
        {
            result.data[pos++] = v.data[i];
        }
    }

    // Null-terminate the result if there's space
    if (pos < 256)
    {
        result.data[pos] = '\0';
    }

    return result;
}
CharArray CharArray::operator*(const CharArray &v) const
{
    CharArray result;
    int pos = 0;
    for (int i = 0; i < 256 && v.data[i] != '\0'; i++)
    {
        for (int j = 0; j < 256 && data[j] != '\0'; j++)
        {
            if (v.data[i] == data[j])
            {
                result.data[pos++] = v.data[i];
                break;
            }
        }
    }
    return result;
}
CharArray CharArray::operator-(const CharArray &v) const
{
    CharArray result;
    int pos = 0;
    for (int i = 0; i < 256 && data[i] != '\0'; i++)
    {
        bool found = false;
        for (int j = 0; j < 256 && v.data[i] != '\0'; j++)
        {
            if (data[i] == v.data[j])
            {
                found = true;
                break;
            }
        }
        if (!found)
        {
            result.data[pos++] = data[i];
        }
    }
    return result;
}
bool CharArray::operator>=(const int &v) const
{
    for (int i = 0; i < 256 && data[i] != '\0'; i++)
    {
        if (data[i] == v)
            return true;
    }
    return false;
}
ostream &operator<<(ostream &out, const CharArray &v)
{
    for (int i = 0; i < 256 && v.data[i] != '\0'; i++)
    {
        out << v.data[i];
    }
    return out;
}
istream &operator>>(istream &in, CharArray &v)
{
    char input[256];
    in.getline(input, 256);
    for (int i = 0; i < 256; i++)
    {
        v.data[i] = input[i];
        if (input[i] == '\0')
            break;
    }
    return in;
}

int main()
{
    CharArray arr1, arr2;
    char element;
    cout << "Enter A: ";
    cin >> arr1;
    cout << "Enter B: ";
    cin >> arr2;
    cout << "Enter element: ";
    cin >> element;
    CharArray arr3 = arr1 + arr2;
    cout << "A + B: " << arr3 << endl;
    arr3 = arr1 * arr2;
    cout << "A * B: " << arr3 << endl;
    arr3 = arr1 - arr2;
    cout << "A - B: " << arr3 << endl;
    arr3 = arr2 - arr1;
    cout << "B - A: " << arr3 << endl;
    cout << "element is " << (arr1 >= element ? "" : "not ") << "in A" << endl;
    cout << "element is " << (arr2 >= element ? "" : "not ") << "in B" << endl;

    return 0;
}
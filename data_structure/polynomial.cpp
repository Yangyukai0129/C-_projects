#include <iostream>
#include <vector>
using namespace std;

class Term;
class Polynomial
{
    friend class Term;

private:
    int degree; // 幾次方
    float coef; // 係數
public:
    Polynomial(int d = 0, float c = 0) : degree(d), coef(c) {} // 添加构造函数
    int getDegree() const { return degree; }
    float getCoef() const { return coef; }
    void setCoef(float c) { coef = c; }
};

class Term
{
private:
    vector<Polynomial> terms;

public:
    Term() = default;
    void addTerm(int degree, float coef)
    {
        // 遍歷terms vector，再有重複的coef時進行加總
        for (auto &term : terms)
        {
            if (term.getDegree() == degree)
            {
                term.setCoef(term.getCoef() + coef);
                return;
            }
        }
        // 對於還沒有的degree添加到terms這個vector
        terms.push_back(Polynomial(degree, coef));
    }
    Term operator+(const Term &other) const
    {
        Term result = *this;
        for (const auto &term : other.terms)
        {
            result.addTerm(term.getDegree(), term.getCoef());
        }
        return result;
    }
    void print() const
    {
        bool first = true;
        for (const auto &term : terms)
        {
            if (!first)
            {
                cout << " + ";
            }
            cout << term.getCoef() << "X^" << term.getDegree();
            first = false;
        }
        cout << endl;
    }
};

int main()
{
    Term A;
    A.addTerm(3, 2);
    A.addTerm(4, 1.5);

    Term B;
    B.addTerm(2, 3);
    B.addTerm(4, 2);
    B.addTerm(8, 1);

    Term C = A + B;
    C.print();

    return 0;
}
#include <iostream>

using namespace std;

class Chain;

enum Triple
{
    var,
    ptr,
    no
};

class PolyNode
{
private:
    PolyNode *next; // 链表中的下一个节点
    int exp;        // 指数
    Triple trio;    // 节点类型

    union
    {
        char vble;      // 用于存储变量名（当trio是var时使用）
        PolyNode *down; // 用于指向下一个子表（当trio是ptr时使用）
        int coef;       // 用于存储系数（当trio是no时使用）
    };

public:
    // 构造函数
    PolyNode(int exponent = 0, Triple type = no)
        : exp(exponent), trio(type), next(nullptr)
    {
        if (type == var)
        {
            vble = '\0'; // 初始化变量名
        }
        else if (type == ptr)
        {
            down = nullptr; // 初始化指针
        }
        else
        {
            coef = 0; // 初始化系数
        }
    }

    // 设置变量名
    void setVariable(char variable)
    {
        if (trio == var)
        {
            vble = variable;
        }
    }

    // 设置子表
    void setDown(PolyNode *downNode)
    {
        if (trio == ptr)
        {
            down = downNode;
        }
    }

    // 设置系数
    void setCoefficient(int coefficient)
    {
        if (trio == no)
        {
            coef = coefficient;
        }
    }

    int main()
    {
        return 0;
    }
};
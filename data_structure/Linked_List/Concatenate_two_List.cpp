#include <iostream>

template <class T>
class Chain;

template <class T>
class ChainNode
{
    friend class Chain<T>; // 修正为 Chain<T>

private:
    T data;
    ChainNode<T> *link; // 修正为指针

public:
    // 构造函数
    ChainNode(const T &element = T(), ChainNode<T> *next = nullptr)
    {
        data = element;
        link = next;
    }
};

template <class T>
class Chain
{
private:
    ChainNode<T> *first, *last;

public:
    Chain() : first(nullptr), last(nullptr) {} // 初始化指针
    void Create2();
    void Create3();
    void Concatenate(Chain<T> &b);
    void Display() const;
};

template <class T>
void Chain<T>::Create2()
{
    ChainNode<T> *second = new ChainNode<T>(20, nullptr);
    first = new ChainNode<T>(10, second);
    first = new ChainNode<T>(30, first);
    last = second; // 确保 last 指向链表的最后一个节点
}

template <class T>
void Chain<T>::Create3()
{
    ChainNode<T> *second = new ChainNode<T>(200, nullptr);
    first = new ChainNode<T>(100, second);
    first = new ChainNode<T>(300, first);
    last = second; // 确保 last 指向链表的最后一个节点
}

template <class T>
void Chain<T>::Concatenate(Chain<T> &b)
{
    if (first)
    {
        last->link = b.first;
        last = b.last;
    }
    else
    {
        first = b.first;
        last = b.last;
    }
    b.first = b.last = 0;
}

template <class T>
void Chain<T>::Display() const
{
    ChainNode<T> *current = first;
    while (current != nullptr)
    {
        std::cout << current->data << " ";
        current = current->link;
    }
    std::cout << std::endl;
}

int main()
{
    Chain<int> chainA, chainB;
    chainA.Create2();
    chainB.Create3();
    chainA.Concatenate(chainB);

    chainA.Display();

    return 0;
}

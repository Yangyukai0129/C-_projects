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
    void Reverse();
    void Display() const;
};

template <class T>
void Chain<T>::Create2()
{
    ChainNode<T> *second = new ChainNode<T>(30, nullptr);
    first = new ChainNode<T>(20, second);
    first = new ChainNode<T>(10, first);
    first = new ChainNode<T>(0, first);
    last = second; // 确保 last 指向链表的最后一个节点
}

template <class T>
void Chain<T>::Reverse()
{
    ChainNode<T> *current = first, *previous = 0;
    while (current)
    {
        ChainNode<T> *r = previous;
        previous = current;
        current = current->link;
        previous->link = r;
    }
    first = previous;
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
    Chain<int> chain;
    chain.Create2(); // 0 10 20 30
    chain.Reverse(); // reverse後變 30 20 10 0
    chain.Display();

    return 0;
}

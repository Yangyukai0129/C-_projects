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
    void InsertBack(const T &e);
    void Display() const;
};

template <class T>
void Chain<T>::Create2()
{
    ChainNode<T> *second = new ChainNode<T>(20, nullptr);
    first = new ChainNode<T>(10, second);
    last = second; // 确保 last 指向链表的最后一个节点
}

template <class T>
void Chain<T>::InsertBack(const T &e)
{
    if (first)
    {
        last->link = new ChainNode<T>(e);
        last = last->link;
    }
    else
    {
        first = last = new ChainNode<T>(e);
    }
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
    Chain<int> chain; // 正确实例化链表对象
    chain.Create2();
    chain.InsertBack(30); // 插入一个新元素到链表末尾
    chain.Display();

    return 0;
}

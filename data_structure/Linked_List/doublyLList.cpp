#include <iostream>

template <class T>
class Chain;

template <class T>
class ChainNode
{
    friend class Chain<T>; // 修正为 Chain<T>

private:
    T data;
    ChainNode<T> *nextlink; // 指向下一个节点
    ChainNode<T> *prevlink; // 指向前一个节点

public:
    // 构造函数
    ChainNode(const T &element = T(), ChainNode<T> *next = nullptr, ChainNode<T> *prev = nullptr)
    {
        data = element;
        nextlink = next;
        prevlink = prev;
    }
};

template <class T>
class Chain
{
private:
    ChainNode<T> *first, *last;

public:
    Chain() : first(nullptr), last(nullptr) {} // 初始化指针

    // 查找链表中值为 element 的节点
    ChainNode<T> *FindNode(const T &element)
    {
        ChainNode<T> *current = first;
        while (current != nullptr)
        {
            if (current->data == element)
            {
                return current;
            }
            current = current->nextlink;
        }
        return nullptr; // 找不到则返回 nullptr
    }

    void Create2();
    void Display() const;
    void DisplayReverse() const;
    void InsertAtHead(const T &e);
    void InsertAtTail(const T &e);
    void InsertAfter(ChainNode<T> *node, const T &e);
};

template <class T>
void Chain<T>::Create2()
{
    ChainNode<T> *fourth = new ChainNode<T>(30, nullptr, nullptr); // 链表的最后一个节点
    ChainNode<T> *third = new ChainNode<T>(20, fourth, nullptr);   // 倒数第二个节点
    fourth->prevlink = third;                                      // 设置 fourth 的 prevlink 指向 third

    ChainNode<T> *second = new ChainNode<T>(10, third, nullptr); // 中间的节点
    third->prevlink = second;                                    // 设置 third 的 prevlink 指向 second

    first = new ChainNode<T>(0, second, nullptr); // 链表的第一个节点
    second->prevlink = first;                     // 设置 second 的 prevlink 指向 first

    last = fourth; // 确保 last 指向链表的最后一个节点
}

template <class T>
void Chain<T>::Display() const
{
    ChainNode<T> *current = first;
    while (current != nullptr)
    {
        std::cout << current->data << " ";
        current = current->nextlink;
    }
    std::cout << std::endl;
}

template <class T>
void Chain<T>::DisplayReverse() const
{
    ChainNode<T> *current = last;
    while (current != nullptr)
    {
        std::cout << current->data << " ";
        current = current->prevlink;
    }
    std::cout << std::endl;
}

template <class T>
void Chain<T>::InsertAtHead(const T &e)
{
    ChainNode<T> *newNode = new ChainNode<T>(e, first, nullptr);
    if (first != nullptr)
        first->prevlink = newNode;
    else
        last = newNode; // 如果链表为空，last也应该指向新节点
    first = newNode;
}

template <class T>
void Chain<T>::InsertAtTail(const T &e)
{
    ChainNode<T> *newNode = new ChainNode<T>(e, nullptr, last);
    if (last != nullptr)
        last->nextlink = newNode;
    else
        first = newNode;
    last = newNode;
}

template <class T>
void Chain<T>::InsertAfter(ChainNode<T> *node, const T &e)
{
    if (node == nullptr)
        return;

    ChainNode<T> *newNode = new ChainNode<T>(e, node->nextlink, node);
    if (node->nextlink != nullptr)
        node->nextlink->prevlink = newNode;
    node->nextlink = newNode;
    if (node == last)
        last = newNode; // 如果插入的是最后一个节点，需要更新last
}

int main()
{
    Chain<int> chain;
    chain.Create2();        // 0 10 20 30
    chain.Display();        // 正向显示链表
    chain.DisplayReverse(); // 反向显示链表

    chain.InsertAtHead(100);
    chain.Display();
    chain.DisplayReverse();

    chain.InsertAtTail(200);
    chain.Display();
    chain.DisplayReverse();

    ChainNode<int> *node = chain.FindNode(20);
    chain.InsertAfter(node, 500);
    chain.Display();
    chain.DisplayReverse();

    return 0;
}
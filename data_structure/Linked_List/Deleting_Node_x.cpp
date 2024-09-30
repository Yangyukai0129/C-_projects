#include <iostream>

class Chain;
class ChainNode
{
    friend class Chain;

private:
    int data;
    ChainNode *link;

public:
    ChainNode(int element = 0, ChainNode *next = nullptr)
    {
        data = element;
        link = next;
    }
};

class Chain
{
private:
    ChainNode *first; // 在 Chain 類中定義 first 指針

public:
    Chain() : first(nullptr) {} // 構造函數初始化指針
    void Create2();
    void Create3();
    void Create4();
    ChainNode *FindNode(int value) const;
    void Delete10(ChainNode *x, ChainNode *y);
    void Display() const;
};

void Chain::Create2()
{
    ChainNode *second = new ChainNode(20, nullptr);
    first = new ChainNode(10, second);
}

void Chain::Create3()
{
    first = new ChainNode(30, first);
}

void Chain::Create4()
{
    first = new ChainNode(40, first);
}

ChainNode *Chain::FindNode(int value) const
{
    ChainNode *current = first;
    while (current != nullptr && current->data != value)
    {
        current = current->link;
    }
    return current;
}

void Chain::Delete10(ChainNode *x, ChainNode *y)
// x is after y
{
    if (x == first)
        first = first->link;
    else
        y->link = x->link;
    delete x;
}

void Chain::Display() const
{
    ChainNode *current = first;
    while (current != nullptr)
    {
        std::cout << current->data << " ";
        current = current->link;
    }
    std::cout << std::endl;
}

int main()
{
    Chain chain;
    chain.Create2();
    chain.Create3();
    chain.Create4();
    ChainNode *previousNode = chain.FindNode(30);
    ChainNode *nodeToDelete = chain.FindNode(10);

    if (nodeToDelete && previousNode)
    {
        chain.Delete10(nodeToDelete, previousNode); // 删除节点10
    }
    chain.Display(); // 顯示鏈表的內容
    return 0;
}
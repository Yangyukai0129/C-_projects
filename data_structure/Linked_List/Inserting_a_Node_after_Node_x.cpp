#include <iostream>

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
    void Insert50(ChainNode *x);
    void Display() const;
    ChainNode *GetFirst() const; // 新增函數，用於獲取鏈表中的第一個節點
    ChainNode *FindNode(int value) const;
};

void Chain::Create2()
{
    ChainNode *second = new ChainNode(20, nullptr);
    first = new ChainNode(10, second);
}

void Chain::Create3()
{
    first = new ChainNode(100, first);
}

void Chain::Insert50(ChainNode *x)
{
    if (first)
    {
        x->link = new ChainNode(50, x->link);
    }
    else
        first = new ChainNode(50);
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

ChainNode *Chain::GetFirst() const
{
    return first;
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

int main()
{
    Chain chain;
    chain.Create2();
    chain.Create3();

    // 获取链表中的第一个节点
    // ChainNode *node = chain.GetFirst();

    // 獲取鏈表中其中一個節點
    ChainNode *node = chain.FindNode(10);

    // 在这个节点后插入50
    chain.Insert50(node);

    // 显示链表的内容
    chain.Display(); // 應該顯示 "100 10 50 20"

    return 0;
}

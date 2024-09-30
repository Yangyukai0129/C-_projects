#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>

using namespace std;

class BST;
class TreeNode
{
    friend class BST;

private:
    TreeNode *leftChild;
    TreeNode *rightChild;
    TreeNode *parent;
    int key;
    int element;

public:
    // constructor
    TreeNode(TreeNode *left = 0, TreeNode *right = nullptr, TreeNode *parent = nullptr, int key = 0)
    {
        leftChild = left;
        rightChild = right;
        this->parent = parent; // 父節點
        // 單純數字排序，因此key=element
        this->key = key; // 决定了节点在树中的位置，并保证了二叉搜索树的有序性
        // element = element; // 實際數據
    }
    // instence
    TreeNode(int a) : leftChild(nullptr), rightChild(nullptr), parent(nullptr), key(a) {};
};

class BST
{
private:
    TreeNode *root;
    // 查找current節點最左邊的節點
    TreeNode *leftmost(TreeNode *current);
    // 排序後current節點的下一個節點，也就是他的後續節點
    TreeNode *successor(TreeNode *current);
    void PrintNode(TreeNode *node)
    {
        if (node != nullptr)
        {
            // 打印当前节点的 key
            cout << node->key << " ";

            // 打印左子节点的 key，若为空则打印 "null"
            if (node->leftChild != nullptr)
            {
                cout << setw(5) << node->leftChild->key << " ";
            }
            else
            {
                cout << setw(5) << "0" << " ";
            }

            // 打印右子节点的 key，若为空则打印 "null"
            if (node->rightChild != nullptr)
            {
                cout << setw(5) << node->rightChild->key << endl;
            }
            else
            {
                cout << setw(5) << "0" << endl;
            }

            // 递归处理左、右子节点
            PrintNode(node->leftChild);
            PrintNode(node->rightChild);
        }
    }
    void Preorder(TreeNode *currentNode)
    {
        if (currentNode)
        {
            cout << currentNode->key << " ";
            Preorder(currentNode->leftChild);
            Preorder(currentNode->rightChild);
        }
    }

public:
    BST() : root(0) {};
    TreeNode *&getRoot() { return root; } // 提供訪問 root 的方法
    void InsertBST(TreeNode *&node, TreeNode *parent, int key);
    void DeleteBST(TreeNode *&node, TreeNode *parent, int key);
    void PrintTree();
    void PrintPreorder();
};

// 查找当前节点的后继节点(實現inorder successor)
TreeNode *BST::successor(TreeNode *current)
{
    // 右子树有节点：如果当前节点有右子树，后继节点是右子树中的最左节点
    if (current->rightChild != nullptr)
    {
        return leftmost(current->rightChild);
    }

    // 右子树没有节点：在这种情况下，需要向上遍历，找到第一个比当前节点大的祖先节点
    // 也就是找到一个祖先节点，使得当前节点是其左子节点或没有祖先节点
    TreeNode *parent = current->parent;
    while (parent != nullptr && current == parent->rightChild)
    {
        current = parent;
        parent = parent->parent;
    }
    return parent;
}

// 查找最左边的节点
TreeNode *BST::leftmost(TreeNode *current)
{
    while (current->leftChild != nullptr)
    {
        current = current->leftChild;
    }
    return current;
}

void BST::InsertBST(TreeNode *&node, TreeNode *parent, int key)
{
    if (node == nullptr)
    {
        node = new TreeNode(nullptr, nullptr, parent, key);
    }
    else if (key < node->key)
    {
        InsertBST(node->leftChild, node, key);
    }
    else if (key > node->key)
    {
        InsertBST(node->rightChild, node, key);
    }
    // 代表存在此node，就進行刪除
    else
    {
        DeleteBST(node, parent, key);
    }
}

// 删除节点
void BST::DeleteBST(TreeNode *&node, TreeNode *parent, int key)
{
    if (node == nullptr)
    {
        // 节点不存在
        return;
    }

    if (key < node->key)
    {
        // 在左子树中查找
        DeleteBST(node->leftChild, node, key);
    }
    else if (key > node->key)
    {
        // 在右子树中查找
        DeleteBST(node->rightChild, node, key);
    }
    else
    {
        // 找到要删除的节点
        if (node->leftChild == nullptr && node->rightChild == nullptr)
        {
            // 情况 1: 节点是叶子节点
            delete node;
            node = nullptr;
        }
        else if (node->leftChild == nullptr || node->rightChild == nullptr)
        {
            // 情况 2: 节点有一个子节点
            TreeNode *child = (node->leftChild != nullptr) ? node->leftChild : node->rightChild;
            TreeNode *temp = node;
            node = child;
            node->parent = parent;
            delete temp;
        }
        else
        {
            // 情况 3: 节点有两个子节点
            TreeNode *successorNode = successor(node);
            node->key = successorNode->key;
            DeleteBST(node->rightChild, node, successorNode->key);
        }
    }
}

void BST::PrintTree()
{
    cout << "node  left  right" << endl;
    PrintNode(root);
}

void BST::PrintPreorder()
{
    cout << "Preorder:" << endl;
    Preorder(root);
}

int main()
{
    BST tree;
    string input;

    cout << "Enter the numbers separated by spaces: ";
    getline(cin, input);

    stringstream ss(input);
    int number;

    while (ss >> number)
    {
        tree.InsertBST(tree.getRoot(), nullptr, number);
    }

    std::cout << "Tree Structure:" << std::endl;
    tree.PrintTree();

    tree.PrintPreorder();

    return 0;
}
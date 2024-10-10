#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <iomanip> //for std::setw()

class Graph
{
private:
    int num_vertex;
    std::vector<std::list<int>> AdjList;

    int *color; // visited情況 0:還沒找到過 1:找到但還在recursive 2:結束
    int *discover;
    int *finish;
    int *predecessor;

public:
    Graph() : num_vertex(0) {};
    Graph(int N) : num_vertex(N)
    {
        AdjList.resize(num_vertex);
    };
    ~Graph()
    {
        delete[] color;
        delete[] discover;
        delete[] finish;
        delete[] predecessor;
    }
    void AddEdgeList(int from, int to);
    void DFS(int Start);
    void DFSVisit(int vertex, int &time);
};

void Graph::AddEdgeList(int from, int to)
{
    AdjList[from].push_back(to);
}

void Graph::DFS(int Start)
{
    // 配置記憶體位置
    color = new int[num_vertex];
    discover = new int[num_vertex];
    finish = new int[num_vertex];
    predecessor = new int[num_vertex];

    // 初始化
    int time = 0;
    for (int i = 0; i < num_vertex; i++)
    {
        color[i] = 0;
        discover[i] = 0;
        finish[i] = 0;
        predecessor[i] = -1;
    }

    int i = Start;
    for (int j = 0; j < num_vertex; j++) // 檢查所有Graph中的vertex都要被搜尋到
    {
        if (color[i] == 0) // 若vertex還沒找到過, 則進行以該vertex作為起點之搜尋
        {
            DFSVisit(i, time);
        }
        i = j; // j會把AdjList完整走過一遍, 確保所有vertex都被搜尋過
    }

    // after for loop
    std::cout << "predecessor:" << std::endl; // 印出 A(0) ~ H(7)的predecessor
    for (int i = 0; i < num_vertex; i++)
    {
        std::cout << std::setw(4) << i;
    }
    std::cout << std::endl;
    for (int i = 0; i < num_vertex; i++)
    {
        std::cout << std::setw(4) << predecessor[i];
    }
    std::cout << "\ndiscover time:" << std::endl; // 印出 A(0) ~ H(7)的discover time
    for (int i = 0; i < num_vertex; i++)
    {
        std::cout << std::setw(4) << i;
    }
    std::cout << std::endl;
    for (int i = 0; i < num_vertex; i++)
    {
        std::cout << std::setw(4) << discover[i];
    }
    std::cout << "\nfinish time:" << std::endl; // 印出 A(0) ~ H(7)的finish time
    for (int i = 0; i < num_vertex; i++)
    {
        std::cout << std::setw(4) << i;
    }
    std::cout << std::endl;
    for (int i = 0; i < num_vertex; i++)
    {
        std::cout << std::setw(4) << finish[i];
    }
}

void Graph::DFSVisit(int vertex, int &time) // 一旦有vertex被發現而且還沒找到過, 便進入DFSVisit()
{
    color[vertex] = 1;         // 找到但還在recursive
    discover[vertex] = ++time; // 更新vertex的discover時間
    for (std::list<int>::iterator itr = AdjList[vertex].begin(); itr != AdjList[vertex].end(); itr++)
    {
        if (color[*itr] == 0) // 若搜尋到還沒找到過的vertex
        {
            predecessor[*itr] = vertex; // 更新其predecessor
            DFSVisit(*itr, time);       // 立刻以其作為新的搜尋起點, 進入新的DFSVisit()
        }
    }
    color[vertex] = 2;       // 當vertex已經搜尋過所有與之相連的vertex後, 結束
    finish[vertex] = ++time; // 並更新finish時間
}

int main()
{
    // 定義一個具有八個vertex的Graph
    Graph g2(8);
    g2.AddEdgeList(0, 1);
    g2.AddEdgeList(0, 2);
    g2.AddEdgeList(1, 3);
    g2.AddEdgeList(2, 1);
    g2.AddEdgeList(2, 5);
    g2.AddEdgeList(3, 4);
    g2.AddEdgeList(3, 5);
    // AdjList[4] is empty
    g2.AddEdgeList(5, 1);
    g2.AddEdgeList(6, 4);
    g2.AddEdgeList(6, 7);
    g2.AddEdgeList(7, 6);

    g2.DFS(0); // 以vertex(0), 也就是vertex(A作為DFS()的起點

    return 0;
}
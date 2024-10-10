#include <iostream>
#include <vector>
#include <list>
#include <queue>

class Graph
{
private:
    int num_vertex;                      // 總共有幾個vertex
    std::vector<std::list<int>> AdjList; // 將AdjList包在vector裡面可以更好進行動態記憶體分配

    // 由於 num_vertex 的值在運行時才確定，因此需要動態分配記憶體來存儲與之相關的數據
    int *color,       // visited情況 0:還沒找到過 1:找到並push queue 2:找到後pop queue
        *distance,    // 距離起點的位置,0:起點 無限大:從起點走不到vertex
        *predecessor; // -1:沒有predecessor，表示為起點vertex
public:
    Graph() : num_vertex(0) {};  // default constructor
    Graph(int N) : num_vertex(N) // constructor with input: number of vertex
    {
        // initial Adjacency List
        AdjList.resize(num_vertex);
    };
    ~Graph()
    {
        delete[] color;
        delete[] distance;
        delete[] predecessor;
    }
    void AddEdgeList(int from, int to);
    void BFS(int Start);
    void printAdjList();
};

// vertex之間的edge
void Graph::AddEdgeList(int from, int to)
{
    AdjList[from].push_back(to);
}

void Graph::BFS(int Start)
{
    // 動態記憶體分配
    color = new int[num_vertex];
    distance = new int[num_vertex];
    predecessor = new int[num_vertex];

    // 初始化
    for (int i = 0; i < num_vertex; i++)
    {
        color[i] = 0;                 // 還沒找到過
        predecessor[i] = -1;          // -1表示沒有predecessor
        distance[i] = num_vertex + 1; // num_vertex個vertex,最長距離 distance = num_vertex -1條edge
    }

    std::queue<int> q;
    int i = Start;

    // 開始遍歷
    for (int j = 0; j < num_vertex; j++) // j從0數到num_vertex-1, 因此j會走過graph中所有vertex
    {
        if (color[i] == 0) // 第一次i會是起點vertex
        {
            color[i] = 1;        // visited情況(找到並push queue)
            distance[i] = 0;     // 距起點位置為0
            predecessor[i] = -1; // 是起點所以predecessor為-1
            q.push(i);           // push queue
        }
        while (!q.empty())
        {
            // u 與 AdjList[u] 的區別
            // u 是當前正在被處理的節點，它是從 BFS 隊列中取出的節點。在每次迭代中，u 代表著 BFS 當前的探索點。
            // AdjList[u] 是與節點 u 直接相連的所有鄰居節點的列表。它包含了所有可以從 u 移動到的節點，即所有與 u 有邊相連的節點。
            int u = q.front(); // 取出隊列的最前端元素 u，作為當前處理的節點
            for (std::list<int>::iterator itr = AdjList[u].begin(); itr != AdjList[u].end(); itr++)
            {
                if (color[*itr] == 0) // 若被「找到」的vertex是0
                {
                    color[*itr] = 1;                  // visited情況(找到並push queue)
                    distance[*itr] = distance[u] + 1; // 距離為前一個vertex的距離+1
                    predecessor[*itr] = u;            // predecesor為前一個vertex
                    q.push(*itr);                     // push queue
                }
            }
            q.pop();      // 把u移出queue
            color[u] = 2; // visited情況(找到並pop queue)
        }
        // 若一次回圈沒有把所有vertex走過, 表示graph有多個connected component
        // 就把i另成j, 繼續檢查graph中的其他vertex是否仍是白色, 若是, 重複while loop
        i = j;
    }
}

int main()
{
    // 創建一個有9個頂點的圖
    Graph g1(9);
    // 建立adjacency list
    g1.AddEdgeList(0, 1);
    g1.AddEdgeList(0, 2);
    g1.AddEdgeList(0, 3);
    g1.AddEdgeList(1, 0);
    g1.AddEdgeList(1, 4);
    g1.AddEdgeList(2, 0);
    g1.AddEdgeList(2, 4);
    g1.AddEdgeList(2, 5);
    g1.AddEdgeList(2, 6);
    g1.AddEdgeList(2, 7);
    g1.AddEdgeList(3, 0);
    g1.AddEdgeList(3, 7);
    g1.AddEdgeList(4, 1);
    g1.AddEdgeList(4, 2);
    g1.AddEdgeList(4, 5);
    g1.AddEdgeList(5, 2);
    g1.AddEdgeList(5, 4);
    g1.AddEdgeList(5, 8);
    g1.AddEdgeList(6, 2);
    g1.AddEdgeList(6, 7);
    g1.AddEdgeList(6, 8);
    g1.AddEdgeList(7, 2);
    g1.AddEdgeList(7, 3);
    g1.AddEdgeList(7, 6);
    g1.AddEdgeList(8, 5);
    g1.AddEdgeList(8, 6);

    g1.BFS(0); // 從頂點0開始遍歷

    return 0;
}
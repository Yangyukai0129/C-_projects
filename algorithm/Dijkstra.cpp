#include <iostream>
// 定義無限大
#define INF 0x3f3f3f3f
// 定義有幾個點
#define V_COUNT 6

int adj[V_COUNT][V_COUNT];

void print_answer(int *L)
{
    std::cout << "Vertex Distance form Source\n";
    for (int i = 0; i < V_COUNT; i++)
    {
        std::cout << i << "\t\t" << L[i] << "\n";
    }
}

// 初始化相鄰陣列(Adjacency Array)都是沒有邊的情況
void init_adj()
{
    for (int i = 0; i < V_COUNT; i++)
    {
        for (int j = 0; j < V_COUNT; j++)
        {
            adj[i][j] = INF;
        }
    }
}

// 加入邊的權重(距離)
void addEdge(int u, int v, int w)
{
    adj[u][v] = w;
    adj[v][u] = w;
}

// 初始化圖
void init_graph()
{
    init_adj();

    addEdge(0, 1, 1);
    addEdge(0, 2, 6);
    addEdge(1, 2, 3);
    addEdge(1, 3, 4);
    addEdge(1, 4, 6);
    addEdge(2, 3, 2);
    addEdge(2, 4, 2);
    addEdge(3, 5, 3);
    addEdge(3, 4, 2);
    addEdge(4, 5, 4);
}

void initial(int *L_table, int *S)
{
    // 初始化S集合，0代表還沒在S集合內
    for (int i = 0; i < V_COUNT; i++)
    {
        S[i] = 0;
    }
    // 將v0放入S集合
    S[0] = 1;

    // 初始化L
    for (int i = 0; i < V_COUNT; i++)
    {
        L_table[i] = INF;
    }
    // v0到自身距離為0
    L_table[0] = 0;

    // 如果v_0與v_i有邊，則將此邊距離暫時作為到v_i所花費的距離，若沒有則代表距離無限
    for (int i = 1; i < V_COUNT; i++)
    {
        if (adj[0][i] != INF)
        {
            L_table[i] = adj[0][i];
        }
        else
        {
            L_table[i] = INF;
        }
    }
}

int chose_u_smallest(int *S, int *L_table)
{
    int min = INF; // 儲存當前找到的最小距離，初始值為INF
    int flag = 0;  // 標記是否找到符合條件的節點，找到最小距離的節點則設置為1
    int vertex;    // 紀錄當前找到距離最小的節點

    // 找最小距離
    for (int i = 1; i < V_COUNT; i++)
    {
        if (S[i] == 0 && L_table[i] < min)
        {
            flag = 1;
            min = L_table[i];
            vertex = i;
        }
    }

    if (flag)
    {
        // 將選中的vertex加入集合S
        S[vertex] = 1;
        // 返回該節點vertex，他是當前距離源節點最近的節點
        return vertex;
    }
    else
    {
        // V-S集合為空，表示沒有剩餘的節點
        return -1;
    }
}

void renew_distance(int *L, int *S)
{
    int vertex;
    while (true)
    {
        // 獲取最小距離的節點
        vertex = chose_u_smallest(S, L);
        if (vertex == -1)
            break;

        // 更新最短路徑表
        for (int i = 1; i < V_COUNT; i++)
        {
            if (i != vertex) // i != vertex是為了避免更新源節點本身
            {
                int new_distance = L[vertex] + adj[vertex][i];
                if (L[i] > new_distance)
                    L[i] = new_distance;
            }
        }
    }
}

int main()
{
    int S_set[V_COUNT];
    int L_table[V_COUNT];
    init_graph();
    initial(L_table, S_set);
    renew_distance(L_table, S_set);
    print_answer(L_table);

    return 0;
}
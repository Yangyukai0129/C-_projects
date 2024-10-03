#include <iostream>
#include <cstring>

#define N 4

// 用來判斷女生'm'偏好男生'm1'更慎'm'，如果是返回true
bool wPrefersM1OverM(int wPreferenceRank[N][N], int w, int m, int m1)
{
    return wPreferenceRank[w][m1] < wPreferenceRank[w][m];
}

// 打印stable maching的N位男生和N位女生
void stableMarriage(int prefer[2 * N][N])
{
    // 陣列儲存女生的未婚夫
    int wPartner[N];

    // 陣列儲存是否還有男生沒有未婚妻
    bool mFree[N];

    // 將女生陣列做一個ranking list，這樣之後進行偏好比較的時候Big O就會一直是O(1)
    // wPreferenceRank[i][j] represents woman i's preference ranking of man j
    int wPreferenceRank[N][N];
    for (int w = 0; w < N; w++)
    {
        for (int rank = 0; rank < N; rank++)
        {
            wPreferenceRank[w][prefer[w + N][rank]] = rank;
        }
    }

    // 初始化所有的男生和女生都是單身
    std::memset(wPartner, -1, sizeof(wPartner));
    std::memset(mFree, false, sizeof(mFree));
    int freeCount = N;

    // 當有男生是單身時，會一直進行迴圈
    while (freeCount > 0)
    {
        int m;
        // 遍歷找尋單身的男生
        for (m = 0; m < N; m++)
        {
            // ==false代表單身，進行後續邏輯
            if (mFree[m] == false)
                break;
        }

        // 如果男生的偏好超過N或男生不是單身則停止迴圈
        for (int i = 0; i < N && mFree[m] == false; i++)
        {
            // w代表男生正在求婚的女生對象
            int w = prefer[m][i];

            // wPartner[w-N]代表，w女生是否有對象
            // 因為女生數字接在男生後面(0~3為男，4~7為女)，因此要確認女生是否有未婚妻要去wPartner確認該女是否為-1，
            // w - N 的作用是将女生的索引从 prefer 数组转换为 wPartner 数组中的正确索引
            if (wPartner[w - N] == -1)
            {
                wPartner[w - N] = m;
                mFree[m] = true;
                freeCount--;
            }
            else
            {
                // 如果該女已經有對象，則確認目前的對象跟正在求婚的對象哪個偏好比較高
                int m1 = wPartner[w - N];

                // 如果女生比較喜歡求婚對象，則m為女生的現任未婚夫，m1則為單身
                if (!wPrefersM1OverM(wPreferenceRank, w - N, m, m1))
                {
                    wPartner[w - N] = m;
                    mFree[m] = true;
                    mFree[m1] = false;
                }
            }
            // 如果更喜歡m1更甚於m，則不用判斷，因為我們已經知道 w 的選擇
        }
    }

    std::cout << "Woman  Man" << std::endl;
    for (int i = 0; i < N; i++)
    {
        std::cout << " " << i + N << "\t" << wPartner[i] << std::endl;
    }
}

int main()
{
    // 前四個為男生，後四個為女生
    // 如果要更多人則男女比例是1:1
    int prefer[2 * N][N] = {
        {7, 5, 6, 4},
        {5, 4, 6, 7},
        {4, 5, 6, 7},
        {4, 5, 6, 7},
        {0, 1, 2, 3},
        {0, 1, 2, 3},
        {0, 1, 2, 3},
        {0, 1, 2, 3},
    };

    stableMarriage(prefer);

    return 0;
}
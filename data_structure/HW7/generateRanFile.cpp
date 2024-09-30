#include <fstream>
#include <iostream>
#include <random>
#include <vector>

int getRandom(int range)
{
    // 用於生成隨機數的種子
    std::random_device rd;
    // 用於提供隨機種子
    std::mt19937_64 mt_rand(rd());
    // 生成一個範圍在 0 到 range-1 之間的隨機數
    return mt_rand() % range;
}

int main()
{
    std::ofstream file;
    // 打開文件，後面是打開模式
    file.open("input.txt", std::ios::out);

    std::vector<int> scale = {100, 500, 1000, 5000, 10000, 50000, 100000, 500000};
    for (auto i : scale)
    {
        // 將數組大小寫入文件
        file << i << std::endl;
        for (int j = 0; j < i; j++)
            // 將 i 作為參數，生成範圍在 0 到 i-1 的隨機數並寫入文件
            file << getRandom(i) << std::endl;
    }

    file.close();
    return 0;
}
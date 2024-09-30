#include <iostream>

#define MaxTerms 100

class SparseMatrix;
class MatrixTerm
{
    friend class SparseMatrix;

private:
    int row;
    int col;
    int value;
};

class SparseMatrix
{
private:
    int Rows;                     // matrix row總數
    int Cols;                     // matrix col總數
    int Terms;                    // matrix不等於0的元素
    int capacity;                 // array總容量
    MatrixTerm smArray[MaxTerms]; // 存储非零元素的数组

public:
    SparseMatrix(int r = 0, int c = 0, int cap = MaxTerms) : Rows(r), Cols(c), Terms(0), capacity(r * c) {};
    SparseMatrix Transpose();
    // 打印矩阵的方法
    void printMatrix() const
    {
        for (int i = 0; i < Terms; i++)
        {
            std::cout << "Row: " << smArray[i].row << ", Col: " << smArray[i].col << ", Value: " << smArray[i].value << std::endl;
        }
    }
    // 添加元素的方法
    void addElement(int r, int c, int val)
    {
        if (Terms >= capacity)
        {
            std::cerr << "Matrix capacity is full. Cannot add more elements." << std::endl;
            return;
        }
        if (val == 0)
        {
            std::cerr << "Cannot add zero value." << std::endl;
            return;
        }
        smArray[Terms].row = r;
        smArray[Terms].col = c;
        smArray[Terms].value = val;
        Terms++;
    }
};
SparseMatrix SparseMatrix::Transpose()
{
    SparseMatrix b;
    b.Rows = Cols;
    b.Cols = Rows;
    b.Terms = Terms;
    b.capacity = capacity;
    if (Terms > 0) // 檢查原矩陣是否有非零元素
    {
        int CurrentB = 0;              // 初始化transpose矩陣中當前元素的位置
        for (int c = 0; c < Cols; c++) // 遍歷每一列
        {
            for (int i = 0; i < Terms; i++) // 遍歷所有非零元素
            {
                if (smArray[i].col == c) // 檢查當前元素是否在第c列，確保在轉換後數據是依照順序排列
                {
                    b.smArray[CurrentB].row = smArray[i].col;
                    b.smArray[CurrentB].col = smArray[i].row;
                    b.smArray[CurrentB].value = smArray[i].value;
                    CurrentB++;
                }
            }
        }
    }
    return b;
}

int main()
{
    SparseMatrix sm(3, 3); // 创建一个3x3的稀疏矩阵

    sm.addElement(0, 0, 1);
    sm.addElement(0, 1, 2);
    sm.addElement(1, 0, 3);

    std::cout << "Original matrix:\n";
    sm.printMatrix();

    SparseMatrix transposed = sm.Transpose();

    std::cout << "Transposed matrix:\n";
    transposed.printMatrix();
    return 0;
}
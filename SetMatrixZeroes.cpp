/*
    73. 矩阵置零
    给定一个 m x n 的矩阵，如果一个元素为 0 ，则将其所在行和列的所有元素都设为 0 。请使用 原地 算法。

    示例 1：
    输入：matrix = [[1,1,1],[1,0,1],[1,1,1]]
    输出：[[1,0,1],[0,0,0],[1,0,1]]

    示例 2：
    输入：matrix = [[0,1,2,0],[3,4,5,2],[1,3,1,5]]
    输出：[[0,0,0,0],[0,4,5,0],[0,3,1,0]]

*/

#include <vector>


void setZeroes(std::vector<std::vector<int>>& matrix) 
{    
    std::vector<size_t> zeroRows;
    std::vector<size_t> zeroCols;
    for(size_t i = 0; i < std::size(matrix); ++i){
        for(size_t j = 0; j < std::size(matrix[i]); ++j){
            if(matrix[i][j] == 0){
                zeroRows.emplace_back(i);
                zeroCols.emplace_back(j);
            }
        }
    }

    for(auto& rowIndex : zeroRows){
        for(auto& val : matrix[rowIndex]){
            val = 0;
        }
    }

    for(auto& colIndex : zeroCols){
        for(size_t i = 0; i < std::size(matrix); ++i){
            matrix[i][colIndex] = 0;
        }
    }
}

int main()
{
    return 0;
}
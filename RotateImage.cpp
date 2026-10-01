/*
    48. 旋转图像
    给定一个 n × n 的二维矩阵 matrix 表示一个图像。请你将图像顺时针旋转 90 度。
    你必须在 原地 旋转图像，这意味着你需要直接修改输入的二维矩阵。请不要 使用另一个矩阵来旋转图像。

    示例 1：
    输入：matrix = [[1,2,3],[4,5,6],[7,8,9]]
    输出：[[7,4,1],[8,5,2],[9,6,3]]
    
    示例 2：
    输入：matrix = [[5,1,9,11],[2,4,8,10],[13,3,6,7],[15,14,12,16]]
    输出：[[15,13,2,5],[14,3,4,1],[12,6,8,9],[16,7,10,11]]

    提示：
    n == matrix.length == matrix[i].length
    1 <= n <= 20
    -1000 <= matrix[i][j] <= 1000
*/

#include <vector>
#include <print>
#include <ranges>
#include <algorithm>

void printMatrix(const std::vector<std::vector<int>>& matrix)
{
    for(const auto& row : matrix){
        for(const auto& col : row){
            std::print("{} ", col);
        }
        std::print("\n");
    }
}

template <std::size_t Version>
void rotate(std::vector<std::vector<int>>& matrix);

template<>
void rotate<0>(std::vector<std::vector<int>>& matrix)
{
    std::vector<std::vector<int>> tmp(matrix.size(), std::vector<int>(matrix.size()));
    for(const auto& [rowIndex, row] : matrix | std::views::enumerate){
        for(const auto& [colIndex, col] : row | std::views::enumerate){
            tmp[colIndex][matrix.size() - 1 - rowIndex] = col;
        }
    }
    matrix = tmp;
}

template<>
void rotate<1>(std::vector<std::vector<int>>& matrix)
{
    for(int i = 0; i < matrix.size(); ++i){
        for(int j = i + 1; j < matrix.size(); ++j){
            std::swap(matrix[i][j], matrix[j][i]);
        }
    }
    for(auto& row : matrix){
        std::ranges::reverse(row);
    }
}

int main()
{
    std::vector<std::vector<int>> matrix = {{1,2,3},{4,5,6},{7,8,9}};
    printMatrix(matrix);
    rotate<1>(matrix);
    printMatrix(matrix);
    return 0;
}
/*
    74. 搜索二维矩阵
    给你一个满足下述两条属性的 m x n 整数矩阵：
    每行中的整数从左到右按非严格递增顺序排列。
    每行的第一个整数大于前一行的最后一个整数。
    给你一个整数 target ，如果 target 在矩阵中，返回 true ；否则，返回 false 。
    你必须编写一个时间复杂度为 O(log(m * n)) 的解决方案。

    示例 1：
    输入：matrix = [[1,3,5,7],
                    [10,11,16,20],
                    [23,30,34,60]], target = 3
    输出：true

    示例 2：
    输入：matrix = [[1,3,5,7],
                    [10,11,16,20],
                    [23,30,34,60]], target = 13
    输出：false

    提示：
    m == matrix.length
    n == matrix[i].length
    1 <= m, n <= 100
    -104 <= matrix[i][j], target <= 104
*/

#include <vector>
#include <ranges>
#include <print>
#include <algorithm>

template <std::size_t Version>
bool searchMatrix(std::vector<std::vector<int>>& matrix, int target);

template<>
bool searchMatrix<0>(std::vector<std::vector<int>>& matrix, int target)
{
    if (matrix.empty() || matrix.front().empty())
        return false;

    const int cols = static_cast<int>(matrix.front().size());
    const int total = static_cast<int>(matrix.size()) * cols;

    auto flat = std::views::iota(0, total)
        | std::views::transform(
            [&matrix, cols](int i) -> const int& {
                return matrix[i / cols][i % cols];
            });
    return std::ranges::binary_search(flat, target);
}

template<>
bool searchMatrix<1>(std::vector<std::vector<int>>& matrix, int target)
{
    if (matrix.empty() || matrix.front().empty())
        return false;

    auto it = std::ranges::upper_bound(matrix, target, {}, 
        [](const std::vector<int>& row) { 
            return row.front(); 
        });
    if(it == matrix.begin())
        return false;
    return std::ranges::binary_search(*std::prev(it), target);
}

int main()
{
    constexpr std::size_t version = 1;
    std::vector<std::vector<int>> matrix0 = {
        {1, 3, 5, 7},
        {10, 11, 16, 20},
        {23, 30, 34, 60}
    };
    std::println("Matrix 0: {}", searchMatrix<version>(matrix0, 3));
    std::vector<std::vector<int>> matrix1 = {
        {1, 3, 5, 7},
        {10, 11, 16, 20},
        {23, 30, 34, 60}
    };
    std::println("Matrix 1: {}", searchMatrix<version>(matrix1, 13));
    std::vector<std::vector<int>> matrix2 = {
        {1,3,5,7},
        {10,11,16,20},
        {23,30,34,60}
    };
    std::println("Matrix 2: {}", searchMatrix<version>(matrix2, 3));
    return 0;
}
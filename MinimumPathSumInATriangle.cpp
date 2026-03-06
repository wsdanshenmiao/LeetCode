/*
    120. 三角形最小路径和
    给定一个三角形 triangle ，找出自顶向下的最小路径和。
    每一步只能移动到下一行中相邻的结点上。相邻的结点 在这里指的是下标与上一层结点下标
    相同或者等于上一层结点下标 + 1 的两个结点。也就是说，如果正位于当前行的下标 i ，
    那么下一步可以移动到下一行的下标 i 或 i + 1 。

    示例 1：
    输入：triangle = [[2],[3,4],[6,5,7],[4,1,8,3]]
    输出：11
    解释：如下面简图所示：
    2
    3 4
    6 5 7
    4 1 8 3
    自顶向下的最小路径和为 11（即，2 + 3 + 5 + 1 = 11）。

    示例 2：
    输入：triangle = [[-10]]
    输出：-10

    提示：
    1 <= triangle.length <= 200
    triangle[0].length == 1
    triangle[i].length == triangle[i - 1].length + 1
    -104 <= triangle[i][j] <= 104

    进阶：
    你可以只使用 O(n) 的额外空间（n 为三角形的总行数）来解决这个问题吗？
*/

#include <vector>
#include <span>
#include <array>
#include <unordered_map>

// int minimumTotal(std::span<std::vector<int>> triangle, int index, std::vector<std::vector<int>>& cache)
// {
//     auto size = triangle.size();
//     if(size <= 1){
//         // 只有一行，直接返回最小值
//         return triangle.empty() ? 0 : *std::ranges::min_element(triangle[0]);
//     }
//     else{
//         int min = std::numeric_limits<int>::max();
//         // 获取上一行对应元素的最小路径和，并取最小值
//         if(index < triangle.back().size() - 1){
//             if(cache[size - 1][index] != std::numeric_limits<int>::max()){
//                 min = std::min(min, cache[size - 1][index]);
//             }
//             else{
//                 cache[size - 1][index] = minimumTotal(triangle.first(size - 1), index, cache);
//                 min = std::min(min, cache[size - 1][index]);
//             }
//         }
//         // 获取上一行对应元素的前一个元素的最小路径和，并取最小值
//         if(index > 0){
//             if(cache[size - 1][index - 1] != std::numeric_limits<int>::max()){
//                 min = std::min(min, cache[size - 1][index - 1]);
//             }
//             else{
//                 cache[size - 1][index - 1] = minimumTotal(triangle.first(size - 1), index - 1, cache);
//                 min = std::min(min, cache[size - 1][index - 1]);
//             }
//         }
//         // 加上当前元素的值
//         return min + triangle.back()[index];
//     }
// }

// // 将问题拆分为子问题
// // 若要求到达指定元素的最小路径和，可通过求得上一行可到达当前元素的元素的最小路径和来得到
// // 通过递归的方式求解子问题，并使用缓存来避免重复计算
// // 终止条件为只有一行时，直接返回最小值
// // 状态转移方程为：minPathSum(i, j) = min(minPathSum(i - 1, j), minPathSum(i - 1, j - 1)) + triangle[i][j]
// int minimumTotal(std::vector<std::vector<int>>& triangle)
// {
//     if(triangle.empty()){
//         return 0;
//     }
//     auto backSize = triangle.back().size();
//     int min = std::numeric_limits<int>::max();
//     std::vector<std::vector<int>> cache(triangle.size(), 
//         std::vector<int>(backSize, std::numeric_limits<int>::max()));
//     // 计算最后一行每个元素的最小路径和，取最小值
//     for(size_t i = 0; i < backSize; ++i){
//         min = std::min(min, minimumTotal(triangle, i, cache));
//     }
//     return min;
// }

// int minimumTotal(std::vector<std::vector<int>>& triangle)
// {
//     if(triangle.empty()){
//         return 0;
//     }
//     auto size = triangle.size();
//     std::array<std::vector<int>, 2> cache({std::vector<int>(size), std::vector<int>(size)});
//     cache[0][0] = triangle[0][0];
//     for(size_t i = 1; i < size; ++i){
//         size_t currIndex = i % 2;
//         size_t prevIndex = (i - 1) % 2;
//         cache[currIndex][0] = cache[prevIndex][0] + triangle[i][0];
//         for(size_t j = 1; j < i; ++j){
//             cache[currIndex][j] = std::min(cache[prevIndex][j], cache[prevIndex][j - 1]) + triangle[i][j];
//         }
//         cache[currIndex][i] = cache[prevIndex][i - 1] + triangle[i][i];
//     }
//     return *std::ranges::min_element(cache[(size - 1) % 2]);
// }

int minimumTotal(std::vector<std::vector<int>>& triangle)
{
    if(triangle.empty()){
        return 0;
    }
    auto size = triangle.size();
    std::vector<int> cache(size);
    cache[0] = triangle[0][0];
    for(size_t i = 1; i < size; ++i){
        cache[i] = cache[i - 1] + triangle[i][i];
        for(ptrdiff_t j = i - 1; j > 0; --j){
            cache[j] = std::min(cache[j], cache[j - 1]) + triangle[i][j];
        }
        cache[0] += triangle[i][0];
    }
    return *std::ranges::min_element(cache);
}

int main()
{
    std::vector<std::vector<int>> triangle = {
        {0},
        {0, 0},
        {0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    };
    printf("%d\n", minimumTotal(triangle));
    return 0;
}
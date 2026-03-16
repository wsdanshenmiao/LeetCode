/*
    63. 不同路径 II
    给定一个 m x n 的整数数组 grid。一个机器人初始位于 左上角（即 grid[0][0]）。
    机器人尝试移动到 右下角（即 grid[m - 1][n - 1]）。机器人每次只能向下或者向右移动一步。
    网格中的障碍物和空位置分别用 1 和 0 来表示。机器人的移动路径中不能包含 任何 有障碍物的方格。
    返回机器人能够到达右下角的不同路径数量。
    测试用例保证答案小于等于 2 * 109。

    示例 1：
    输入：obstacleGrid = [[0,0,0],[0,1,0],[0,0,0]]
    输出：2
    解释：3x3 网格的正中间有一个障碍物。
    从左上角到右下角一共有 2 条不同的路径：
    1. 向右 -> 向右 -> 向下 -> 向下
    2. 向下 -> 向下 -> 向右 -> 向右
    
    示例 2：
    输入：obstacleGrid = [[0,1],[0,0]]
    输出：1
*/

#include <vector>
#include <stack>

// int uniquePathsWithObstacles(std::vector<std::vector<int>>& obstacleGrid)
// {
//     if(std::empty(obstacleGrid))
//         return 0;

//     size_t count = 0;
//     auto dfs = [&count](auto&& dfs, const auto& grid, int i, int j){
//         // 若当前被遮挡则无法到达
//         if(grid[i][j] == 1)
//             return;

//         // 已经到达右下角，记录路径数量
//         if(i == std::size(grid) - 1 && j == std::size(grid[0]) - 1) {
//             ++count;
//             return;
//         }

//         if(i < std::size(grid) - 1 && grid[i + 1][j] != 1)
//             dfs(dfs, grid, i + 1, j);
//         if(j < std::size(grid[0]) - 1 && grid[i][j + 1] != 1)
//             dfs(dfs, grid, i, j + 1);
//     };
//     dfs(dfs, obstacleGrid, 0, 0);

//     return count;
// }

// int uniquePathsWithObstacles(std::vector<std::vector<int>>& obstacleGrid)
// {
//     if(std::empty(obstacleGrid))
//         return 0;

//     std::stack<std::pair<int, int>> stk;
//     stk.emplace(0, 0);
//     size_t count = 0;
//     while(!std::empty(stk)) {
//         auto [i, j] = stk.top();
//         stk.pop();

//         // 若当前被遮挡则无法到达
//         if(obstacleGrid[i][j] == 1)
//             continue;

//         if(i == std::size(obstacleGrid) - 1 && j == std::size(obstacleGrid[0]) - 1) {
//             ++count;
//             continue;
//         }

//         if(i < std::size(obstacleGrid) - 1)
//             stk.emplace(i + 1, j);
//         if(j < std::size(obstacleGrid[0]) - 1)
//             stk.emplace(i, j + 1);
//     }
//     return count;
// }

int uniquePathsWithObstacles(std::vector<std::vector<int>>& obstacleGrid)
{
    if(std::empty(obstacleGrid))
        return 0;

    for(size_t i = 0; i < std::size(obstacleGrid); ++i){
        if(obstacleGrid[i][0] == 1){
            break;
        }
        obstacleGrid[i][0] = 11;
    }
    for(size_t i = 0; i < std::size(obstacleGrid[0]); ++i){
        if(obstacleGrid[0][i] == 1){
            break;
        }
        obstacleGrid[0][i] = 11;
    }
    for(size_t i = 1; i < std::size(obstacleGrid); ++i){
        for(size_t j = 1; j < std::size(obstacleGrid[i]); ++j){
            // 若当前被遮挡则无法到达
            if(obstacleGrid[i][j] != 1 && (obstacleGrid[i - 1][j] > 1 || obstacleGrid[i][j - 1] > 1)) {
                obstacleGrid[i][j] = obstacleGrid[i - 1][j] > 1 ? (obstacleGrid[i - 1][j] - 10) : 0;
                obstacleGrid[i][j] += (obstacleGrid[i][j - 1] > 1 ? (obstacleGrid[i][j - 1] - 10) : 0) + 10;
            }
        }
    }

    return std::max(0, obstacleGrid.back().back() - 10);
}

int main()
{
    std::vector<std::vector<int>> obstacleGrid1 = {
        {1, 0}
    };
    std::printf("%d\n", uniquePathsWithObstacles(obstacleGrid1)); // 2
    return 0;
}
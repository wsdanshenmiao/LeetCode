/*
    200. 岛屿数量
    给你一个由 '1'（陆地）和 '0'（水）组成的的二维网格，请你计算网格中岛屿的数量。
    岛屿总是被水包围，并且每座岛屿只能由水平方向和/或竖直方向上相邻的陆地连接形成。
    此外，你可以假设该网格的四条边均被水包围。
    
    示例 1：
    输入：grid = [
    ['1','1','1','1','0'],
    ['1','1','0','1','0'],
    ['1','1','0','0','0'],
    ['0','0','0','0','0']
    ]
    输出：1

    示例 2：
    输入：grid = [
    ['1','1','0','0','0'],
    ['1','1','0','0','0'],
    ['0','0','1','0','0'],
    ['0','0','0','1','1']
    ]
    输出：3
*/


#include <vector>

bool inArea(size_t i, size_t j, size_t rows, size_t cols)
{
    return i >= 0 && i < rows && j >= 0 && j < cols;
}

template<typename T>
void dfs(T&& grid, std::vector<std::vector<bool>>& visited, size_t i, size_t j)
{
    if(!inArea(i, j, grid.size(), grid[0].size()))
        return;

    // 标记当前格子并访问四周的格子
    if(!visited[i][j] && grid[i][j] == '1') {
        visited[i][j] = true;
        dfs(grid, visited, i - 1, j);
        dfs(grid, visited, i + 1, j);
        dfs(grid, visited, i, j - 1);
        dfs(grid, visited, i, j + 1);
    }
}

int numIslands(std::vector<std::vector<char>>& grid) 
{
    if(grid.empty() || grid[0].empty())
        return 0;

    size_t num_islands = 0;
    std::vector<std::vector<bool>> visited(grid.size(), std::vector<bool>(grid[0].size(), false));
    for(size_t i = 0; i < std::size(grid); ++i){
        for(size_t j = 0; j < std::size(grid[i]); ++j){
            // 若当前格子是陆地且未访问，则进行DFS进行遍历并增加岛屿数
            if(grid[i][j] == '1' && !visited[i][j]){
                ++num_islands;
                dfs(grid, visited, i, j);
            }
        }
    }
    return num_islands;
}


int main()
{
    std::vector<std::vector<char>> lsland(
        {{'1','1','0','0','0'},
        {'1','1','0','0','0'},
        {'0','0','1','0','0'},
        {'0','0','0','1','1'}});
    printf("The number of islands is %d\n", numIslands(lsland));
    return 0;
}
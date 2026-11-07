/*
    130. 被围绕的区域
    给你一个 m x n 的矩阵 board ，由若干字符 'X' 和 'O' 组成，捕获 所有 被围绕的区域：

    连接：一个单元格与水平或垂直方向上相邻的单元格连接。
    区域：连接所有 'O' 的单元格来形成一个区域。
    围绕：如果一个区域中的所有 'O' 单元格都不在棋盘的边缘，则该区域被包围。这样的区域 完全 被 'X' 单元格包围。
    通过 原地 将输入矩阵中的所有 'O' 替换为 'X' 来 捕获被围绕的区域。你不需要返回任何值。

    示例 1：
    输入：board = [['X','X','X','X'],['X','O','O','X'],['X','X','O','X'],['X','O','X','X']]
    输出：[['X','X','X','X'],['X','X','X','X'],['X','X','X','X'],['X','O','X','X']]
    解释：

    示例 2：
    输入：board = [['X']]
    输出：[['X']]

    提示：
    m == board.length
    n == board[i].length
    1 <= m, n <= 200
    board[i][j] 为 'X' 或 'O'
*/

#include <vector>
#include <print>
#include <ranges>

void solve(std::vector<std::vector<char>>& board)
{
    size_t m = board.size();
    if(m <= 0)
        return;

    size_t n = board[0].size();
    std::vector<std::vector<bool>> visited(m, std::vector<bool>(n, false));

    auto dfs = [&board, &visited, m, n](
        this auto&& self, ptrdiff_t i, ptrdiff_t j){
        if(i < 0 || i >= m || j < 0 || j >= n || board[i][j] != 'O' || visited[i][j])
            return;
        
        visited[i][j] = true;
        
        // 访问上下左右四个方向
        self(i - 1, j);
        self(i + 1, j);
        self(i, j - 1);
        self(i, j + 1);

        board[i][j] = '#';
    };

    for(size_t i = 0; i < m; ++i){
        dfs(i, 0);
        dfs(i, n - 1);
    }
    for(size_t j = 0; j < n; ++j){
        dfs(0, j);
        dfs(m - 1, j);
    }

    for(auto& row : board){
        for(auto& cell : row){
            if(cell == 'O'){
                cell = 'X';
            }
            else if(cell == '#'){
                cell = 'O';
            }
        }
    }
}

int main()
{
    std::vector<std::vector<char>> board = {
        {'X','X','X','X','O','O','X','X','O'},
        {'O','O','O','O','X','X','O','O','X'},
        {'X','O','X','O','O','X','X','O','X'},
        {'O','O','X','X','X','O','O','O','O'},
        {'X','O','O','X','X','X','X','X','O'},
        {'O','O','X','O','X','O','X','O','X'},
        {'O','O','O','X','X','O','X','O','X'},
        {'O','O','O','X','O','O','O','X','O'},
        {'O','X','O','O','O','X','O','X','O'}
    };

    solve(board);

    for(const auto& row : board){
        std::println("{}", row);
    }

    return 0;
}
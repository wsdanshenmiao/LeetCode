/*
    51. N 皇后
    按照国际象棋的规则，皇后可以攻击与之处在同一行或同一列或同一斜线上的棋子。
    n 皇后问题 研究的是如何将 n 个皇后放置在 n×n 的棋盘上，并且使皇后彼此之间不能相互攻击。
    给你一个整数 n ，返回所有不同的 n 皇后问题 的解决方案。
    每一种解法包含一个不同的 n 皇后问题 的棋子放置方案，该方案中 'Q' 和 '.' 分别代表了皇后和空位。

    示例 1：
    输入：n = 4
    输出：[[".Q..","...Q","Q...","..Q."],["..Q.","Q...","...Q",".Q.."]]
    解释：如上图所示，4 皇后问题存在两个不同的解法。
    
    示例 2：
    输入：n = 1
    输出：[["Q"]]
*/


#include <vector>
#include <string>
#include <cmath>
#include <set>
#include <array>

// // 查找能放置皇后的位置并放置棋子
// void setQueens(std::set<std::vector<std::string>>& res, std::vector<std::string>& board, std::vector<std::vector<bool>> visited, int curr)
// {
//     if(curr <= 0){
//         res.insert(board);
//         return;
//     }

//     int n = std::size(visited);
//     // 尝试在棋盘中的每个位置放置皇后
//     for(size_t i = 0; i < std::size(visited); ++i){
//         for(size_t j = 0; j < std::size(visited[i]); ++j){
//             // 不可放置则跳过
//             if(visited[i][j])
//                 continue;

//             std::vector<std::vector<bool>> newVisited{visited};
//             board[i][j] = 'Q';
//             // 标记同一行、同一列、同一斜线上的位置
//             for(size_t k = 0; k < n; ++k){
//                 newVisited[i][k] = true;
//                 newVisited[k][j] = true;

//                 if(i + k < n && j + k < n)
//                     newVisited[i + k][j + k] = true;
//                 if(ptrdiff_t(i - k) >= 0 && ptrdiff_t(j - k) >= 0)
//                     newVisited[i - k][j - k] = true;
//                 if(i + k < n && ptrdiff_t(j - k) >= 0)
//                     newVisited[i + k][j - k] = true;
//                 if(ptrdiff_t(i - k) >= 0 && j + k < n)
//                     newVisited[i - k][j + k] = true;
//             }
//             setQueens(res, board, newVisited, curr - 1);
//             board[i][j] = '.';
//         }
//     }
// }

// std::vector<std::vector<std::string>> solveNQueens(int n)
// {
//     std::set<std::vector<std::string>> res{};
//     std::vector<std::string> board(n, std::string(n, '.'));
//     std::vector<std::vector<bool>> visited(n, std::vector<bool>(n, false));
//     setQueens(res, board, visited, n);
//     return std::vector<std::vector<std::string>>(res.begin(), res.end());
// }


// // 查找能放置皇后的位置并放置棋子
// void setQueens(std::set<std::vector<std::string>>& res, std::vector<std::string>& board, std::set<std::pair<size_t, size_t>> indices, int curr)
// {
//     if(curr <= 0){
//         res.insert(board);
//         return;
//     }

//     if(indices.size() < curr)
//         return;

//     for(const auto& [x, y] : indices){
//         auto newIndices{indices};
//         newIndices.erase({x, y});
//         board[x][y] = 'Q';
//         // 标记同一行、同一列、同一斜线上的位置
//         for(size_t k = 0; k < std::size(board); ++k){
//             newIndices.erase({x, k});
//             newIndices.erase({k, y});
//             if(x + k < std::size(board) && y + k < std::size(board))
//                 newIndices.erase({x + k, y + k});
//             if(ptrdiff_t(x - k) >= 0 && ptrdiff_t(y - k) >= 0)
//                 newIndices.erase({x - k, y - k});
//             if(x + k < std::size(board) && ptrdiff_t(y - k) >= 0)
//                 newIndices.erase({x + k, y - k});
//             if(ptrdiff_t(x - k) >= 0 && y + k < std::size(board))
//                 newIndices.erase({x - k, y + k});
//         }
//         setQueens(res, board, newIndices, curr - 1);
//         board[x][y] = '.';
//     }
// }

// std::vector<std::vector<std::string>> solveNQueens(int n)
// {
//     std::set<std::vector<std::string>> res{};
//     std::vector<std::string> board(n, std::string(n, '.'));
//     std::set<std::pair<size_t, size_t>> indices{};
//     for(size_t i = 0; i < n; ++i)
//         for(size_t j = 0; j < n; ++j)
//             indices.insert({i, j});
//     setQueens(res, board, indices, n);
//     return std::vector<std::vector<std::string>>(res.begin(), res.end());
// }


// 在 curr - 1 行查找能放置皇后的位置并放置棋子
void setQueens(std::vector<std::vector<std::string>>& res, 
    std::vector<std::string>& board, 
    std::set<size_t>& indices, 
    const std::vector<std::vector<size_t>>& kittyCorner, 
    int curr)
{
    if(curr <= 0){
        res.push_back(board);
        return;
    }

    if(indices.size() < curr)
        return;

    auto newIndices{indices};
    for(const auto& index : kittyCorner[curr - 1])
        newIndices.erase(index);

    for(const auto index : newIndices){
		auto newKittyCorner{ kittyCorner };
        // 下一行的斜对角位置
        for(ptrdiff_t i = curr - 2; i >= 0; --i){
            if(index + curr - 1 - i < std::size(board))
                newKittyCorner[i].push_back(index + curr - 1 - i);
            if(ptrdiff_t(index - (curr - 1 - i)) >= 0)
                newKittyCorner[i].push_back(index - (curr - 1 - i));
        }
        
        // 后续 index 列不能放置皇后
        indices.erase(index);
        board[curr - 1][index] = 'Q';
        setQueens(res, board, indices, newKittyCorner, curr - 1);
        board[curr - 1][index] = '.';
        indices.insert(index);
    }
}

std::vector<std::vector<std::string>> solveNQueens(int n)
{
    std::vector<std::vector<std::string>> res{};
    std::vector<std::string> board(n, std::string(n, '.'));
    std::set<size_t> indices{};
    for(size_t i = 0; i < n; ++i)
        indices.insert(i);
    std::vector<std::vector<size_t>> kittyCorner(n);
    setQueens(res, board, indices, kittyCorner, n);
    return res;
}

int main()
{
    int n;
    scanf("%d", &n);
    for (auto c = getchar(); c != '\n' && c != EOF;);
    n = std::max(1, n);
    std::vector<std::vector<std::string>> res = solveNQueens(n);
    for(const auto& solution : res){
        for(const auto& row : solution)
            printf("%s\n", row.c_str());
        printf("\n");
    }
    printf("Total solutions: %zu\n", std::size(res));
    getchar();
    return 0;
}
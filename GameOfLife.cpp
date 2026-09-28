/*
    289. 生命游戏
    根据 百度百科 ， 生命游戏 ，简称为 生命 ，是英国数学家约翰·何顿·康威在 1970 年发明的细胞自动机。
    给定一个包含 m × n 个格子的面板，每一个格子都可以看成是一个细胞。
    每个细胞都具有一个初始状态： 1 即为 活细胞 （live），或 0 即为 死细胞 （dead）。
    每个细胞与其八个相邻位置（水平，垂直，对角线）的细胞都遵循以下四条生存定律：
    如果活细胞周围八个位置的活细胞数少于两个，则该位置活细胞死亡；
    如果活细胞周围八个位置有两个或三个活细胞，则该位置活细胞仍然存活；
    如果活细胞周围八个位置有超过三个活细胞，则该位置活细胞死亡；
    如果死细胞周围正好有三个活细胞，则该位置死细胞复活；
    下一个状态是通过将上述规则同时应用于当前状态下的每个细胞所形成的，其中细胞的出生和死亡是 同时 发生的。
    给你 m x n 网格面板 board 的当前状态，返回下一个状态。
    给定当前 board 的状态，更新 board 到下一个状态。
    注意 你不需要返回任何东西。

    示例 1：
    输入：board = [[0,1,0],[0,0,1],[1,1,1],[0,0,0]]
    输出：[[0,0,0],[1,0,1],[0,1,1],[0,1,0]]
    
    示例 2：
    输入：board = [[1,1],[1,0]]
    输出：[[1,1],[1,1]]
*/

#include <vector>
#include <array>

// void gameOfLife(std::vector<std::vector<int>>& board)
// {
//     std::vector<std::vector<int>> newState(board.size(), std::vector<int>(board.empty() ? 0 : board[0].size()));
//     for(size_t i = 0; i < std::size(board); ++i){
//         for(size_t j = 0; j < std::size(board[i]); ++j){
//             // 计算 board[i][j] 周围八个位置的活细胞数
//             for(size_t y = std::max(i, 1zu) - 1; y <= std::min(i + 1, std::size(board) - 1); ++y){
//                 for(size_t x = std::max(j, 1zu) - 1; x <= std::min(j + 1, std::size(board[i]) - 1); ++x){
//                     if(y == i && x == j) continue;
//                     newState[i][j] += board[y][x];
//                 }
//             }

//             if(newState[i][j] < 2 || newState[i][j] > 3){
//                 // 活细胞周围八个位置的活细胞数少于两个，则该位置活细胞死亡
//                 // 活细胞周围八个位置有超过三个活细胞，则该位置活细胞死亡
//                 newState[i][j] = 0;
//             }
//             else if(newState[i][j] == 3){
//                 // 死细胞周围正好有三个活细胞，则该位置死细胞复活
//                 newState[i][j] = 1;
//             }
//             else{
//                 // 活细胞周围八个位置有两个或三个活细胞，则该位置活细胞仍然存活
//                 newState[i][j] = board[i][j];

//             }
//         }
//     }
    
//     board = newState;
// }


// void gameOfLife(std::vector<std::vector<int>>& board)
// {
//     if(board.empty())
//         return;
//     // 一个用于保存上一行状态，一个用于保存当前行状态
//     std::array<std::vector<int>, 2> oldState{std::vector<int>(board[0].size()), std::vector<int>(board[0].size())};
//     for(size_t i = 0; i < std::size(board); ++i){
//         int preState = 0;
//         for(size_t j = 0; j < std::size(board[i]); ++j){
//             int liveCount = 0;
//             // 计算上一行的活细胞数
//             if(i > 0){
//                 for(size_t x = std::max(j, 1zu) - 1; x <= std::min(j + 1, std::size(board[i]) - 1); ++x){
//                     liveCount += oldState[i % 2][x];
//                 }
//             }
//             liveCount += preState;
//             liveCount += j < std::size(board[i]) - 1 ? board[i][j + 1] : 0;
//             if(i < std::size(board) - 1){
//                 for(size_t x = std::max(j, 1zu) - 1; x <= std::min(j + 1, std::size(board[i]) - 1); ++x){
//                     liveCount += board[i + 1][x];
//                 }
//             }
//             preState = board[i][j];
//             // 将当前行的状态保存到 oldState 中，以便下一行计算时使用
//             oldState[(i + 1) % 2][j] = board[i][j];

//             if(liveCount < 2 || liveCount > 3){
//                 // 活细胞周围八个位置的活细胞数少于两个，则该位置活细胞死亡
//                 // 活细胞周围八个位置有超过三个活细胞，则该位置活细胞死亡
//                 board[i][j] = 0;
//             }
//             else if(liveCount == 3){
//                 // 死细胞周围正好有三个活细胞，则该位置死细胞复活
//                 board[i][j] = 1;
//             }
//             else{
//                 // 活细胞周围八个位置有两个或三个活细胞，则该位置活细胞仍然存活
//                 board[i][j] = board[i][j];
//             }
//         }
//     }
// }

void gameOfLife(std::vector<std::vector<int>>& board)
{
    for(size_t i = 0; i < std::size(board); ++i){
        for(size_t j = 0; j < std::size(board[i]); ++j){
            // 遍历周围的八个位置，计算活细胞数
            for(size_t y = std::max(i, 1zu) - 1; y <= std::min(i + 1, std::size(board) - 1); ++y){
                for(size_t x = std::max(j, 1zu) - 1; x <= std::min(j + 1, std::size(board[i]) - 1); ++x){
                    if(y == i && x == j)
                        continue;
                    board[i][j] += (board[y][x] % 10) * 10;
                }
            }
        }
    }

    for(auto& row : board){
        for(auto& cell : row){
            int liveCount = cell / 10;
            cell = liveCount == 3 ? 1 : cell % 10;
            if(liveCount < 2 || liveCount > 3){
                cell = 0;
            }
        }
    }
}


int main()
{
    auto printBoard = [](const std::vector<std::vector<int>>& board) {
        for(const auto& row : board) {
            for(int cell : row) {
                printf("%d ", cell);
            }
            printf("\n");
        }
    };
    std::vector<std::vector<int>> board = {{0,1,0},{0,0,1},{1,1,1},{0,0,0}};
    printBoard(board);
    gameOfLife(board);
    printf("Next State:\n");
    printBoard(board);
    return 0;
}
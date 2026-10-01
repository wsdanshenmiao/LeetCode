/*
    77. 组合
    给定两个整数 n 和 k，返回范围 [1, n] 中所有可能的 k 个数的组合。
    你可以按 任何顺序 返回答案。

    示例 1：
    输入：n = 4, k = 2
    输出：
    [
    [2,4],
    [3,4],
    [2,3],
    [1,2],
    [1,3],
    [1,4],
    ]

    示例 2：
    输入：n = 1, k = 1
    输出：[[1]]
    
    提示：
    1 <= n <= 20
    1 <= k <= n
*/

#include <vector>
#include <print>
#include <numeric>
#include <unordered_set>

std::vector<std::vector<int>> combine(int n, int k)
{
    if(n <= 0 || k <= 0 || k > n)
        return {};

    std::vector<int> path{};
    path.reserve(k);
    std::vector<std::vector<int>> result{};
    auto dfs = [&result, &path, n, k](this auto&& self, int curr){
        if(std::size(path) >= k){
            result.push_back(path);
            return;
        }

        for(int i = curr; i  <= n; ++i){
            path.push_back(i);
            self(i + 1);
            path.pop_back();
        }
    };

    dfs(1);

    return result;
}


int main()
{
    std::println("combine(4, 2) = {}", combine(4, 2));
    return 0;
}
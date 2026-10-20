/*
    20.
    放他去修仙
    放他去修仙是一款特别好玩的武侠修仙游戏，秘境探索是游戏的一大特色。
    随着修行者能力的提升，玩家也可以不断的探索新的奇山怪景，直至探索人人都向往的天外天。如今天地灵气聚集，无需自身修为即可自由出入各大仙境。
    小G作为游戏的忠实玩家，非常期待去探索所有的地方，虽然没有了仙法的限制，但是每一条路都需要消耗一定的机缘。
    小G为了尽量少的消耗机缘，每一个地点至多经过俩次。那么要游览所有的地点，至少需要多少机缘呢？
    时间限制：C/C++ 1秒，其他语言2秒
    空间限制：C/C++ 128M，其他语言256M
    输入描述：
    第一行n,m。n(1<=n<=10), 代表了仙境的编号和路径的数量。
    接下来有m行,每行有a,b,c(1<=a,b<=n ; 1<=c<=100), 代表了仙境a到达仙境b需要消耗c的机缘。
    输出描述：
    输出小G需要消耗的最小的机缘。如果无法游览所有的地点,输出-1。

    示例1
    输入例子：
    3 2
    1 2 5
    1 3 1
    输出例子：
    6
*/

#include <iostream>
#include <vector>
#include <unordered_map>
#include <limits>

int main()
{
    int n, m;
    std::cin >> n >> m;

    std::vector<std::unordered_map<int, int>> graph(n, std::unordered_map<int, int>());
    for(int i = 0; i < m; ++i){
        int a, b, c;
        std::cin >> a >> b >> c;
        if(graph[a - 1].count(b - 1)){
            graph[a - 1][b - 1] = std::min(graph[a - 1][b - 1], c);
        } else {
            graph[a - 1][b - 1] = c;
        }
        if(graph[b - 1].count(a - 1)){
            graph[b - 1][a - 1] = std::min(graph[b - 1][a - 1], c);
        } else {
            graph[b - 1][a - 1] = c;
        }
    }

    std::vector<int> visitedCount(n, 0);
    int minCost = std::numeric_limits<int>::max();
    auto dfs = [&](auto&& self, int node, int count, int cost) -> int {
        if(count == n || cost >= minCost)
            return cost;

        for(const auto& [nextNode, edgeCost] : graph[node]){
            if(visitedCount[nextNode] < 2){
                visitedCount[nextNode]++;
                int nextCount = count + (visitedCount[nextNode] == 2 ? 0 : 1);
                minCost = std::min(minCost, self(self, nextNode, nextCount, cost + edgeCost));
                visitedCount[nextNode]--;
            }
        }
        return minCost;
    };

    for(int startNode = 0; startNode < n; ++startNode){
        visitedCount[startNode]++;
        minCost = std::min(minCost, dfs(dfs, startNode, 1, 0));
        visitedCount[startNode]--;
    }
    if(minCost == std::numeric_limits<int>::max())
        std::cout << -1 << std::endl;
    else
        std::cout << minCost << std::endl;

    return 0;
}
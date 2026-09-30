/*
    502. IPO
    假设 力扣（LeetCode）即将开始 IPO 。为了以更高的价格将股票卖给风险投资公司，力扣 希望在 IPO 之前开展一些项目以增加其资本。
    由于资源有限，它只能在 IPO 之前完成最多 k 个不同的项目。帮助 力扣 设计完成最多 k 个不同项目后得到最大总资本的方式。
    给你 n 个项目。对于每个项目 i ，它都有一个纯利润 profits[i] ，和启动该项目需要的最小资本 capital[i] 。
    最初，你的资本为 w 。当你完成一个项目时，你将获得纯利润，且利润将被添加到你的总资本中。
    总而言之，从给定项目中选择 最多 k 个不同项目的列表，以 最大化最终资本 ，并输出最终可获得的最多资本。
    答案保证在 32 位有符号整数范围内。

    示例 1：
    输入：k = 2, w = 0, profits = [1,2,3], capital = [0,1,1]
    输出：4
    解释：
    由于你的初始资本为 0，你仅可以从 0 号项目开始。
    在完成后，你将获得 1 的利润，你的总资本将变为 1。
    此时你可以选择开始 1 号或 2 号项目。
    由于你最多可以选择两个项目，所以你需要完成 2 号项目以获得最大的资本。
    因此，输出最后最大化的资本，为 0 + 1 + 3 = 4。
    
    示例 2：
    输入：k = 3, w = 0, profits = [1,2,3], capital = [0,1,2]
    输出：6

    提示：
    1 <= k <= 105
    0 <= w <= 109
    n == profits.length
    n == capital.length
    1 <= n <= 105
    0 <= profits[i] <= 104
    0 <= capital[i] <= 109
*/

#include <vector>
#include <ranges>
#include <print>
#include <queue>
#include <numeric>
#include <algorithm>

template<std::size_t Version = 0>
int findMaximizedCapital(int k, int w, std::vector<int>& profits, std::vector<int>& capital);

template<>
int findMaximizedCapital<0>(int k, int w, std::vector<int>& profits, std::vector<int>& capital) {
    for(std::size_t i = 0; i < k; ++i){
        int maxProfit = 0;
        std::size_t maxProfitIndex = -1;
        // 查找最小资本小于 w 的最大利润的项目
        for(const auto& [index, c] : capital | std::views::enumerate){
            if(c <= w && profits[index] > maxProfit){
                maxProfit = profits[index];
                maxProfitIndex = index;
            }
        }
        if(maxProfitIndex != -1){
            w += maxProfit;
            profits.erase(std::next(std::begin(profits), maxProfitIndex));
            capital.erase(std::next(std::begin(capital), maxProfitIndex));
            maxProfit = 0;
            maxProfitIndex = -1;
        }
        else{
            break;
        }
    }

    return w;
}

template<>
int findMaximizedCapital<1>(int k, int w, std::vector<int>& profits, std::vector<int>& capital) {
    // 使用优先队列优化
    using PairType = std::pair<int, int>;
    auto cmp = [](const PairType& a, const PairType& b) { return a.first < b.first; };
    std::priority_queue<PairType, std::vector<PairType>, decltype(cmp)> maxHeap{};
    std::vector<std::size_t> indices(std::size(profits));
    std::ranges::iota(indices, 0);
    for(std::size_t i = 0; i < k; ++i){
        // 将所有可行的项目加入优先队列
        for(auto it = std::begin(indices); it != std::end(indices);){
            if(capital[*it] <= w){
                maxHeap.emplace(profits[*it], static_cast<int>(*it));
                it = indices.erase(it);
            } else {
                ++it;
            }
        }

        // 选择利润最大的项目
        if(!maxHeap.empty()){
            w += maxHeap.top().first;
            maxHeap.pop();
        }
        else{
            break;
        }
    }

    return w;
}

template<>
int findMaximizedCapital<2>(int k, int w, std::vector<int>& profits, std::vector<int>& capital) {
    std::priority_queue<int> maxHeap{};
    std::vector<std::size_t> indices(std::size(profits));

    std::ranges::iota(indices, 0);
    // 按照最小资本进行排序
    std::ranges::sort(indices, [&capital](std::size_t a, std::size_t b) { return capital[a] < capital[b]; });

    std::size_t index = 0;
    for(std::size_t i = 0; i < k; ++i){
        // 将所有可行的项目加入优先队列
        while (index < capital.size() && capital[indices[index]] <= w) {
            maxHeap.push(profits[indices[index]]);
            ++index;
        }

        if(maxHeap.empty())
            break;

        // 选择利润最大的项目
        w += maxHeap.top();
        maxHeap.pop();
    }

    return w;
}

int main()
{
    constexpr std::size_t version = 2;
    std::vector<int> profits = {1, 2, 3};
    std::vector<int> capital = {0, 1, 1};
    std::println("{}", findMaximizedCapital<version>(2, 0, profits, capital));
    std::vector<int> profits2 = {1, 2, 3};
    std::vector<int> capital2 = {0, 1, 2};
    std::println("{}", findMaximizedCapital<version>(3, 0, profits2, capital2));
    return 0;
}
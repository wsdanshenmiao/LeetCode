/*
    274. H 指数
    提示
    给你一个整数数组 citations ，其中 citations[i] 表示研究者的第 i 篇论文被引用的次数。计算并返回该研究者的 h 指数。

    根据维基百科上 h 指数的定义：h 代表“高引用次数” ，一名科研人员的 h 指数 是指他（她）至少发表了 h 篇论文，
    并且 至少 有 h 篇论文被引用次数大于等于 h 。如果 h 有多种可能的值，h 指数 是其中最大的那个。

    示例 1：
    输入：citations = [3,0,6,1,5]
    输出：3 
    解释：给定数组表示研究者总共有 5 篇论文，每篇论文相应的被引用了 3, 0, 6, 1, 5 次。
        由于研究者有 3 篇论文每篇 至少 被引用了 3 次，其余两篇论文每篇被引用 不多于 3 次，所以她的 h 指数是 3。
    
    示例 2：
    输入：citations = [1,3,1]
    输出：1

    提示：
    n == citations.length
    1 <= n <= 5000
    0 <= citations[i] <= 1000
*/

#include <vector>
#include <ranges>
#include <print>
#include <algorithm>

template <std::size_t Version = 0>
int HIndex(std::vector<int>& citations);

template<>
int HIndex<0>(std::vector<int>& citations)
{
    size_t maxH = 0;
    for(const auto& [i, citation] : citations | std::views::enumerate){
        size_t h = 0;
        for(const auto& [j, otherCitation] : citations | std::views::enumerate){
            // 统计引用次数大于等于当前论文引用次数的论文数量
            if(otherCitation >= citation){
                h++;
            }
        }
        if (auto newH = std::min(h, size_t(citation)); newH > maxH) {
            maxH = newH;
        }
    }

    return maxH;
}

template<>
int HIndex<1>(std::vector<int>& citations)
{
    std::ranges::sort(citations);

    size_t maxH = 0;
    for(const auto& [i, citation] : citations | std::views::enumerate){
        size_t h = citations.size() - i;
        if (auto newH = std::min(h, size_t(citation)); newH > maxH) {
            maxH = newH;
        }
    }
    return maxH;
}

void CountSort(std::vector<int>& container)
{
    std::vector<int> count{1001, 0};
    for(const auto& citation : container){
        if(std::size(count) <= citation){
            count.resize(citation + 1, 0);
        }
        count[citation]++;
    }

    size_t index = 0;
    for(auto [i, val] : count | std::views::enumerate){
        while(val > 0){
            container[index++] = i;
            val--;
        }
    }
}

int main()
{
    constexpr std::size_t version = 1;
    
    std::vector<int> citations0{3, 0, 6, 1, 5};
    std::vector<int> citations1{1, 3, 1};
    std::println("HIndex: {}", HIndex<version>(citations0));
    std::println("HIndex: {}", HIndex<version>(citations1));
    return 0;
}
/*
57. 插入区间
    给你一个 无重叠的 ，按照区间起始端点排序的区间列表 intervals，其中 intervals[i] = [starti, endi] 表示第 i 个区间的开始和结束，
    并且 intervals 按照 starti 升序排列。同样给定一个区间 newInterval = [start, end] 表示另一个区间的开始和结束。
    如果两个区间 至少 共享一个点，则认为它们是重叠的。
    在 intervals 中插入区间 newInterval，使得 intervals 依然按照 starti 升序排列，且区间之间不重叠（如果有必要的话，可以合并区间）。
    返回插入之后的 intervals。
    注意 你不需要原地修改 intervals。你可以创建一个新数组然后返回它。

    示例 1：
    输入：intervals = [[1,3],[6,9]], newInterval = [2,5]
    输出：[[1,5],[6,9]]
    
    示例 2：
    输入：intervals = [[1,2],[3,5],[6,7],[8,10],[12,16]], newInterval = [4,8]
    输出：[[1,2],[3,10],[12,16]]
    解释：这是因为新的区间 [4,8] 与 [3,5],[6,7],[8,10] 重叠。

    提示：
    0 <= intervals.length <= 104
    intervals[i].length == 2
    0 <= starti <= endi <= 105
    intervals 根据 starti 按 升序 排列
    newInterval.length == 2
    0 <= start <= end <= 105

    实现要点：
    - 整体 O(n) 单趟扫描，三段式：拷贝左侧 / 合并重叠 / 拷贝右侧
    - 一次 reserve，避免扩容搬移；不做 vector::erase（中间 erase 是 O(n)，套在循环里会退化成 O(n^2)）
    - newInterval 按值传入：函数内部自由扩张它，同时不污染调用方的入参
*/

#include <algorithm>
#include <cstddef>
#include <print>
#include <vector>

std::vector<std::vector<int>> insert(const std::vector<std::vector<int>>& intervals, std::vector<int> newInterval)
{
    std::vector<std::vector<int>> result;
    result.reserve(intervals.size() + 1);

    std::size_t i = 0;

    // 1. 完全位于新区间左侧、不可能重叠的部分，直接搬运
    //    （共享一个点算重叠，所以这里必须是严格小于）
    while (i < intervals.size() && intervals[i][1] < newInterval[0]) {
        result.push_back(intervals[i++]);
    }

    // 2. 所有与新区间相交的区间，就地扩张 newInterval
    while (i < intervals.size() && intervals[i][0] <= newInterval[1]) {
        newInterval[0] = std::min(newInterval[0], intervals[i][0]);
        newInterval[1] = std::max(newInterval[1], intervals[i][1]);
        ++i;
    }
    result.push_back(std::move(newInterval)); // 此后不再访问 newInterval

    // 3. 剩余右侧部分，直接搬运
    while (i < intervals.size()) {
        result.push_back(intervals[i++]);
    }

    return result;
}

int main()
{
    struct TestCase {
        std::vector<std::vector<int>> intervals;
        std::vector<int> newInterval;
    };

    const std::vector<TestCase> cases = {
        {{{1, 3}, {6, 9}}, {2, 5}},                            // 示例 1：合并左侧
        {{{1, 2}, {3, 5}, {6, 7}, {8, 10}, {12, 16}}, {4, 8}}, // 示例 2：合并中间三段
        {{}, {5, 7}},                                          // 空列表
        {{{1, 5}}, {2, 3}},                                    // 新区间被完全包含
        {{{1, 5}}, {6, 8}},                                    // 追加到末尾且不接触
        {{{1, 5}}, {5, 8}},                                    // 末尾端点接触，需合并
        {{{3, 5}, {6, 9}}, {1, 2}},                            // 插入到开头
        {{{1, 2}, {3, 5}, {6, 9}}, {0, 10}},                   // 吞掉全部区间
    };

    for (const auto& testCase : cases) {
        std::println("intervals:   {}", testCase.intervals);
        std::println("newInterval: {}", testCase.newInterval);
        std::println("result:      {}", insert(testCase.intervals, testCase.newInterval));
        std::println();
    }

    return 0;
}

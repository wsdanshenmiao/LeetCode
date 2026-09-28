/*
    34. 在排序数组中查找元素的第一个和最后一个位置
    给你一个按照非递减顺序排列的整数数组 nums，和一个目标值 target。请你找出给定目标值在数组中的开始位置和结束位置。
    如果数组中不存在目标值 target，返回 [-1, -1]。
    你必须设计并实现时间复杂度为 O(log n) 的算法解决此问题。

    示例 1：
    输入：nums = [5,7,7,8,8,10], target = 8
    输出：[3,4]
    
    示例 2：
    输入：nums = [5,7,7,8,8,10], target = 6
    输出：[-1,-1]

    示例 3：
    输入：nums = [], target = 0
    输出：[-1,-1]
*/

#include <vector>
#include <algorithm>

// std::vector<int> searchRange(std::vector<int>& nums, int target)
// {
//     auto it = std::ranges::lower_bound(nums, target);
//     std::vector<int> result{};
//     if(it != std::end(nums) && *it == target) {
//         result.emplace_back(std::distance(std::begin(nums), it));
//         while(it != std::end(nums) && *it == target){
//             ++it;
//         }
//         result.emplace_back(std::distance(std::begin(nums), it) - 1);
//     }
//     else{
//         result.emplace_back(-1);
//         result.emplace_back(-1);
//     }
//     return result;
// }


std::vector<int> searchRange(std::vector<int>& nums, int target)
{
    if(std::empty(nums)){
        return {-1, -1};
    }

    size_t left = 0, right = std::size(nums) - 1;
    while (left < right) {
        size_t mid = left + (right - left) / 2;
        if(nums[mid] < target){
            left = mid + 1;
        }
        else{
            right = mid;
        }
    }

    if(nums[left] != target){
        return {-1, -1};
    }

    right = left;
    while (right < std::size(nums) - 1 && nums[right + 1] == target) {
        ++right;
    }

    return {static_cast<int>(left), static_cast<int>(right)};
}

int main()
{
    std::vector<int> nums{5,7,7,8,8,10};
    auto result = searchRange(nums, 8);
    for(const auto& i : result){
        printf("%d ", i);
    }
    return 0;
}
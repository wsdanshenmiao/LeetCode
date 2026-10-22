/*
    35. 搜索插入位置
    给定一个排序数组和一个目标值，在数组中找到目标值，并返回其索引。如果目标值不存在于数组中，返回它将会被按顺序插入的位置。
    请必须使用时间复杂度为 O(log n) 的算法。

    示例 1:
    输入: nums = [1,3,5,6], target = 5
    输出: 2
    
    示例 2:
    输入: nums = [1,3,5,6], target = 2
    输出: 1
    
    示例 3:
    输入: nums = [1,3,5,6], target = 7
    输出: 4

    提示:
    1 <= nums.length <= 104
    -104 <= nums[i] <= 104
    nums 为 无重复元素 的 升序 排列数组
    -104 <= target <= 104
*/

#include <vector>
#include <print>
#include <algorithm>

template<std::size_t Version>
int searchInsert(std::vector<int>& nums, int target);

template<>
int searchInsert<0>(std::vector<int>& nums, int target)
{
    auto it = std::ranges::lower_bound(nums, target);
    if(it == std::end(nums) || *it != target){
        it = nums.insert(it, target);
    }

    return std::distance(std::begin(nums), it);
}

template<>
int searchInsert<1>(std::vector<int>& nums, int target)
{
    std::size_t left = 0, right = std::size(nums);
    while(left < right){
        std::size_t mid = left + (right - left) / 2;
        if(nums[mid] < target){
            left = mid + 1;
        }
        else{
            right = mid;
        }
    }

    return left;
}

int main()
{
    constexpr std::size_t version = 1; // 选择使用的版本
    std::vector<int> nums = {1, 3, 5, 6};
    int target = 5;
    int result = searchInsert<version>(nums, target);
    std::println("The index of the target is: {}", result); // 输出: The index of the target is: 2
    return 0;
}
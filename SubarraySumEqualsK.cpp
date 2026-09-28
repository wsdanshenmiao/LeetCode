/*
    560. 和为 K 的子数组
    给你一个整数数组 nums 和一个整数 k ，请你统计并返回 该数组中和为 k 的子数组的个数 。
    子数组是数组中元素的连续非空序列。

    示例 1：
    输入：nums = [1,1,1], k = 2
    输出：2

    示例 2：
    输入：nums = [1,2,3], k = 3
    输出：2
*/

#include <vector>
#include <unordered_map>
#include <ranges>

// int subarraySum(std::vector<int>& nums, int k)
// {
//     // 计算前缀和
//     int count = nums.empty() ? 0 : (nums[0] == k ? 1 : 0);
//     for(size_t i = 1; i < std::size(nums); ++i){
//         nums[i] += nums[i - 1];
//         if(nums[i] == k){
//             ++count;
//         }
//     }

//     // 分别计算窗口为 i 的子数组的和是否等于 k
//     for(size_t i = 2; i <= std::size(nums); ++i){
//         for(size_t j = 0; j <= std::size(nums) - i; ++j){
//             if(nums[i + j - 1] - nums[j] == k){
//                 ++count;
//             }
//         }
//     }

//     return count;
// }

int subarraySum(std::vector<int>& nums, int k)
{
    std::unordered_map<int, size_t> prefixSumCount;
    int pre = 0;
    int count = 0;
    prefixSumCount[0] = 1;
    for(const auto& num : nums){
        pre += num;
        if(prefixSumCount.contains(pre - k)){
            count += prefixSumCount[pre - k];
        }
        ++prefixSumCount[pre];
    }

    return count;
}


int main()
{    
    std::vector<int> nums1{1, 1, 1};
    std::printf("%d\n", subarraySum(nums1, 2)); // 2
    return 0;
}
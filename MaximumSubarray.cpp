/*
    53. 最大子数组和
    给你一个整数数组 nums ，请你找出一个具有最大和的连续子数组（子数组最少包含一个元素），返回其最大和。
    子数组是数组中的一个连续部分。

    示例 1：
    输入：nums = [-2,1,-3,4,-1,2,1,-5,4]
    输出：6
    解释：连续子数组 [4,-1,2,1] 的和最大，为 6 。

    示例 2：
    输入：nums = [1]
    输出：1
    
    示例 3：
    输入：nums = [5,4,-1,7,8]
    输出：23
    
    提示：
    1 <= nums.length <= 105
    -104 <= nums[i] <= 104
    
    进阶：如果你已经实现复杂度为 O(n) 的解法，尝试使用更为精妙的 分治法 求解。
*/

#include <vector>
#include <limits>
#include <print>

template<size_t Version>
int maxSubArray(std::vector<int>& nums);

void printTable(const std::vector<std::vector<int>>& t){
    for(const auto& a : t){
        std::println("{}", a);
    }
    std::println();
}

template<>
int maxSubArray<0>(std::vector<int>& nums)
{
    int maxSum = std::numeric_limits<int>::lowest();
    for(size_t i = 0; i < std::size(nums); ++i){
        int currSum = 0;
        for(size_t j = i; j < std::size(nums); ++j){
            currSum += nums[j];
            if(currSum > maxSum){
                maxSum = currSum;
            }
        }
    }
    return maxSum;
}

template<>
int maxSubArray<1>(std::vector<int>& nums)
{
    int curr = std::numeric_limits<int>::lowest();
    int max = curr;
    for(const auto& num : nums){
        curr = num + std::max(curr, 0);
        max = std::max(curr, max);
    }

    return max;
}

int main()
{
    constexpr size_t version = 1;
    std::vector<int> nums = {-2,1,-3,4,-1,2,1,-5,4};
    int result = maxSubArray<version>(nums);
    std::println("Maximum subarray sum: {}", result);
    return 0;
}
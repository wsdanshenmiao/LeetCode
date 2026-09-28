/*
    209. 长度最小的子数组
    给定一个含有 n 个正整数的数组和一个正整数 target 。
    找出该数组中满足其总和大于等于 target 的长度最小的 子数组 [numsl, numsl+1, ..., numsr-1, numsr] ，
    并返回其长度。如果不存在符合条件的子数组，返回 0 。

    示例 1：
    输入：target = 7, nums = [2,3,1,2,4,3]
    输出：2
    解释：子数组 [4,3] 是该条件下的长度最小的子数组。

    示例 2：
    输入：target = 4, nums = [1,4,4]
    输出：1

    示例 3：
    输入：target = 11, nums = [1,1,1,1,1,1,1,1]
    输出：0
*/

#include <vector>

// int minSubArrayLen(int target, std::vector<int>& nums)
// {
//     for(size_t i = 0; i < std::size(nums); ++i){
//         if(nums[i] >= target)
//             return 1;
//         if(i > 0)
//             nums[i] += nums[i - 1];
//     }
//     for(size_t i = 2; i <= std::size(nums); ++i){
//         for(size_t j = 0; j < std::size(nums) - i + 1; ++j){
//             int left = j == 0 ? 0 : nums[j - 1];
//             if(nums[i + j - 1] - left >= target)
//                 return i;
//         }
//     }

//     return 0;
// }

int minSubArrayLen(int target, std::vector<int>& nums)
{
    int minLen = std::numeric_limits<int>::max();
    for(size_t left = 0, right = 0, sum = 0; right < std::size(nums); ++right){
        sum += nums[right];
        while (sum >= target) {
            minLen = std::min(minLen, static_cast<int>(right - left + 1));
            sum -= nums[left++];
        }
    }
    return minLen == std::numeric_limits<int>::max() ? 0 : minLen;
}

int main()
{
    std::vector<int> nums{1,2,3,4,5};
    printf("%d\n", minSubArrayLen(15, nums));
    return 0;
}
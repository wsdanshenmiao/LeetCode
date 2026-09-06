/*
    238. 除了自身以外数组的乘积
    给你一个整数数组 nums，返回 数组 answer ，其中 answer[i] 等于 nums 中除了 nums[i] 之外其余各元素的乘积 。
    题目数据 保证 数组 nums之中任意元素的全部前缀元素和后缀的乘积都在  32 位 整数范围内。
    请 不要使用除法，且在 O(n) 时间复杂度内完成此题。

    示例 1:
    输入: nums = [1,2,3,4]
    输出: [24,12,8,6]

    示例 2:
    输入: nums = [-1,1,0,-3,3]
    输出: [0,0,9,0,0]
*/

#include <vector>
#include <ranges>

// std::vector<int> productExceptSelf(std::vector<int>& nums)
// {
//     std::vector<int> result(std::size(nums), 0);
//     int sum = 1;
//     bool hasZero = false;
//     bool oneZero = false;
//     for(const auto& num : nums){
//         sum *= num == 0 ? 1 : num;
//         if(hasZero && num == 0){
//             oneZero = false;
//             break;
//         }
//         hasZero |= num == 0;
//         oneZero |= num == 0;
//     }
    
//     for(auto [i, num] : result | std::views::enumerate){
//         num = hasZero ? (oneZero ? (nums[i] == 0 ? sum : 0) : 0) : sum / nums[i];
//     }
//     return result;
// }

// std::vector<int> productExceptSelf(std::vector<int>& nums)
// {
//     if(std::empty(nums)){
//         return {};
//     }

//     auto size = std::size(nums);
//     std::vector<int> prefix(size, nums[0]);
//     std::vector<int> suffix(size, nums[size - 1]);
//     // 计算前缀积
//     for(size_t i = 1; i < size; ++i){
//         prefix[i] = prefix[i - 1] * nums[i];
//     }
//     // 计算后缀积
//     for(ptrdiff_t i = size - 2; i >= 0; --i){
//         suffix[i] = suffix[i + 1] * nums[i];
//     }
    
//     std::vector<int> result(size, 0);
//     for(size_t i = 0; i < size; ++i){
//         // 当前元素等于前缀积与后缀积的乘积
//         result[i] = (i == 0 ? 1 : prefix[i - 1]) * (i == size - 1 ? 1 : suffix[i + 1]);
//     }

//     return result;
// }

std::vector<int> productExceptSelf(std::vector<int>& nums)
{
    auto size = std::size(nums);
    std::vector<int> result(size, 0);
    // 计算前缀积
    for(size_t i = 0; i < size; ++i){
        result[i] = (i == 0 ? 1 : result[i - 1]) * nums[i];
    }
    int suffix = 1;
    for(ptrdiff_t i = size - 1; i >= 0; --i){
        // 保存后缀积
        suffix *= i == size - 1 ? 1 : nums[i + 1];
        // 当前元素等于前缀积与后缀积的乘积
        result[i] = suffix * (i == 0 ? 1 : result[i - 1]);
    }
    return result;
}

int main()
{
    std::vector<int> nums = {-1,1,0,-3,3};
    std::vector<int> result = productExceptSelf(nums);
    for(const auto& num : result){
        printf("%d\n", num);
    }
    return 0;
}
/*
    15. 三数之和
    给你一个整数数组 nums ，判断是否存在三元组 [nums[i], nums[j], nums[k]] 满足 i != j、i != k 且 j != k ，
    同时还满足 nums[i] + nums[j] + nums[k] == 0 。请你返回所有和为 0 且不重复的三元组。
    注意：答案中不可以包含重复的三元组。

    示例 1：
    输入：nums = [-1,0,1,2,-1,-4]
    输出：[[-1,-1,2],[-1,0,1]]
    解释：
    nums[0] + nums[1] + nums[2] = (-1) + 0 + 1 = 0 。
    nums[1] + nums[2] + nums[4] = 0 + 1 + (-1) = 0 。
    nums[0] + nums[3] + nums[4] = (-1) + 2 + (-1) = 0 。
    不同的三元组是 [-1,0,1] 和 [-1,-1,2] 。
    注意，输出的顺序和三元组的顺序并不重要。
    
    示例 2：
    输入：nums = [0,1,1]
    输出：[]
    解释：唯一可能的三元组和不为 0 。
    
    示例 3：
    输入：nums = [0,0,0]
    输出：[[0,0,0]]
    解释：唯一可能的三元组和为 0 。
*/


#include <vector>
#include <algorithm>

// std::vector<std::vector<int>> threeSum(std::vector<int>& nums)
// {
//     auto size = std::size(nums);

//     // 先排序，后续使用二分查找
//     std::ranges::sort(nums);
//     std::vector<std::vector<int>> result{};
//     for(size_t i = 0; i < size - 2; ++i){
//         // 若当前元素大于 0，则后续元素也大于 0，不可能满足条件，直接退出循环
//         if(nums[i] > 0)
//             break;
//         for(size_t j = i + 1; j < size; ++j){
//             auto sum = nums[i] + nums[j];
//             if(sum <= 0){
//                 // 查找余数
//                 auto it = std::lower_bound(std::begin(nums) + j + 1, std::end(nums), -sum);
//                 if(it != std::end(nums) && *it == -sum) {
//                     result.push_back({nums[i], nums[j], *it});
//                 }
//             }
//             // 跳过重复的元素
//             while(j + 1 < size && nums[j] == nums[j + 1])
//                 ++j;
//         }
//         // 跳过重复的元素
//         while(i + 1 < size && nums[i] == nums[i + 1])
//             ++i;
//     }

//     return result;
// }


std::vector<std::vector<int>> threeSum(std::vector<int>& nums)
{
    auto size = std::size(nums);

    // 先排序，后续使用双指针
    std::ranges::sort(nums);
    std::vector<std::vector<int>> result{};
    for(size_t i = 0; i < size - 2; ++i){
        // 跳过重复的元素
        if(i > 0 && nums[i] == nums[i - 1])
            continue;
        // 若当前元素大于 0，则后续元素也大于 0，不可能满足条件
        if(nums[i] > 0)
            break;
        
        size_t left = i + 1, right = size - 1;
        while (left < right) {
            auto sum = nums[i] + nums[left] + nums[right];
            if(sum == 0){
                result.push_back({nums[i], nums[left], nums[right]});
                // 跳过重复的元素
                while(left < right && nums[left] == nums[left + 1])
                    ++left;
                while(left < right && nums[right] == nums[right - 1])
                    --right;
                ++left;
                --right;
            }
            else if(sum < 0){
                ++left;
            }
            else{
                --right;
            }
        }
    }
    
    return result;
}

int main()
{
    std::vector nums = {-1,0,1,2,-1,-4};
    auto result = threeSum(nums);
    for(const auto& combination : result) {
        for(int num : combination) {
            printf("%d ", num);
        }
        printf("\n");
    }
    return 0;
}
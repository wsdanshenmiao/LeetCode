/*
    80. 删除有序数组中的重复项 II
    给你一个有序数组 nums ，请你 原地 删除重复出现的元素，使得出现次数超过两次的元素只出现两次 ，返回删除后数组的新长度。
    不要使用额外的数组空间，你必须在 原地 修改输入数组 并在使用 O(1) 额外空间的条件下完成。

    说明：
    为什么返回数值是整数，但输出的答案是数组呢？
    请注意，输入数组是以「引用」方式传递的，这意味着在函数里修改输入数组对于调用者是可见的。
    你可以想象内部操作如下:

    // nums 是以“引用”方式传递的。也就是说，不对实参做任何拷贝
    int len = removeDuplicates(nums);

    // 在函数里修改输入数组对于调用者是可见的。
    // 根据你的函数返回的长度, 它会打印出数组中 该长度范围内 的所有元素。
    for (int i = 0; i < len; i++) {
        print(nums[i]);
    }
    
    示例 1：
    输入：nums = [1,1,1,2,2,3]
    输出：5, nums = [1,1,2,2,3]
    解释：函数应返回新长度 length = 5, 并且原数组的前五个元素被修改为 1, 1, 2, 2, 3。 不需要考虑数组中超出新长度后面的元素。
    
    示例 2：
    输入：nums = [0,0,1,1,1,1,2,3,3]
    输出：7, nums = [0,0,1,1,2,3,3]
    解释：函数应返回新长度 length = 7, 并且原数组的前七个元素被修改为 0, 0, 1, 1, 2, 3, 3。不需要考虑数组中超出新长度后面的元素。
    
    提示：
    1 <= nums.length <= 3 * 104
    -104 <= nums[i] <= 104
    nums 已按升序排列
*/

#include <vector>
#include <print>

template<std::size_t Version = 0>
int removeDuplicates(std::vector<int>& nums);

template<>
int removeDuplicates<0>(std::vector<int>& nums)
{
    std::size_t size = std::size(nums);
    if(size <= 2)
        return size;

    auto removeRepet = [&nums, &size](auto begin, auto end) {
        size -= std::distance(begin, end);
        auto it = nums.erase(begin, end);
        return it;
    };

    std::size_t repetNum = 1;
    int pre = nums[0];
    for(auto it = std::begin(nums) + 1; it != std::end(nums);){
        if(*it == pre){
            ++repetNum;
            ++it;
        }
        else { 
            pre = *it;
            if (repetNum > 2)
                it = removeRepet(std::prev(it, repetNum - 2), it);
            ++it;
            repetNum = 1;
        }
    }

    if (repetNum > 2)
	    removeRepet(std::prev(std::end(nums), repetNum - 2), std::end(nums));

    return size;
}

template<>
int removeDuplicates<1>(std::vector<int>& nums)
{
    std::size_t index = 0;
    for(const auto& num : nums){
        if(index < 2 || num != nums[index - 2])
            nums[index++] = num;
    }

    return index;
}

int main()
{
    std::vector<int> nums{0,0,1,1,1,1,2,3,3};
    int len = removeDuplicates(nums);
    std::println("len = {}, nums = {}", len, nums);
    std::vector<int> nums2{1,1,1};
    len = removeDuplicates(nums2);
    std::println("len = {}, nums = {}", len, nums2);
    return 0;
}
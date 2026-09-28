/*
    33. 搜索旋转排序数组
    整数数组 nums 按升序排列，数组中的值 互不相同 。
    在传递给函数之前，nums 在预先未知的某个下标 k（0 <= k < nums.length）上进行了 向左旋转，
    使数组变为 [nums[k], nums[k+1], ..., nums[n-1], nums[0], nums[1], ..., nums[k-1]]（下标 从 0 开始 计数）。
    例如， [0,1,2,4,5,6,7] 下标 3 上向左旋转后可能变为 [4,5,6,7,0,1,2] 。
    给你 旋转后 的数组 nums 和一个整数 target ，如果 nums 中存在这个目标值 target ，则返回它的下标，否则返回 -1 。
    你必须设计一个时间复杂度为 O(log n) 的算法解决此问题。

    示例 1：
    输入：nums = [4,5,6,7,0,1,2], target = 0
    输出：4

    示例 2：
    输入：nums = [4,5,6,7,0,1,2], target = 3
    输出：-1

    示例 3：
    输入：nums = [1], target = 0
    输出：-1
*/

#include <vector>
#include <algorithm>
#include <span>

// int search(std::vector<int>& nums, int target) 
// {
//     size_t size = std::size(nums);
//     if(size <= 0){
//         return -1;
//     }

// 	// 若有序则直接二分查找
//     auto findTarget = [](const std::span<int>& arr, int target) -> int {
//         auto it = std::lower_bound(std::begin(arr), std::end(arr), target);
//         if (it != std::end(arr) && *it == target) {
//             return std::distance(std::begin(arr), it);
//         }
//         return -1;
//     };

//     if (nums.back() >= nums.front()) {
// 		return findTarget(nums, target);
//     }

//     // 查找旋转点
//     size_t left = 0, right = size - 1;
//     while (left < right) {
//         auto mid = left + (right - left) / 2;
//         // 旋转点一定比前一个元素和后一个元素都小
//         if ((nums[mid] <= nums[std::max(mid, 1uz) - 1] &&
//             nums[mid] <= nums[std::min(mid + 1, size - 1)])) {
//             left = mid;
//             break;
//         }
//         if(nums[mid] >= nums.front()){
//             left = mid + 1;
//         }else{
//             right = mid;
//         }
//     }
//     printf("mid: %zu\n", left);

//     // 根据目标决定在哪个区间进行二分查找
//     right = target < nums.front() ? size - 1 : std::max(left, 1uz) - 1;
//     left = target < nums.front() ? left : 0;
//     auto dist = findTarget(std::span<int>(nums.data() + left, right - left + 1), target);
//     return dist == -1 ? -1 : left + dist;
// }


int search(std::vector<int>& nums, int target) 
{
    size_t size = std::size(nums);
    if(size <= 0){
        return -1;
    }

    size_t left = 0, right = size - 1;
    while (left <= right){
        auto mid = left + (right - left) / 2;
        // 二分后有一边有序有一边无序
        bool rightSorted = nums[mid] < nums[left];
        size_t sortedLeft = left;
        size_t sortedRight = mid;
        left = mid + 1;
        // 判断哪边是有序的
        if(rightSorted && left <= right){
            std::swap(left, sortedLeft);
            std::swap(right, sortedRight);
        }
        if(nums[sortedLeft] <= target && target <= nums[sortedRight]){
            // 元素在有序的一侧，使用二分查找
            auto endIt = std::begin(nums) + sortedRight + 1;
            auto it = std::lower_bound(std::begin(nums) + sortedLeft, endIt, target);
            // 如果没有找到或者找到的元素不等于目标值，则返回 -1，否则返回元素的下标
            return (it == endIt) || (*it != target) ? -1 : std::distance(std::begin(nums), it);
        }
    }

    return -1;
}

int main()
{
    std::vector<int> nums = { 1,3,5 };
    printf("result: %d", search(nums, 2));
    return 0;
}
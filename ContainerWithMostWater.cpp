/*
    11. 盛最多水的容器
    给定一个长度为 n 的整数数组 height 。有 n 条垂线，第 i 条线的两个端点是 (i, 0) 和 (i, height[i]) 。
    找出其中的两条线，使得它们与 x 轴共同构成的容器可以容纳最多的水。
    返回容器可以储存的最大水量。
    说明：你不能倾斜容器。

    示例 1：
    输入：[1,8,6,2,5,4,8,3,7]
    输出：49 
    解释：图中垂直线代表输入数组 [1,8,6,2,5,4,8,3,7]。在此情况下，容器能够容纳水（表示为蓝色部分）的最大值为 49。

    示例 2：
    输入：height = [1,1]
    输出：1
*/

#include <vector>

// int maxArea(std::vector<int>& height)
// {
//     int maxArea = 0;
//     for(size_t i = 0; i < std::size(height); ++i){
//         for(size_t j = std::max(i + 1, size_t(maxArea / std::max(height[i], 1))); j < std::size(height); ++j){
//             int area = std::min(height[i], height[j]);
//             area *= (j - i);
//             maxArea = std::max(maxArea, area);
//         }
//     }
//     return maxArea;
// }

int maxArea(std::vector<int>& height)
{
    if(std::empty(height)){
        return 0;
    }

    int maxArea = 0;
    size_t left = 0, right = std::size(height) - 1;
    while (left < right) {
        int len = int(right - left);
        maxArea = std::max(maxArea, len * std::min(height[left], height[right]));
        if(height[left] < height[right]){
            ++left;
        }
        else{
            --right;
        }
    }
    
    return maxArea;
}


int main()
{
    std::vector<int> height{1,8,6,2,5,4,8,3,7};
    printf("result: %d", maxArea(height));
    return 0;
}
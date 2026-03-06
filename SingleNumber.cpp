/*
    137. 只出现一次的数字 II
    给你一个整数数组 nums ，除某个元素仅出现 一次 外，其余每个元素都恰出现 三次 。请你找出并返回那个只出现了一次的元素。
    你必须设计并实现线性时间复杂度的算法且使用常数级空间来解决此问题。

    示例 1：
    输入：nums = [2,2,3,2]
    输出：3
    
    示例 2：
    输入：nums = [0,1,0,1,0,1,99]
    输出：99
*/


#include <vector>
#include <unordered_map>

int singleNumber(std::vector<int>& nums) 
{
    // 使用哈希表有 O(n) 的空间复杂度
    std::unordered_map<int, int> count;
    for(const int& num : nums){
        ++count[num];
    }
    for(const auto& pair : count){
        if(pair.second == 1){
            return pair.first;
        }
    }
    return 0;
}


int singleNumber(std::vector<int>& nums) 
{
    int result = 0;
    // 计算每一个位
    for(int i = 0; i < 32; ++i){
        // 统计第 i 位上 1 的个数
        int count = 0;
        for(const int& num : nums){
            count += (num >> i) & 1;
        }
        // 由于除了一个元素外，其余元素都出现了三次，所以排除独立的元素，其他元素该位上 1 的个数一定是 3 的倍数
        // 因此 count % 3 的结果就取决于独立的元素该位上是 0 还是 1
        if(count % 3 != 0){
            result |= (1 << i);
        }
    }
    return result;
}

int singleNumber(std::vector<int>& nums) 
{
    int ones = 0, twos = 0;
    for(const int& num : nums){
        // 更新 ones 和 twos 的值
        ones = (ones ^ num) & ~twos;
        twos = (twos ^ num) & ~ones;
    }
    return ones;
}

int main()
{
    std::vector<int> nums = {2,2,3,2};
    printf("result: %d\n", singleNumber(nums));
    return 0;
}
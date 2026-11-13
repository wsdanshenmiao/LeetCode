/*
    556. 下一个更大元素 III
    给你一个正整数 n ，请你找出符合条件的最小整数，
    其由重新排列 n 中存在的每位数字组成，并且其值大于 n 。如果不存在这样的正整数，则返回 -1 。
    注意 ，返回的整数应当是一个 32 位整数 ，如果存在满足题意的答案，但不是 32 位整数 ，同样返回 -1 。

    示例 1：
    输入：n = 12
    输出：21
    
    示例 2：
    输入：n = 21
    输出：-1
    
    提示：
    1 <= n <= 231 - 1
*/

#include <queue>
#include <print>
#include <algorithm>

int nextGreaterElement(int n)
{
    std::vector<int> digits{};
    int num = n;
    size_t size = 0;
    // 将数字拆分为各个位数
    while(num > 0){
        digits.push_back(num % 10);
        num /= 10;
        ++size;
    }
    std::ranges::sort(digits);

    auto func = [n, size](
        this auto&& self, 
        int64_t result, 
        size_t index, 
        bool isGreater,
        std::vector<int>& digits){
        if(index == size){
            return result > n ? result : -1;
        }

        int digit = static_cast<int>(n / std::pow(10, size - index - 1)) % 10;
        // 若已经比原数字大，则从剩余的数字中选择最小的一个
        if(isGreater){
            auto val = digits.front();
            digits.erase(digits.begin());
            result = self(result * 10 + val, index + 1, isGreater, digits);
            digits.insert(digits.begin(), val);
        }
        else{
            // 从剩余的数字中选择大于等于当前位的最小数字
            auto lowerIt = std::ranges::lower_bound(digits, digit);
            if(lowerIt == digits.end()){
                return std::int64_t(-1);
            }
            int val = *lowerIt;
            digits.erase(lowerIt);
            auto tmp = self(result * 10 + val, index + 1, val != digit, digits);

            // 若选取的数字等于当前位，则继续选择下一位
            if(tmp == -1 && val == digit){
                auto upperIt = std::ranges::upper_bound(digits, digit);
                if(upperIt != digits.end()){
                    auto upperVal = *upperIt;
                    tmp = result * 10 + upperVal;
                    *upperIt = val;
                    tmp = self(tmp, index + 1, true, digits);
                    val = upperVal;
                }
            }
            auto upperIt = std::ranges::upper_bound(digits, digit);
            digits.insert(upperIt, val);

            result = tmp;
        }
        return result;
    };

    auto result = func(0, 0, false, digits);
    return result > std::numeric_limits<int>::max() ? -1 : result;
}

int main()
{
    int n = 2147483476;
    std::println("n: {}, result: {}", n, nextGreaterElement(n));
    return 0;
}
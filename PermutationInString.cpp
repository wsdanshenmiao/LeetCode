/*
    567. 字符串的排列
    给你两个字符串 s1 和 s2 ，写一个函数来判断 s2 是否包含 s1 的 排列。
    如果是，返回 true ；否则，返回 false 。
    换句话说，s1 的排列之一是 s2 的 子串 。

    示例 1：
    输入：s1 = "ab" s2 = "eidbaooo"
    输出：true
    解释：s2 包含 s1 的排列之一 ("ba").
    
    示例 2：
    输入：s1= "ab" s2 = "eidboaoo"
    输出：false
    
    提示：
    1 <= s1.length, s2.length <= 104
    s1 和 s2 仅包含小写字母
*/

#include <string>
#include <array>
#include <print>

bool checkInclusion(std::string s1, std::string s2)
{
    if(s1.size() > s2.size())
        return false;

    constexpr size_t s_StrSize = 26;
    std::array<size_t, s_StrSize> map1{}, map2{};
    auto getIndex = [](char c) -> size_t { return c - 'a'; };

    for(size_t i = 0; i < s1.size(); ++i){
        ++map1[getIndex(s1[i])];
        ++map2[getIndex(s2[i])];
    }

    bool result = false;
    for(size_t left = 0, right = s1.size() - 1; right < s2.size(); ++left, ++right){
        if(map1 == map2){
            result = true;
            break;
        }

        --map2[getIndex(s2[left])];
        if(right + 1 < s2.size())
            ++map2[getIndex(s2[right + 1])];
    }

    return result;
}

int main()
{
    std::string s1 = "adc", s2 = "dcda";
    bool result = checkInclusion(s1, s2);
    std::println("result = {}", result);
    return 0;
}
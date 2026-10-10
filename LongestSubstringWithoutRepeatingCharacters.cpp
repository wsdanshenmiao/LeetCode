/*
    3. 无重复字符的最长子串
    给定一个字符串 s ，请你找出其中不含有重复字符的最长子串的长度。

    示例 1:
    输入: s = "abcabcbb"
    输出: 3 
    解释: 因为无重复字符的最长子串是 "abc"，所以其长度为 3。注意 "bca" 和 "cab" 也是正确答案。
    
    示例 2:
    输入: s = "bbbbb"
    输出: 1
    解释: 因为无重复字符的最长子串是 "b"，所以其长度为 1。
    
    示例 3:
    输入: s = "pwwkew"
    输出: 3
    解释: 因为无重复字符的最长子串是 "wke"，所以其长度为 3。
        请注意，你的答案必须是 子串 的长度，"pwke" 是一个子序列，不是子串。

    提示：
    0 <= s.length <= 105
    s 由英文字母、数字、符号和空格组成
*/

#include <string>
#include <ranges>
#include <print>
#include <unordered_set>

template<std::size_t Version = 0>
int lengthOfLongestSubstring(std::string s);

template<>
int lengthOfLongestSubstring<0>(std::string s)
{
    std::size_t maxLength{};
    // 记录先前出现的字符
    std::unordered_set<char> charSet{};
    for(std::size_t i = 0; i < std::size(s); ++i){
        for(std::size_t j = i; j < std::size(s); ++j){
            if(charSet.contains(s[j])){
                charSet.clear();
                break;
            }
            maxLength = std::max(maxLength, j - i + 1);
            charSet.insert(s[j]);
        }
    }
    return maxLength;
}

template<>
int lengthOfLongestSubstring<1>(std::string s)
{
    std::size_t right{};
    std::size_t maxLength{};
    // 记录先前出现的字符
    std::unordered_set<char> charSet{};
    for(std::size_t left = 0; left < std::size(s); ++left){
        while(right < std::size(s) && !charSet.contains(s[right])){
            charSet.insert(s[right]);
            ++right;
        }
        maxLength = std::max(maxLength, right - left);
        charSet.erase(s[left]);
    }
    return maxLength;
}

int main()
{
    constexpr std::size_t Version = 1;
    std::string s = "abcabcbb";
    int length = lengthOfLongestSubstring<Version>(s);
    std::println("{} -> {}", s, length);
    std::string s2 = "bbbbb";
    length = lengthOfLongestSubstring<Version>(s2);
    std::println("{} -> {}", s2, length);
    std::string s3 = "pwwkew";
    length = lengthOfLongestSubstring<Version>(s3);
    std::println("{} -> {}", s3, length);
    return 0;
}
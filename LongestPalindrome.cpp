/*
    5. 最长回文子串
    给你一个字符串 s，找到 s 中最长的 回文 子串。

    示例 1：
    输入：s = "babad"
    输出："bab"
    解释："aba" 同样是符合题意的答案。
    
    示例 2：
    输入：s = "cbbd"
    输出："bb"
*/


#include <string>
#include <cstdio>
#include <vector>


/*
    version 1
    要求求 n 个字符 s 的最长回文子串，可将该问题分解为以下子问题：
    1. 求包含 s[i] 的最长回文子串。
    2. 判断包含 s[i] 的回文子串是否长于 n - 1 个字符的最长回文子串。
    3. 若更长则更新 n 个字符 s 的最长回文子串。
    
    边界条件为 n < 2 时，最长回文子串为 s 本身。
*/

// // 判断字符串是否为回文串
// bool isPalindrome(std::string_view s)
// {
//     if(s.empty())
// 		return true;
//     for(auto left = std::begin(s), right = std::prev(std::end(s)); left < right; ++left, --right){
//         if(*left != *right)
//             return false;
//     }
//     return true;
// }

// std::string longestPalindrome(std::string s)
// {
//     if(std::size(s) < 2)
//         return s;

//     std::string result{s[0]};
//     for(auto it = std::next(std::begin(s)); it != std::end(s); std::advance(it, 1)){
//         // 查找包含当前字符的最长回文子串
//         for(auto curr_it = std::begin(s); curr_it != it; std::advance(curr_it, 1)){
//             // 判断当前字串是否是回文串
//             if (auto sub_str = std::string_view{curr_it, std::next(it)}; isPalindrome(sub_str)) {
//                 // 若当前回文子串长于 result，则更新 result
//                 if(std::size(result) - 1 < std::distance(curr_it, it)){
//                     result = sub_str;
//                 }
//             }
//         }
//     }

//     return result;
// }



std::string longestPalindrome(std::string s)
{
    auto max_begin = std::begin(s), max_end = std::begin(s);
    // 遍历所有元素
    for(auto it = std::begin(s); it != std::end(s); std::advance(it, 1)){
        auto left = it, right = it;
        // 向左查找重复元素构成的回文子串
        while (left != std::begin(s) && *std::prev(left) == *right) {
            std::advance(left, -1);
        }

        // 两边扩展搜索回文子串
        while(left != std::begin(s) && right != std::prev(std::end(s)) && *std::prev(left) == *std::next(right)){
            std::advance(left, -1);
            std::advance(right, 1);
        }

        if(std::distance(max_begin, max_end) < std::distance(left, std::next(right))){
            max_begin = left;
            max_end = std::next(right);
        }
    }

    return std::string{max_begin, max_end};
}

int main()
{
    auto result = longestPalindrome("cbbd");
    printf("%s\n", result.c_str());
    return 0;
}
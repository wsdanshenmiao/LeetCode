/*
    97. 交错字符串
    给定三个字符串 s1、s2、s3，请你帮忙验证 s3 是否是由 s1 和 s2 交错 组成的。
    两个字符串 s 和 t 交错 的定义与过程如下，其中每个字符串都会被分割成若干 非空 子字符串：
    s = s1 + s2 + ... + sn
    t = t1 + t2 + ... + tm
    |n - m| <= 1
    交错 是 s1 + t1 + s2 + t2 + s3 + t3 + ... 或者 t1 + s1 + t2 + s2 + t3 + s3 + ...
    注意：a + b 意味着字符串 a 和 b 连接。

    示例 1：
    输入：s1 = "aabcc", s2 = "dbbca", s3 = "aadbbcbcac"
    输出：true

    示例 2：
    输入：s1 = "aabcc", s2 = "dbbca", s3 = "aadbbbaccc"
    输出：false

    示例 3：
    输入：s1 = "", s2 = "", s3 = ""
    输出：true
*/

#include <string>
#include <vector>
#include <array>

// // 超时
// bool isInterleave(std::string_view s1, std::string_view s2, std::string_view s3)
// {
//     if(std::size(s1) + std::size(s2) != std::size(s3))
//         return false;
//     if(std::empty(s1) || std::empty(s2) || std::empty(s3))
//         return s1 == s3 || s2 == s3;

//     std::string_view sub1{s1.data(), s1.size() - 1};
//     std::string_view sub2{s2.data(), s2.size() - 1};
//     std::string_view sub3{s3.data(), s3.size() - 1};
//     if(s1.back() != s3.back() && s2.back() != s3.back())
//         return false;
// 	bool result = isInterleave(sub1, s2, sub3) && s1.back() == s3.back();
//     if (!result) {
// 		result = isInterleave(s1, sub2, sub3) && s2.back() == s3.back();
//     }
//     return result;
// }


// bool isInterleave(std::string s1, std::string s2, std::string s3)
// {
//     return isInterleave(std::string_view{s1}, std::string_view{s2}, std::string_view{s3});
// }

bool isInterleave(std::string s1, std::string s2, std::string s3)
{
    if(std::size(s1) + std::size(s2) != std::size(s3))
        return false;
    if(std::empty(s1) || std::empty(s2) || std::empty(s3))
        return s1 == s3 || s2 == s3;
    std::vector<bool> row(std::size(s2) + 1, false);
    std::array<std::vector<bool>, 2> dp({row, row});
    dp[0][0] = true;
    for(size_t i = 0; i <= std::size(s1); ++i){
        auto& curr = dp[i % 2];
        auto& prev = dp[(i + 1) % 2];
        curr[0] = i > 0 ? prev[0] && s1[i - 1] == s3[i - 1] : true;
        for(size_t j = 0; j <= std::size(s2); ++j){
            if(i > 0){
                curr[j] = prev[j] && s1[i - 1] == s3[i + j - 1];
            }
            if(j > 0 && !curr[j]){
                curr[j] = curr[j - 1] && s2[j - 1] == s3[i + j - 1];
            }
        }
    }
    return dp[std::size(s1) % 2].back();
}


int main()
{
    std::string s1 = "aa", 
        s2 = "ab", 
        s3 = "aaab";
    bool result = isInterleave(s1, s2, s3);
    printf("%s\n", result ? "true" : "false");
    return 0;
}
/*
    151. 反转字符串中的单词
    给你一个字符串 s ，请你反转字符串中 单词 的顺序。
    单词 是由非空格字符组成的字符串。s 中使用至少一个空格将字符串中的 单词 分隔开。
    返回 单词 顺序颠倒且 单词 之间用单个空格连接的结果字符串。
    注意：输入字符串 s中可能会存在前导空格、尾随空格或者单词间的多个空格。
    返回的结果字符串中，单词间应当仅用单个空格分隔，且不包含任何额外的空格。

    示例 1：
    输入：s = "the sky is blue"
    输出："blue is sky the"

    示例 2：
    输入：s = "  hello world  "
    输出："world hello"
    解释：反转后的字符串中不能存在前导空格和尾随空格。
    
    示例 3：
    输入：s = "a good   example"
    输出："example good a"
    解释：如果两个单词间有多余的空格，反转后的字符串需要将单词间的空格减少到仅有一个。
*/


#include <string>
#include <ranges>

// std::string reverseWords(std::string s)
// {
//     auto words = s | std::views::split(' ');
//     std::string result{};
//     for(const auto& word : words){
//         if(!word.empty()){
//             result = (word | std::ranges::to<std::string>()) + (result.empty() ? "" : " ") + result;
//         }
//     }
//     return result;
// }

std::string reverseWords(std::string s)
{
    auto removeEndSpaces = [](std::string& str) {
        while (!str.empty() && str.back() == ' ') {
            str.pop_back();
        }
    };
    // 移除尾部的空格
    removeEndSpaces(s);
    if(std::empty(s)){
        return s;
	}

    std::reverse(s.begin(), s.end());
    // 记录每个单词的起始位置
    ptrdiff_t lastEnd = 0;
    for(size_t i = 0; i < std::size(s); ++i){
		bool isLast = (i == std::size(s) - 1);
        if(s[i] == ' ' || isLast){
            std::reverse(std::begin(s) + lastEnd, 
                (isLast && s[i] != ' ') ? std::end(s) : std::begin(s) + i);
            lastEnd = i - 1;
            // 移除单词之间的多余空格
            while (lastEnd > 0 && s[lastEnd] == ' ') {
                lastEnd--;
            }
            lastEnd += 2;
        }
    }
    removeEndSpaces(s);
    
    return s;
}

int main()
{
    auto result = reverseWords(" asdasd df f");
    printf("result: %s", result.c_str());
    return 0;
}
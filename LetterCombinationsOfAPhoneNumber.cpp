/*
    17. 电话号码的字母组合
    给定一个仅包含数字 2-9 的字符串，返回所有它能表示的字母组合。答案可以按 任意顺序 返回。
    给出数字到字母的映射如下（与电话按键相同）。注意 1 不对应任何字母。

    1：不对应任何字母
    2：abc
    3：def
    4：ghi
    5：jkl
    6：mno
    7：pqrs
    8：tuv
    9：wxyz

    示例 1：
    输入：digits = "23"
    输出：["ad","ae","af","bd","be","bf","cd","ce","cf"]
    
    示例 2：
    输入：digits = "2"
    输出：["a","b","c"]
    
    提示：
    1 <= digits.length <= 4
    digits[i] 是范围 ['2', '9'] 的一个数字。
*/

#include <vector>
#include <string>
#include <array>
#include <print>

template<std::size_t Version = 0>
std::vector<std::string> letterCombinations(std::string digits);

template<>
std::vector<std::string> letterCombinations<0>(std::string digits)
{
    static constexpr std::array<std::string_view, 10> mapping{
        "",     // 0
        "",     // 1
        "abc",  // 2
        "def",  // 3
        "ghi",  // 4
        "jkl",  // 5
        "mno",  // 6
        "pqrs", // 7
        "tuv",  // 8
        "wxyz"  // 9
    };

    std::vector<std::string> result{};
    auto backtrack = [&result](this auto&& self, const std::string& digits, std::size_t index, std::string& current){
        if(index >= digits.size()){
            result.push_back(current);
            return;
        }

        std::size_t digit = digits[index] - '0';
        for(const auto& letter : mapping[digit]){
            current.push_back(letter);
            self(digits, index + 1, current);
            current.pop_back();
        }
    };

    if(!digits.empty()){
        std::string current{};
        backtrack(digits, 0, current);
    }

    return result;
}

template<>
std::vector<std::string> letterCombinations<1>(std::string digits)
{
    static constexpr std::array<std::string_view, 10> mapping{
        "",     // 0
        "",     // 1
        "abc",  // 2
        "def",  // 3
        "ghi",  // 4
        "jkl",  // 5
        "mno",  // 6
        "pqrs", // 7
        "tuv",  // 8
        "wxyz"  // 9
    };

    std::vector<std::string> result{};
    

    return result;
}

int main()
{
    std::string digits = "23";
    std::vector<std::string> combinations = letterCombinations(digits);
    std::println("Letter combinations for digits '{}':", digits);
    std::println("[{}]", combinations);
    std::string digits2 = "2";
    std::vector<std::string> combinations2 = letterCombinations(digits2);
    std::println("Letter combinations for digits '{}':", digits2);
    std::println("[{}]", combinations2);
    return 0;
}
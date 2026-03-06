/*
    49. 字母异位词分组
    给你一个字符串数组，请你将 字母异位词 组合在一起。可以按任意顺序返回结果列表。

    示例 1:
    输入: strs = ["eat", "tea", "tan", "ate", "nat", "bat"]
    输出: [["bat"],["nat","tan"],["ate","eat","tea"]]
    解释：
    在 strs 中没有字符串可以通过重新排列来形成 "bat"。
    字符串 "nat" 和 "tan" 是字母异位词，因为它们可以重新排列以形成彼此。
    字符串 "ate" ，"eat" 和 "tea" 是字母异位词，因为它们可以重新排列以形成彼此。

    示例 2:
    输入: strs = [""]
    输出: [[""]]

    示例 3:
    输入: strs = ["a"]
    输出: [["a"]]
*/

#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>

std::vector<std::vector<std::string>> groupAnagrams(std::vector<std::string>& strs) 
{
    if(std::size(strs) <= 1){
        return {strs};
    }
    
    std::unordered_map<std::string, size_t> indexMap{};
    std::vector<std::vector<std::string>> result{};
    for(auto& str : strs){
        auto sortedStr = str;
        std::sort(std::begin(sortedStr), std::end(sortedStr));
        if(indexMap.contains(sortedStr)){
            result[indexMap[sortedStr]].push_back(str);
        }
        else{
            result.push_back({str});
            indexMap[sortedStr] = std::size(result) - 1;
        }
    }

    return result;
}

int main()
{
    std::vector<std::string> strs{"eat", "tea", "tan", "ate", "nat", "bat"};
    auto result = groupAnagrams(strs);
    for(const auto& group : result){
        for(const auto& str : group){
            printf("%s ", str.c_str());
        }
        printf("\n");
    }
    return 0;
}
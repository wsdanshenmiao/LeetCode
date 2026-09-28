/*
    211. 添加与搜索单词 - 数据结构设计
    提示
    请你设计一个数据结构，支持 添加新单词 和 查找字符串是否与任何先前添加的字符串匹配 。

    实现词典类 WordDictionary ：
    WordDictionary() 初始化词典对象
    void addWord(word) 将 word 添加到数据结构中，之后可以对它进行匹配
    bool search(word) 如果数据结构中存在字符串与 word 匹配，则返回 true ；否则，返回  false 。
    word 中可能包含一些 '.' ，每个 . 都可以表示任何一个字母。
    
    示例：
    输入：
    ["WordDictionary","addWord","addWord","addWord","search","search","search","search"]
    [[],["bad"],["dad"],["mad"],["pad"],["bad"],[".ad"],["b.."]]
    输出：
    [null,null,null,null,false,true,true,true]

    解释：
    WordDictionary wordDictionary = new WordDictionary();
    wordDictionary.addWord("bad");
    wordDictionary.addWord("dad");
    wordDictionary.addWord("mad");
    wordDictionary.search("pad"); // 返回 False
    wordDictionary.search("bad"); // 返回 True
    wordDictionary.search(".ad"); // 返回 True
    wordDictionary.search("b.."); // 返回 True
    
    提示：
    1 <= word.length <= 25
    addWord 中的 word 由小写英文字母组成
    search 中的 word 由 '.' 或小写英文字母组成
    最多调用 104 次 addWord 和 search
*/

#include <string>
#include <string_view>
#include <vector>
#include <print>
#include <memory>
#include <array>
#include <cassert>
#include <cstdint>
#include <ranges>
#include <bitset>

template <std::size_t Version>
class WordDictionary;

template<>
class WordDictionary<0>
{
public:
    WordDictionary() {}
    
    void addWord(std::string word)
    {
        m_Words.push_back(word);
    }

    bool search(std::string word)
    {
        bool exist = false;
        // 遍历所有添加的单词，检测是否又匹配的单词
        for(const auto& w : m_Words){
            size_t wordIndex = 0;
            for(const auto& c : w){
                // 字母相同，或者 word 中的字符为 '.'，则继续匹配
                if(c == word[wordIndex] || word[wordIndex] == '.'){
                    ++wordIndex;
                }
                else{
                    // 如果不匹配，重置索引
                    wordIndex = 0;
                }

                if(wordIndex == std::size(word) && wordIndex == std::size(w)){
                    exist = true;
                    break;
                }
            }
            // 如果已经找到匹配的单词，则直接跳出循环
            if(exist){
                break;
            }
        }

        return exist;
    }

private:
    std::vector<std::string> m_Words{};
};

template<>
class WordDictionary<1>
{
public:
    WordDictionary()
    {
        m_Pool.emplace_back();
    }

    void addWord(std::string word)
    {
        std::uint32_t nodeIndex = sm_RootIndex;
        for(const char& c : word){
            size_t index = c - 'a';
            assert(index < sm_MaxChildren);
            if(auto childIndex = m_Pool[nodeIndex].children[index]; childIndex != sm_InvalidIndex){
                nodeIndex = childIndex;
            }
            else{
                const auto newIndex = static_cast<std::uint32_t>(m_Pool.size());
                m_Pool[nodeIndex].children[index] = newIndex;
                nodeIndex = newIndex;
                m_Pool.emplace_back();
            }
        }
        m_Pool[nodeIndex].isEnd = true;
    }

    bool search(std::string word)
    {
        return searchInNode(word, sm_RootIndex);
    }
    
    bool searchInNode(std::string_view word, std::uint32_t nodeIndex)
    {
        if(word.empty()){
            return nodeIndex != sm_InvalidIndex && m_Pool[nodeIndex].isEnd;
        }

        std::size_t wordIndex = word[0] - 'a';
        if(word[0] == '.'){
            for(const auto& [index , child] : m_Pool[nodeIndex].children | std::views::enumerate){
                // 如果子节点不为空，则继续进行匹配
                if(child != sm_InvalidIndex && searchInNode(word.substr(1), child)){
                    return true;
                }
            }
        }
        else{
            // 如果当前字符不是通配符，则检查对应的子节点
            if(m_Pool[nodeIndex].children[wordIndex] != sm_InvalidIndex){
                return searchInNode(word.substr(1), m_Pool[nodeIndex].children[wordIndex]);
            }
        }

        return false;
    }

private:
    static constexpr std::size_t sm_MaxChildren = 26;
    static constexpr std::uint32_t sm_InvalidIndex = std::uint32_t(-1);
    static constexpr std::uint32_t sm_RootIndex = 0;
    
    struct TrieNode
    {
        std::array<std::uint32_t, sm_MaxChildren> children;
        bool isEnd = false;

        TrieNode()
        {
            children.fill(sm_InvalidIndex);
        }
    };

    std::vector<TrieNode> m_Pool{};
};

int main()
{
    constexpr std::size_t version = 1;
    WordDictionary<version> wordDictionary;
    wordDictionary.addWord("bad");
    wordDictionary.addWord("dad");
    wordDictionary.addWord("mad");
    std::println("{}", wordDictionary.search("pad")); // 返回 False
    std::println("{}", wordDictionary.search("bad")); // 返回 True
    std::println("{}", wordDictionary.search(".ad")); // 返回 True
    std::println("{}", wordDictionary.search("b..")); // 返回 True
    return 0;
}

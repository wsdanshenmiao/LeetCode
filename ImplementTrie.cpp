/*
    208. 实现 Trie (前缀树)
    Trie（发音类似 "try"）或者说 前缀树 是一种树形数据结构，
    用于高效地存储和检索字符串数据集中的键。这一数据结构有相当多的应用情景，例如自动补全和拼写检查。

    请你实现 Trie 类：
    Trie() 初始化前缀树对象。
    void insert(String word) 向前缀树中插入字符串 word 。
    boolean search(String word) 如果字符串 word 在前缀树中，
    返回 true（即，在检索之前已经插入）；否则，返回 false 。
    boolean startsWith(String prefix) 如果之前已经插入的字符串 word 的前缀之一为 prefix ，
    返回 true ；否则，返回 false 。

    示例：
    输入
    ["Trie", "insert", "search", "search", "startsWith", "insert", "search"]
    [[], ["apple"], ["apple"], ["app"], ["app"], ["app"], ["app"]]
    输出
    [null, null, true, false, true, null, true]

    解释
    Trie trie = new Trie();
    trie.insert("apple");
    trie.search("apple");   // 返回 True
    trie.search("app");     // 返回 False
    trie.startsWith("app"); // 返回 True
    trie.insert("app");
    trie.search("app");     // 返回 True
    
    提示：
    1 <= word.length, prefix.length <= 2000
    word 和 prefix 仅由小写英文字母组成
    insert、search 和 startsWith 调用次数 总计 不超过 3 * 104 次
*/

#include <print>
#include <string>
#include <memory>
#include <ranges>
#include <vector>
#include <algorithm>

class Trie
{
    struct Node{
        std::vector<std::unique_ptr<Node>> children{};
        bool isEnd{};
        char val;
    };

public:
    Trie() : m_Root(std::make_unique<Node>()) {}
    
    void insert(std::string word) {
        auto node = m_Root.get();
        for(auto c : word){
            auto& child = node->children;
            auto it = std::ranges::upper_bound(child, c, std::less{}, getValue);
            if(it == child.begin() || (*std::prev(it))->val != c){
                // 插入新的节点
                it = child.insert(it, std::make_unique<Node>());
                (*it)->val = c;
            }
            else{
                std::advance(it, -1);
            }
            node = it->get();
        }
        node->isEnd = true;
    }
    
    bool search(std::string word) {
        return find(word, true);
    }
    
    bool startsWith(std::string prefix) {
        return find(prefix, false);
    }

private:
    static char getValue(const std::unique_ptr<Node>& node)
    {
        return node->val;
    }

    bool find(std::string word, bool wholeWord)
    {
        const Node* node = m_Root.get();
        for (char c : word) {
            auto it = std::ranges::lower_bound(node->children, c, std::less{}, getValue);
            if (it == node->children.end() || (*it)->val != c)
                return false;
            node = it->get();
        }
        return wholeWord ? node->isEnd : true;
    }

private:
    std::unique_ptr<Node> m_Root{};
};

int main()
{
    int* test0 = new int(12);
    delete[] test0;

    int* test1 = new int[1];
    delete[] test1;

    int* test2 = new int(12);
    free(test2);

    int* test3 = static_cast<int*>(malloc(sizeof(int)));
    delete test3;


    Trie trie;
    trie.insert("apple");
    std::println("{}", trie.search("apple"));   // 输出 1
    std::println("{}", trie.search("app"));     // 输出 0
    std::println("{}", trie.startsWith("app")); // 输出 1
    trie.insert("app");
    std::println("{}", trie.search("app"));     // 输出 1
    return 0;
}
/*
    173. 二叉搜索树迭代器
    实现一个二叉搜索树迭代器类BSTIterator ，表示一个按中序遍历二叉搜索树（BST）的迭代器：
    BSTIterator(TreeNode root) 初始化 BSTIterator 类的一个对象。BST 的根节点 root 会作为构造函数的一部分给出。
    指针应初始化为一个不存在于 BST 中的数字，且该数字小于 BST 中的任何元素。
    boolean hasNext() 如果向指针右侧遍历存在数字，则返回 true ；否则返回 false 。
    int next()将指针向右移动，然后返回指针处的数字。
    注意，指针初始化为一个不存在于 BST 中的数字，所以对 next() 的首次调用将返回 BST 中的最小元素。
    你可以假设 next() 调用总是有效的，也就是说，当调用 next() 时，BST 的中序遍历中至少存在一个下一个数字。

    示例：
    输入
    ["BSTIterator", "next", "next", "hasNext", "next", "hasNext", "next", "hasNext", "next", "hasNext"]
    [[[7, 3, 15, null, null, 9, 20]], [], [], [], [], [], [], [], [], []]
    输出
    [null, 3, 7, true, 9, true, 15, true, 20, false]

    解释
    BSTIterator bSTIterator = new BSTIterator([7, 3, 15, null, null, 9, 20]);
    bSTIterator.next();    // 返回 3
    bSTIterator.next();    // 返回 7
    bSTIterator.hasNext(); // 返回 True
    bSTIterator.next();    // 返回 9
    bSTIterator.hasNext(); // 返回 True
    bSTIterator.next();    // 返回 15
    bSTIterator.hasNext(); // 返回 True
    bSTIterator.next();    // 返回 20
    bSTIterator.hasNext(); // 返回 False
    
    提示：
    树中节点的数目在范围 [1, 105] 内
    0 <= Node.val <= 106
    最多调用 105 次 hasNext 和 next 操作

    进阶：
    你可以设计一个满足下述条件的解决方案吗？next() 和 hasNext() 操作均摊时间复杂度为 O(1) ，并使用 O(h) 内存。其中 h 是树的高度。
*/

#include <vector>
#include <stack>
#include <print>

 struct TreeNode
 {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 };


template<std::size_t Version>
class BSTIterator;

template<>
class BSTIterator<0> {
public:
    BSTIterator(TreeNode* root) {
        std::stack<TreeNode*> stack{};
        TreeNode* curr = root;
        while(!stack.empty() || curr != nullptr){
            while(curr != nullptr){
                stack.push(curr);
                curr = curr->left;
            }

            if(!stack.empty()){
                curr = stack.top();
                stack.pop();
                if(curr != nullptr){
                    m_Array.push_back(curr);
                    curr = curr->right;
                }
            }
        }
        for(const auto& node : m_Array){
            std::println("{}", node->val);
        }
    }
    
    int next() {
        if(hasNext()){
            return m_Array[m_Index++]->val;
        }
        return 0;
    }
    
    bool hasNext() {
        return m_Index < m_Array.size();
    }

private:
    std::vector<TreeNode*> m_Array{};
    std::size_t m_Index{};
};

template<>
class BSTIterator<1> {
public:
    BSTIterator(TreeNode* root) {
        while(root != nullptr){
            m_Path.push(root);
            root = root->left;
        }
    }

    int next() {
        if(!hasNext())
            return 0;

        TreeNode* current = m_Path.top();
        int currVal = current->val;
        if(auto node = current->right; node != nullptr){
            while(node != nullptr){
                m_Path.push(node);
                node = node->left;
            }
        }
        else{
            m_Path.pop();
            while(!m_Path.empty() && current != nullptr){
                auto top = m_Path.top();
                if(top != nullptr && current == top->left){
                    current = nullptr;
                }
                else{
                    current = top;
                    m_Path.pop();
                }
            }
        }

        return currVal;
    }
    
    bool hasNext() {
        return !m_Path.empty();
    }

private:
    // 从根节点到当前节点的路径
    std::stack<TreeNode*> m_Path{};
};

template<>
class BSTIterator<2> {
public:
    BSTIterator(TreeNode* root) {
        m_Curr = root;
    }

    int next() {
        while(m_Curr != nullptr){
            m_Path.push(m_Curr);
            m_Curr = m_Curr->left;
        }

        TreeNode* current = m_Path.top();
        m_Path.pop();
        int currVal = current->val;
        m_Curr = current->right;

        return currVal;
    }

    bool hasNext() {
        return m_Curr != nullptr || !m_Path.empty();
    }

private:
    std::stack<TreeNode*> m_Path{};
    TreeNode* m_Curr{};
};

int main()
{
    constexpr std::size_t version = 1;
    TreeNode* root = new TreeNode(7, new TreeNode(3), new TreeNode(15, new TreeNode(9), new TreeNode(20)));
    BSTIterator<version> bSTIterator = BSTIterator<version>(root);
    std::println("{}", bSTIterator.next());    // 返回 3
    std::println("{}", bSTIterator.next());    // 返回 7
    std::println("{}", bSTIterator.hasNext()); // 返回 True
    std::println("{}", bSTIterator.next());    // 返回 9
    std::println("{}", bSTIterator.hasNext()); // 返回 True
    std::println("{}", bSTIterator.next());    // 返回 15
    std::println("{}", bSTIterator.hasNext()); // 返回 True
    std::println("{}", bSTIterator.next());    // 返回 20
    std::println("{}", bSTIterator.hasNext()); // 返回 False
    return 0;
}
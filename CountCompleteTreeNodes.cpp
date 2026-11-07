/*
    222. 完全二叉树的节点个数
    给你一棵 完全二叉树 的根节点 root ，求出该树的节点个数。

    完全二叉树 的定义如下：在完全二叉树中，除了最底层节点可能没填满外，其余每层节点数都达到最大值，
    并且最下面一层的节点都集中在该层最左边的若干位置。若最底层为第 h 层（从第 0 层开始），则该层包含 1~ 2h 个节点。

    示例 1：
    输入：root = [1,2,3,4,5,6]
    输出：6

    示例 2：
    输入：root = []
    输出：0

    示例 3：
    输入：root = [1]
    输出：1

    提示：
    树中节点的数目范围是[0, 5104]
    0 <= Node.val <= 5104
    题目数据保证输入的树是 完全二叉树

    进阶：遍历树来统计节点是一种时间复杂度为 O(n) 的简单解决方案。你可以设计一个更快的算法吗？
*/

#include <queue>
#include <cmath>
#include <print>

// Definition for a binary tree node.
struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

template<size_t Version>
int countNodes(TreeNode* root);

template<>
int countNodes<0>(TreeNode* root)
{
    std::queue<TreeNode*> queue;
    queue.push(root);
    size_t count{};
    while(!queue.empty()){
        TreeNode* node = queue.back();
        queue.pop();
        if(node == nullptr)
            continue;
        
        if(node->left != nullptr)
            queue.push(node->left);
        if(node->right != nullptr)
            queue.push(node->right);
        
        count++;
    }
    return count;
}

template<>
int countNodes<1>(TreeNode* root)
{
    if(root == nullptr)
        return 0;

    auto getHeight = [](TreeNode* node){
        size_t height = 0;
        for(; node != nullptr; node = node->left, ++height);
        return height;
    };

    size_t height = getHeight(root);
    size_t count = std::pow(2, height - 1) - 1;
    size_t currHeight = 1;
    auto node = root;
    while(node != nullptr){
        size_t rightHeight = getHeight(node->right);
        if(rightHeight + currHeight == height && node->right != nullptr){
            // 往右子树走
            count += std::pow(2, rightHeight - 1);
            node = node->right;
        }
        else{
            // 往左子树走
            if(node->left == nullptr && node->right == nullptr)
                ++count;
            node = node->left;
        }
        currHeight++;
    }

    return count;
}


int main()
{
    TreeNode* root = new TreeNode(1, new TreeNode(2, new TreeNode(4), new TreeNode(5)), new TreeNode(3, new TreeNode(6), nullptr));
    int count = countNodes<1>(root);
    std::println("count: {}", count);
    return 0;
}
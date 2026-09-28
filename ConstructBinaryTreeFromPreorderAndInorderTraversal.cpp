/*
    105. 从前序与中序遍历序列构造二叉树
    给定两个整数数组 preorder 和 inorder ，其中 preorder 是二叉树的先序遍历， inorder 是同一棵树的中序遍历，请构造二叉树并返回其根节点。

    示例 1:
    输入: preorder = [3,9,20,15,7], inorder = [9,3,15,20,7]
    输出: [3,9,20,null,null,15,7]

    示例 2:
    输入: preorder = [-1], inorder = [-1]
    输出: [-1]
*/

#include <vector>
#include <span>
#include <stack>
#include <cassert>

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

// TreeNode* buildTree(std::span<const int> preorder, std::span<const int> inorder)
// {
//     if(std::empty(preorder) || std::empty(inorder)){
//         return nullptr;
//     }

//     // 前序遍历的第一个元素为根节点
//     auto root = new TreeNode{preorder[0]};

//     // 在中序遍历中找到根节点
//     auto it = std::ranges::find(inorder, preorder[0]);
//     assert(it != std::end(inorder));
//     // 在根节点处拆分为左右子树
//     std::span<const int> leftInorder{std::begin(inorder), it};
//     std::span<const int> rightInorder{std::next(it), std::end(inorder)};

//     auto rightSize = std::size(rightInorder);
//     // 在前序遍历中最右端的 n 个元素为右子树
//     std::span<const int> leftPreorder{std::next(std::begin(preorder)), std::end(preorder) - rightSize};
//     // 除了右子树与根节点以外的元素为左子树
//     std::span<const int> rightPreorder{std::end(preorder) - rightSize, std::end(preorder)};

//     root->left = buildTree(leftPreorder, leftInorder);
//     root->right = buildTree(rightPreorder, rightInorder);

//     return root;
// }

// TreeNode* buildTree(std::vector<int>& preorder, std::vector<int>& inorder)
// {
//     return buildTree(std::span{preorder}, std::span{inorder});
// }

TreeNode* buildTree(std::vector<int>& preorder, std::vector<int>& inorder)
{
    struct StackNode{
        TreeNode* node{};
        bool isLeft{};
        std::span<const int> preorder{};
        std::span<const int> inorder{};
    };
    TreeNode root{};
    std::stack<StackNode> stack{};
    stack.push({&root, false, preorder, inorder});
    while (!std::empty(stack)) {
        auto [root, isLeft, pre, in] = stack.top();
        stack.pop();
        if(std::empty(pre) || std::empty(in)){
            continue;
        }

        // 前序遍历的第一个元素为根节点
        auto& child = isLeft ? root->left : root->right;
        child = new TreeNode{pre[0]};

        // 在中序遍历中找到根节点
        auto it = std::ranges::find(in, pre[0]);
        assert(it != std::end(in));
        // 在根节点处拆分为左右子树
        std::span<const int> leftInorder{std::begin(in), it};
        std::span<const int> rightInorder{std::next(it), std::end(in)};

        auto rightSize = std::size(rightInorder);
        // 在前序遍历中最右端的 n 个元素为右子树
        std::span<const int> leftPreorder{std::next(std::begin(pre)), std::end(pre) - rightSize};
        if(!std::empty(leftPreorder)){
            stack.push({child, true, leftPreorder, leftInorder});
        }
        // 除了右子树与根节点以外的元素为左子树
        std::span<const int> rightPreorder{std::end(pre) - rightSize, std::end(pre)};
        if(!std::empty(rightPreorder)){
            stack.push({child, false, rightPreorder, rightInorder});
        }
    }
    
    return root.right;
}


int main()
{
    return 0;
}
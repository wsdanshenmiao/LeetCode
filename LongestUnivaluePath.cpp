/*
    687. 最长同值路径
    给定一个二叉树的 root ，返回 最长的路径的长度 ，
    这个路径中的 每个节点具有相同值 。 这条路径可以经过也可以不经过根节点。
    两个节点之间的路径长度 由它们之间的边数表示。

    示例 1:
    输入：root = [5,4,5,1,1,5]
    输出：2
    
    示例 2:
    输入：root = [1,4,5,4,4,5]
    输出：2
    
    提示:
    树的节点数的范围是 [0, 104] 
    -1000 <= Node.val <= 1000
    树的深度将不超过 1000 
*/

#include <utility>

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};


int longestUnivaluePath(TreeNode* root)
{
    // 返回沿着当前节点的最大相同节点， result 为最终的结果
    auto func = [](auto&& self, TreeNode* node, int& result) -> int{
        if(node == nullptr)
            return 0;

        auto left = node->left;
        auto right = node->right;
        auto leftPath = self(self, left, result);
        auto rightPath = self(self, right, result);

        leftPath = left != nullptr && left->val == node->val ? leftPath + 1 : 0;
        rightPath = right != nullptr && right->val == node->val ? rightPath + 1 : 0;

        result = std::max(result, leftPath + rightPath);
        return std::max(leftPath, rightPath);
    };

    int result = 0;
    func(func, root, result);
    return result;
}

int main()
{
    return 0;
}
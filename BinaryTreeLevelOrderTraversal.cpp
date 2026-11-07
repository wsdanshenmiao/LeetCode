/*
    102. 二叉树的层序遍历
    给你二叉树的根节点 root ，返回其节点值的 层序遍历 。 （即逐层地，从左到右访问所有节点）。

    示例 1：
    输入：root = [3,9,20,null,null,15,7]
    输出：[[3],[9,20],[15,7]]
    
    示例 2：
    输入：root = [1]
    输出：[[1]]
    
    示例 3：
    输入：root = []
    输出：[]

    提示：
    树中节点数目在范围 [0, 2000] 内
    -1000 <= Node.val <= 1000
*/

#include <vector>
#include <queue>
#include <print>

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

std::vector<std::vector<int>> levelOrder(TreeNode* root)
{
    std::vector<std::vector<int>> result{};
    std::queue<std::pair<TreeNode*, size_t>> nodeQueue{};
    nodeQueue.emplace(root, 0);
    while(!nodeQueue.empty()){
        auto [node, depth] = nodeQueue.front();
        nodeQueue.pop();
        if(node == nullptr)
            continue;

        if(result.size() <= depth){
            result.resize(depth + 1);
        }
        result[depth].push_back(node->val);
        if(node->left != nullptr)
            nodeQueue.emplace(node->left, depth + 1);
        if(node->right != nullptr)
            nodeQueue.emplace(node->right, depth + 1);
    }

    return result;
}

int main()
{
    TreeNode* root = new TreeNode(3, new TreeNode(9), new TreeNode(20, new TreeNode(15), new TreeNode(7)));
    auto result = levelOrder(root);
    for(const auto& level : result){
        for(const auto& val : level){
            std::print("{} ", val);
        }
        std::println();
    }
    return 0;
}
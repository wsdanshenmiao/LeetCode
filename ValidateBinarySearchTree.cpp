/*
    98. 验证二叉搜索树
    给你一个二叉树的根节点 root ，判断其是否是一个有效的二叉搜索树。
    有效 二叉搜索树定义如下：
    节点的左子树只包含 严格小于 当前节点的数。
    节点的右子树只包含 严格大于 当前节点的数。
    所有左子树和右子树自身必须也是二叉搜索树。

    示例 1：
    输入：root = [2,1,3]
    输出：true
    
    示例 2：
    输入：root = [5,1,4,null,null,3,6]
    输出：false
    解释：根节点的值是 5 ，但是右子节点的值是 4 。

    提示：
    树中节点数目范围在[1, 104] 内
    -231 <= Node.val <= 231 - 1
*/

#include <tuple>
#include <limits>

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

std::tuple<bool, int, int> isValidBSTHelper(TreeNode* root)
{
    if(root->left == nullptr && root->right == nullptr){
        return std::make_tuple(true, root->val, root->val);
    }

    bool isValid = true;
    // max 为左子树的最大值，min 为右子树的最小值
    int max = root->val, min = root->val;
    if(root->left != nullptr){
        auto [isValidLeft, leftMin, leftMax] = isValidBSTHelper(root->left);
        isValid &= isValidLeft && root->val > leftMax;
        min = leftMin;
    }
    if(isValid && root->right != nullptr){
        auto [isValidRight, rightMin, rightMax] = isValidBSTHelper(root->right);
        isValid &= isValidRight && root->val < rightMin;
		max = rightMax;
    }

    // 返回当前子树是否为二叉搜索树，以及当前子树的最小值和最大值
    return std::make_tuple(isValid, min, max);
}

bool isValidBST(TreeNode* root)
{
    return std::get<0>(isValidBSTHelper(root));
}


int main()
{
    TreeNode*root = new TreeNode(45);
    root->left = new TreeNode(42);
    root->right = new TreeNode(44);
    root->right->left = new TreeNode(43);
    root->right->right = new TreeNode(41);
    printf("%d\n", isValidBST(root));
    return 0;
}
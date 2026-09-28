/*
    236. 二叉树的最近公共祖先
    给定一个二叉树, 找到该树中两个指定节点的最近公共祖先。
    百度百科中最近公共祖先的定义为：“对于有根树 T 的两个节点 p、q，最近公共祖先表示为一个节点 x，
    满足 x 是 p、q 的祖先且 x 的深度尽可能大（一个节点也可以是它自己的祖先）。”

    示例 1：
    输入：root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 1
    输出：3
    解释：节点 5 和节点 1 的最近公共祖先是节点 3 。
    
    示例 2：
    输入：root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 4
    输出：5
    解释：节点 5 和节点 4 的最近公共祖先是节点 5 。因为根据定义最近公共祖先节点可以为节点本身。
    
    示例 3：
    输入：root = [1,2], p = 1, q = 2
    输出：1
*/

#include <unordered_map>
#include <stack>

// Definition for a binary tree node.
struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

// TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q)
// {
//     if (root == nullptr || root == p || root == q)
//         return root;
    
//     // 查找左右子树中是否包含 p 或 q
//     auto left = lowestCommonAncestor(root->left, p, q);
//     auto right = lowestCommonAncestor(root->right, p, q);
//     // 若都包含则当前节点为最近公共祖先
//     if (left != nullptr && right != nullptr)
//         return root;
//     // 否则为包含 p 或 q 的子树
//     return left != nullptr ? left : right;
// }

TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q)
{
    struct Frame {
        TreeNode* node;
        TreeNode* left;
        TreeNode* right;
        int state;
    };
    std::stack<Frame> stack{};
    TreeNode* result = nullptr;
    stack.push({root, 0});
    auto setResultToParent = [&stack, &result](TreeNode* node){
        if(!stack.empty()){
            auto& parent = stack.top();
            if (parent.node->left == node){
                parent.left = result;
            }
            else if (parent.node->right == node){
                parent.right = result;
            }
        }
    };
    while(!stack.empty()){
        auto& frame = stack.top();
        switch (frame.state) {
        case 0:{
            if (frame.node == nullptr || frame.node == p || frame.node == q){
                stack.pop();
                result = frame.node;
                setResultToParent(frame.node);
            }
            else{
                frame.state = 1;
            }
            break;
        }
        case 1:{
            frame.state = 2;
            stack.push({frame.node->left, 0});
            break;
        }
        case 2:{
            frame.state = 3;
            stack.push({frame.node->right, 0});
            break;
        }
        case 3:{
            stack.pop();
            result = frame.left != nullptr && frame.right != nullptr ?
                frame.node : (frame.left != nullptr ? frame.left : frame.right);
            setResultToParent(frame.node);
            break;
        }
        default:
            break;
        }
    }
    return result;
}


int main()
{
    // TreeNode* root = new TreeNode(3, new TreeNode(5, new TreeNode(6), new TreeNode(2, new TreeNode(7), new TreeNode(4))), new TreeNode(1, new TreeNode(0), new TreeNode(8)));
    TreeNode* root = new TreeNode(1, new TreeNode(2), new TreeNode(3));
    TreeNode* p = root->left;
    TreeNode* q = root->right;
    auto result = lowestCommonAncestor(root, p, q);
    printf("%d\n", result->val);
    return 0;
}
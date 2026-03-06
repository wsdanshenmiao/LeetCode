/*
    230. 二叉搜索树中第 K 小的元素
    给定一个二叉搜索树的根节点 root ，和一个整数 k ，请你设计一个算法查找其中第 k 小的元素（k 从 1 开始计数）。

    示例 1：
    输入：root = [3,1,4,null,2], k = 1
    输出：1

    示例 2：
    输入：root = [5,3,6,2,4,null,null,1], k = 3
    输出：3
*/

#include <stack>
#include <vector>
#include <algorithm>
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

// int kthSmallest(TreeNode* root, int k)
// {
//     std::stack<TreeNode*> nodeStack{};
//     std::vector<int> sortedArr{};
//     nodeStack.push(root);
//     // 遍历树，将所有节点的值放入数组中
//     while (!std::empty(nodeStack)) {
//         auto node = nodeStack.top();
//         nodeStack.pop();
//         if(node == nullptr)
//             continue;
        
//         sortedArr.push_back(node->val);
//         if(node->right != nullptr){
//             nodeStack.push(node->right);
//         }
//         if(node->left != nullptr){
//             nodeStack.push(node->left);
//         }
//     }
    
//     // 对数组进行排序
//     std::ranges::sort(sortedArr);

//     return std::empty(sortedArr) ? 0 : sortedArr[k - 1];
// }

// int getNodeCount(TreeNode* node)
// {
//     if(node == nullptr)
//         return 0;
    
//     std::stack<TreeNode*> nodeStack{};
//     nodeStack.push(node);
//     int count = 0;
//     while (!std::empty(nodeStack)) {
//         auto node = nodeStack.top();
//         nodeStack.pop();
//         if(node == nullptr)
//             continue;
        
//         count++;
//         if(node->right != nullptr){
//             nodeStack.push(node->right);
//         }
//         if(node->left != nullptr){
//             nodeStack.push(node->left);
//         }
//     }
//     return count;
// }

// int kthSmallest(TreeNode* root, int k)
// {
//     std::stack<TreeNode*> nodeStack{};
//     nodeStack.push(root);
//     while (!std::empty(nodeStack)) {
//         auto node = nodeStack.top();
//         nodeStack.pop();
//         if(node == nullptr)
//             continue;
        
//         // 计算左子树的节点数量
//         int leftNodeCount = getNodeCount(node->left);
//         if(k <= leftNodeCount){
//             // 继续在左子树中寻找
//             nodeStack.push(node->left);
//         }
//         else if(k == leftNodeCount + 1){
//             return node->val;
//         }
//         else{
//             // 继续在右子树中寻找，同时更新 k 的值
//             nodeStack.push(node->right);
//             k -= leftNodeCount + 1;
//         }
//     }

//     return 0;
// }

int kthSmallest(TreeNode* root, int k)
{
    std::stack<TreeNode*> nodeStack{};
    nodeStack.push(root);
    // 进行中序遍历
    for(TreeNode* node = root; node != nullptr || !std::empty(nodeStack);){
        // 先访问左子树
        while (node != nullptr){
            nodeStack.push(node);
            node = node->left;
        }
        node = nodeStack.top();
        nodeStack.pop();
        if(--k == 0){
            return node->val;
        }
        // 再访问右子树
        node = node->right;
    }

    return 0;
}

int main()
{
    TreeNode* root = new TreeNode(5, new TreeNode(3, new TreeNode(2, new TreeNode(1), nullptr), new TreeNode(4)), new TreeNode(6));
    // TreeNode* root = new TreeNode(1, nullptr, new TreeNode(2));
    int k = 1;
    printf("kth smallest: %d\n", kthSmallest(root, k));
    return 0;
}
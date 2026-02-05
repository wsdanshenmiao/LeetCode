/*
    82. 删除排序链表中的重复元素 II
    给定一个已排序的链表的头 head ， 删除原始链表中所有重复数字的节点，只留下不同的数字 。返回 已排序的链表 。

    示例 1：
    输入：head = [1,2,3,3,4,4,5]
    输出：[1,2,5]

    示例 2：
    输入：head = [1,1,1,2,3]
    输出：[2,3]
*/

#include <memory>

struct ListNode 
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

ListNode* deleteDuplicates(ListNode* head) 
{
    if(head == nullptr)
        return head;

    std::unique_ptr<ListNode> newHead = std::make_unique<ListNode>(0, head);
    for(ListNode* prev = newHead.get(), *node = newHead->next; node != nullptr && node->next != nullptr;){
        int nextVal = node->next->val;
        bool isDuplicate = false;
        // 若有重复的节点则持续删除所有重复节点
        while (node != nullptr && node->val == nextVal){
            // 删除当前重复节点并移位
            prev->next = node->next;
            delete node;
            node = prev->next;
            // 标记存在重复节点
            isDuplicate = true;
        }
        if(!isDuplicate){
            // 没有重复节点，继续向后移动
            prev = node;
            node = node->next;
        }
    }

    return newHead->next;
}

int main()
{

    return 0;
}
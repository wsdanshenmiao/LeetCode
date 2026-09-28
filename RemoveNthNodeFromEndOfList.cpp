/*
    19. 删除链表的倒数第 N 个结点
    给你一个链表，删除链表的倒数第 n 个结点，并且返回链表的头结点。

    示例 1：
    输入：head = [1,2,3,4,5], n = 2
    输出：[1,2,3,5]

    示例 2：
    输入：head = [1], n = 1
    输出：[]
    
    示例 3：
    输入：head = [1,2], n = 1
    输出：[1]
*/

#include <cstdio>

// Definition for singly-linked list.
struct ListNode
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};


// ListNode* removeNthFromEnd(ListNode* head, int n)
// {
//     size_t size = 0;
//     for(auto node = head; node != nullptr; node = node->next, ++size);
//     size_t index = size - n;
//     auto node = head, prev = head;
//     while (node != nullptr && index > 0) {
//         prev = node;
//         node = node->next;
//         --index;
//     }
//     if(node == nullptr){
//         return head;
//     }

//     if(node == head){
//         head = head->next;
//         delete node;
//     }
//     else{
//         prev->next = node->next;
//         delete node;
//     }
//     return head;
// }

ListNode* removeNthFromEnd(ListNode* head, int n)
{
    ListNode dummy{0, head};
    auto slow = &dummy, fast = &dummy;
    // 快慢指针之间相隔 n 个节点
    while(n-- >= 0 && fast != nullptr){
        fast = fast->next;
    }
    // fast 指针到达链表末尾时，slow 指针正好指向倒数第 n + 1 个节点
    while(fast != nullptr){
        slow = slow->next;
        fast = fast->next;
    }
    // 删除 slow 指针指向的节点
    auto node = slow->next;
    if(node != nullptr){
        slow->next = node->next;
        delete node;
    }
    return dummy.next;
}

int main()
{
    ListNode* head = new ListNode(1, new ListNode(2));
    int n = 2;
    head = removeNthFromEnd(head, n);
    for(auto node = head; node != nullptr; node = node->next){
        printf("%d ", node->val);
    }
    return 0;
}
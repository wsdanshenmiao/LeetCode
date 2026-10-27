/*
    92. 反转链表 II
    给你单链表的头指针 head 和两个整数 left 和 right ，其中 left <= right 。请你反转从位置 left 到位置 right 的链表节点，返回 反转后的链表 。

    示例 1：
    输入：head = [1,2,3,4,5], left = 2, right = 4
    输出：[1,4,3,2,5]
    
    示例 2：
    输入：head = [5], left = 1, right = 1
    输出：[5]
    
    提示：
    链表中节点数目为 n
    1 <= n <= 500
    -500 <= Node.val <= 500
    1 <= left <= right <= n
    
    进阶： 你可以使用一趟扫描完成反转吗？
*/

#include <print>
#include <string>

// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

template<>
struct std::formatter<ListNode> : public std::formatter<std::string>
{
    auto format(const ListNode& node, auto& ctx) const
    {
        std::string result;
        const ListNode* current = &node;
        while (current != nullptr)
        {
            result += std::to_string(current->val);
            if (current->next != nullptr)
                result += " -> ";
            current = current->next;
        }
        return std::formatter<std::string>::format(result, ctx);
    }
};

ListNode* reverseBetween(ListNode* head, int left, int right)
{
    if(head == nullptr || left >= right)
        return head;

    ListNode dummy{};
    dummy.next = head;
    ListNode* prev = &dummy;
    for(int i = 1; i < left; ++i){
        prev = prev->next;
    }

    // 插入到 prev 节点之后
    ListNode* curr = prev->next;
    for(int i = left; i < right; ++i){
        ListNode* next = curr->next;
        curr->next = next->next;
        next->next = prev->next;
        prev->next = next;
    }

    return dummy.next;
}


int main()
{
    int left = 1;
    int right = 2;
    ListNode* head = new ListNode(1);
    ListNode* curr = head;
    for(int i = 2; i <= right; ++i){
        curr->next = new ListNode(i);
        curr = curr->next;
    }

    head = reverseBetween(head, left, right);
    std::println("{}", *head);
    return 0;
}
/*
    86. 分隔链表
    给你一个链表的头节点 head 和一个特定值 x ，请你对链表进行分隔，
    使得所有 小于 x 的节点都出现在 大于或等于 x 的节点之前。
    你应当 保留 两个分区中每个节点的初始相对位置。

    示例 1：
    输入：head = [1,4,3,2,5,2], x = 3
    输出：[1,2,2,4,3,5]

    示例 2：
    输入：head = [2,1], x = 2
    输出：[1,2]
*/


#include <vector>
#include <ranges>


struct ListNode
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};


ListNode* partition(ListNode* head, int x) 
{
    if(head == nullptr)
        return head;

    ListNode root{0, head}, tmpRoot{0, nullptr};
    ListNode* lastElement = &tmpRoot;
    auto push = [&lastElement](ListNode* node){
        node->next = lastElement->next;
        lastElement->next = node;
        lastElement = node;
    };
    for(ListNode* node = root.next, *prev = &root; node != nullptr; prev = node, node = node->next){
        if(node->val < x){
            prev->next = node->next;
            push(node);
            node = prev;
        }
    }
    lastElement->next = root.next;

    return tmpRoot.next == nullptr ? root.next : tmpRoot.next;
}

int main()
{
    std::vector<int> vals{1,4,3,2,5,2};
    ListNode* head = new ListNode(vals[0]);
    ListNode* node = head;
    for(const int& val : vals | std::views::drop(1)){
        node->next = new ListNode(val);
        node = node->next;
    }

    head = partition(head, 3);

    for(node = head; node != nullptr; node = node->next){
        printf("%d ", node->val);
    }

    return 0;
}
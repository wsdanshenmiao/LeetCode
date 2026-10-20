/*
    148. 排序链表
    给你链表的头结点 head ，请将其按 升序 排列并返回 排序后的链表 。

    示例 1：
    输入：head = [4,2,1,3]
    输出：[1,2,3,4]
    
    示例 2：
    输入：head = [-1,5,3,4,0]
    输出：[-1,0,3,4,5]
    
    示例 3：
    输入：head = []
    输出：[]

    提示：
    链表中节点的数目在范围 [0, 5 * 104] 内
    -105 <= Node.val <= 105
    
    进阶：你可以在 O(n log n) 时间复杂度和常数级空间复杂度下，对链表进行排序吗？
*/

#include <print>
#include <string>

// Definition for singly-linked list.
struct ListNode
{
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

enum class SortType
{
    MergeSort,
    QuickSort
};

ListNode* quickSort(ListNode* head)
{
    struct List
    {
        ListNode* head{};
        ListNode* tail{};
        std::size_t size{};
    };

    auto sortHelper = [](this auto&& self, List list){
        if(list.head == nullptr || list.head->next == nullptr)
            return list;
        
        // 将节点进行尾插
        auto insertList = [](List& src, const List& list, bool isAppend = true) {
            if(list.head == nullptr || list.tail == nullptr)
                return;
            if(src.head == nullptr){
                src.head = list.head;
                src.tail = list.tail;
                src.size = list.size;
            }
            else{
                src.tail->next = list.head;
                src.tail = list.tail;
                src.size += list.size;
            }
            if(isAppend){
                list.head->next = nullptr;
                list.tail->next = nullptr;
            }
        };

        List less{}, equal{}, greater{};

        ListNode* curr = list.head;
        int pivot = list.head->val;
        while(curr != nullptr){
            ListNode* next = curr->next;
            if(curr->val < pivot){
                // 插入小序列链表中
                insertList(less, {curr, curr, 1});
            }
            else if(curr->val == pivot){
                // 插入相等序列链表中
                insertList(equal, {curr, curr, 1});
            }
            else{
                // 插入大序列链表中
                insertList(greater, {curr, curr, 1});
            }
            curr = next;
        }

        // 递归排序小序列和大序列
        less = self(less);
        greater = self(greater);

        // 合并小序列、相等序列和大序列
        insertList(list, less, false);
        insertList(list, equal, false);
        insertList(list, greater, false);

        return list;
    };

    List list{head, nullptr, 0};
    while(head != nullptr){
        list.tail = head;
        list.size++;
        head = head->next;
    }

    return sortHelper(list).head;
}

ListNode* mergeSort(ListNode* head)
{
    return head;
}

template <SortType sortType>
ListNode* sortList(ListNode* head)
{
    if (head == nullptr || head->next == nullptr)
        return head;

    if constexpr (sortType == SortType::QuickSort){
        return quickSort(head);
    }
    else if constexpr (sortType == SortType::MergeSort){
        return mergeSort(head);
    }
};

int main()
{
    ListNode* head = new ListNode(4);
    head->next = new ListNode(2);
    head->next->next = new ListNode(1);
    head->next->next->next = new ListNode(3);

    head = sortList<SortType::QuickSort>(head);

    std::println("Sorted list: {}", *head);

    return 0;
}
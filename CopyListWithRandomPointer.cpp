/*
    138. 随机链表的复制
    给你一个长度为 n 的链表，每个节点包含一个额外增加的随机指针 random ，该指针可以指向链表中的任何节点或空节点。
    构造这个链表的 深拷贝。 深拷贝应该正好由 n 个 全新 节点组成，其中每个新节点的值都设为其对应的原节点的值。
    新节点的 next 指针和 random 指针也都应指向复制链表中的新节点，并使原链表和复制链表中的这些指针
    能够表示相同的链表状态。复制链表中的指针都不应指向原链表中的节点 。
    例如，如果原链表中有 X 和 Y 两个节点，其中 X.random --> Y 。
    那么在复制链表中对应的两个节点 x 和 y ，同样有 x.random --> y 。
    返回复制链表的头节点。
    用一个由 n 个节点组成的链表来表示输入/输出中的链表。每个节点用一个 [val, random_index] 表示：
    val：一个表示 Node.val 的整数。
    random_index：随机指针指向的节点索引（范围从 0 到 n-1）；如果不指向任何节点，则为  null 。
    你的代码 只 接受原链表的头节点 head 作为传入参数。

    示例 1：
    输入：head = [[7,null],[13,0],[11,4],[10,2],[1,0]]
    输出：[[7,null],[13,0],[11,4],[10,2],[1,0]]
    
    示例 2：
    输入：head = [[1,1],[2,1]]
    输出：[[1,1],[2,1]]
    
    示例 3：
    输入：head = [[3,null],[3,0],[3,null]]
    输出：[[3,null],[3,0],[3,null]]
*/

#include <unordered_map>

// Definition for a Node.
struct Node
{
    int val;
    Node* next;
    Node* random;
    
    Node(int _val)
        : val(_val), next(nullptr), random(nullptr) {}
};

// Node* copyRandomList(Node* head)
// {
//     std::unordered_map<Node*, Node*> nodeMap;
//     Node copyList{0};
//     for(Node* node = head, *copyNode = &copyList; node != nullptr; 
//         node = node->next, copyNode = copyNode->next){
//         copyNode->next = new Node(node->val);
//         // 记录原节点与复制节点的映射关系
//         nodeMap[node] = copyNode->next;
//     }

//     for(auto node = copyList.next, origin = head; node != nullptr; 
//         node = node->next, origin = origin->next){
//         if(origin->random != nullptr){
//             // 在映射表中找到原节点的随机指针所指向的节点对应的复制节点
//             node->random = nodeMap[origin->random];
//         }
//     }

//     return copyList.next;
// }


// Node* copyRandomList(Node* head)
// {
//     Node copyList{0};
//     std::unordered_map<Node*, Node*> nodeMap;
//     for(Node* node = head, *copy = &copyList; node != nullptr; 
//         node = node->next, copy = copy->next){
//         if(auto it = nodeMap.find(node); it != nodeMap.end()){
//             // 若先前已创建了复制节点，则直接使用复制节点
//             copy->next = it->second;
//         }
//         else{
//             // 否则创建一个节点并记录映射关系
//             copy->next = new Node(node->val);
//             nodeMap[node] = copy->next;
//         }

//         if(auto it = nodeMap.find(node->random); it != std::end(nodeMap)){
//             // 若复制链表中已存在原节点的随机节点，则直接指向对应节点
//             copy->next->random = it->second;
//         }
//         else if(node->random != nullptr) {
//             // 否则创建一个节点并记录映射关系
//             copy->next->random = new Node(node->random->val);
//             nodeMap[node->random] = copy->next->random;
//         }
//     }

//     return copyList.next;
// }

Node* copyRandomList(Node* head)
{
    if(head == nullptr){
        return head;
    }

    // 在原节点的中间插入复制节点
    for(auto node = head; node != nullptr; node = node->next->next){
        auto newNode = new Node(node->val);
        newNode->next = node->next;
        node->next = newNode;
    }
    for(auto node = head; node != nullptr; node = node->next->next){
        // 更新复制节点的随机指针
        node->next->random = node->random == nullptr ? nullptr : node->random->next;
    }
    // 分离两个链表
    Node* newHead = head->next;
    for(auto node = head; node != nullptr; node = node->next){
        auto newNode = node->next;
        node->next = newNode->next;
        newNode->next = newNode->next == nullptr ? nullptr : newNode->next->next;
    }

    return newHead;
}

int main()
{
    
    return 0;
}
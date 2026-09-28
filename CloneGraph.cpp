/*
    133. 克隆图
    给你无向连通图中一个节点的引用，请你返回该图的深拷贝（克隆）。
    图中的每个节点都包含它的值 val（int） 和其邻居的列表（list[Node]）。

    class Node {
        public int val;
        public List<Node> neighbors;
    }

    测试用例格式：
    简单起见，每个节点的值都和它的索引相同。例如，第一个节点值为 1（val = 1），第二个节点值为 2（val = 2），以此类推。
    该图在测试用例中使用邻接列表表示。
    邻接列表是用于表示有限图的无序列表的集合。每个列表都描述了图中节点的邻居集。
    给定节点将始终是图中的第一个节点（值为 1）。你必须将 给定节点的拷贝 作为对克隆图的引用返回。

    示例 1：
    输入：adjList = [[2,4],[1,3],[2,4],[1,3]]
    输出：[[2,4],[1,3],[2,4],[1,3]]
    解释：
    图中有 4 个节点。
    节点 1 的值是 1，它有两个邻居：节点 2 和 4 。
    节点 2 的值是 2，它有两个邻居：节点 1 和 3 。
    节点 3 的值是 3，它有两个邻居：节点 2 和 4 。
    节点 4 的值是 4，它有两个邻居：节点 1 和 3 。
    
    示例 2：
    输入：adjList = [[]]
    输出：[[]]
    解释：输入包含一个空列表。该图仅仅只有一个值为 1 的节点，它没有任何邻居。
    
    示例 3：
    输入：adjList = []
    输出：[]
    解释：这个图是空的，它不含任何节点。
    
    提示：
    这张图中的节点数在 [0, 100] 之间。
    1 <= Node.val <= 100
    每个节点值 Node.val 都是唯一的，
    图中没有重复的边，也没有自环。
    图是连通图，你可以从给定节点访问到所有节点。
*/

#include <vector>
#include <print>
#include <unordered_map>
#include <unordered_set>

// Definition for a Node.
class Node
{
public:
    int val{};
    std::vector<Node*> neighbors{};
    
    Node(int _val)
    {
        val = _val;
    }
    
    Node(int _val, std::vector<Node*> _neighbors)
    {
        val = _val;
        neighbors = _neighbors;
    }
};

Node* cloneGraph(Node* node)
{
    if(node == nullptr)
        return nullptr;

    std::unordered_map<Node*, Node*> clonedNodes{};
    auto cloneGraphHelper = [&clonedNodes](this auto&& self, Node* node) -> Node* {
        if(node == nullptr){
            return nullptr;
        }
        if(clonedNodes.count(node)){
            return clonedNodes[node];
        }

        auto newNode = new Node(node->val);
        clonedNodes[node] = newNode;
        newNode->neighbors.reserve(node->neighbors.size());
        for(const auto& neighbor : node->neighbors){
            if(neighbor == nullptr)
                continue;

            auto clonedNeighbor = clonedNodes.count(neighbor) ? 
                clonedNodes[neighbor] : self(neighbor);
            newNode->neighbors.push_back(clonedNeighbor);
        }

        return newNode;
    };

    return cloneGraphHelper(node);
}

int main()
{
    // Example usage:
    Node* node1 = new Node(1);
    Node* node2 = new Node(2);
    Node* node3 = new Node(3);
    Node* node4 = new Node(4);

    node1->neighbors.push_back(node2);
    node1->neighbors.push_back(node4);
    node2->neighbors.push_back(node1);
    node2->neighbors.push_back(node3);
    node3->neighbors.push_back(node2);
    node3->neighbors.push_back(node4);
    node4->neighbors.push_back(node1);
    node4->neighbors.push_back(node3);

    Node* clonedGraph = cloneGraph(node1);

    auto printGraph = [](this auto&& self, const Node* node, std::unordered_set<const Node*>& visited) {
        if (node == nullptr || visited.count(node)) {
            return;
        }
        visited.insert(node);
        std::print("Node {} neighbors: ", node->val);
        for (const auto& neighbor : node->neighbors) {
            std::print("{} ", neighbor->val);
        }
        std::println();
        for (const auto& neighbor : node->neighbors) {
            self(neighbor, visited);
        }
    };

    std::unordered_set<const Node*> visited{};
    printGraph(node1, visited);
    visited.clear();
    std::println("Cloned graph:");
    printGraph(clonedGraph, visited);

    return 0;
}
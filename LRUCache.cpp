/*
    146. LRU 缓存
    请你设计并实现一个满足  LRU (最近最少使用) 缓存 约束的数据结构。
    实现 LRUCache 类：
        LRUCache(int capacity) 以 正整数 作为容量 capacity 初始化 LRU 缓存
        int get(int key) 如果关键字 key 存在于缓存中，则返回关键字的值，否则返回 -1 。
        void put(int key, int value) 如果关键字 key 已经存在，则变更其数据值 value ；如果不存在，
        则向缓存中插入该组 key-value 。如果插入操作导致关键字数量超过 capacity ，则应该 逐出 最久未使用的关键字。
        函数 get 和 put 必须以 O(1) 的平均时间复杂度运行。

    

    示例：
    输入
    ["LRUCache", "put", "put", "get", "put", "get", "put", "get", "get", "get"]
    [[2], [1, 1], [2, 2], [1], [3, 3], [2], [4, 4], [1], [3], [4]]
    输出
    [null, null, null, 1, null, -1, null, -1, 3, 4]

    解释
    LRUCache lRUCache = new LRUCache(2);
    lRUCache.put(1, 1); // 缓存是 {1=1}
    lRUCache.put(2, 2); // 缓存是 {1=1, 2=2}
    lRUCache.get(1);    // 返回 1
    lRUCache.put(3, 3); // 该操作会使得关键字 2 作废，缓存是 {1=1, 3=3}
    lRUCache.get(2);    // 返回 -1 (未找到)
    lRUCache.put(4, 4); // 该操作会使得关键字 1 作废，缓存是 {4=4, 3=3}
    lRUCache.get(1);    // 返回 -1 (未找到)
    lRUCache.get(3);    // 返回 3
    lRUCache.get(4);    // 返回 4
*/

#include <memory>
#include <unordered_map>
#include <queue>

class LRUCache 
{
public:
    LRUCache(int capacity) 
        : m_Capacity(capacity) {}
    
    int get(int key) 
    {
        if(m_Cache.find(key) == std::end(m_Cache)){
            return -1;
        }
        // 将访问的节点移动到链表头部
        m_List.splice(m_List.begin(), m_List, m_Cache[key]);
        return m_List.front().second;
    }
    
    void put(int key, int value) 
    {
        if(m_Cache.find(key) != std::end(m_Cache)){
            // 移动到链表头部，由于迭代器不会失效所以无需更新迭代器
            m_List.splice(m_List.begin(), m_List, m_Cache[key]);
            m_List.front().second = value;
        }
        else{
            if(std::size(m_Cache) >= m_Capacity){
                // 删除最末端的节点
                m_Cache.erase(m_List.back().first);
                m_List.pop_back();
            }
            // 从头部插入新节点
            m_List.emplace_front(key, value);
            m_Cache.insert({key, m_List.begin()});
        }
    }

private:
    const int m_Capacity = 0;
    std::unordered_map<int, std::list<std::pair<int, int>>::iterator> m_Cache;
    std::list<std::pair<int, int>> m_List;
};


int main()
{
    auto lRUCache = std::make_unique<LRUCache>(2);
    lRUCache->put(1, 0);
    lRUCache->put(2, 2);
    int val = lRUCache->get(1); // returns 0
    printf("%d\n", val);
    lRUCache->put(3, 3); // evicts key 2
    val = lRUCache->get(2); // returns -1 (not found)
    printf("%d\n", val);
    lRUCache->put(4, 4); // evicts key 1
    val = lRUCache->get(1); // returns -1 (not found)
    printf("%d\n", val);
    val = lRUCache->get(3); // returns 3
    printf("%d\n", val);
    val = lRUCache->get(4); // returns 4
    printf("%d\n", val);

    return 0;
}
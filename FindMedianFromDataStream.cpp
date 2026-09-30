/*
    295. 数据流的中位数
    中位数是有序整数列表中的中间值。如果列表的大小是偶数，则没有中间值，中位数是两个中间值的平均值。
    例如 arr = [2,3,4] 的中位数是 3 。
    例如 arr = [2,3] 的中位数是 (2 + 3) / 2 = 2.5 。

    实现 MedianFinder 类:
    MedianFinder() 初始化 MedianFinder 对象。
    void addNum(int num) 将数据流中的整数 num 添加到数据结构中。
    double findMedian() 返回到目前为止所有元素的中位数。与实际答案相差 10-5 以内的答案将被接受。

    示例 1：
    输入
    ["MedianFinder", "addNum", "addNum", "findMedian", "addNum", "findMedian"]
    [[], [1], [2], [], [3], []]
    输出
    [null, null, null, 1.5, null, 2.0]

    解释
    MedianFinder medianFinder = new MedianFinder();
    medianFinder.addNum(1);    // arr = [1]
    medianFinder.addNum(2);    // arr = [1, 2]
    medianFinder.findMedian(); // 返回 1.5 ((1 + 2) / 2)
    medianFinder.addNum(3);    // arr[1, 2, 3]
    medianFinder.findMedian(); // return 2.0
    
    提示:
    -105 <= num <= 105
    在调用 findMedian 之前，数据结构中至少有一个元素
    最多 5 * 104 次调用 addNum 和 findMedian
*/

#include <vector>
#include <algorithm>
#include <print>
#include <queue>

class MedianFinder {
public:
    MedianFinder() {
        
    }
    
    void addNum(int num) {
        if(m_MaxHeap.size() > m_MinHeap.size()) {
            m_MinHeap.push(num);
        }
        else{
            m_MaxHeap.push(num);
        }
        while(!m_MaxHeap.empty() && !m_MinHeap.empty() && 
            m_MaxHeap.top() > m_MinHeap.top()) {
            int maxTop = m_MaxHeap.top();
            int minTop = m_MinHeap.top();
            m_MaxHeap.pop();
            m_MinHeap.pop();
            m_MaxHeap.push(minTop);
            m_MinHeap.push(maxTop);
        }
    }
    
    double findMedian() {
        if(m_MaxHeap.empty()) {
            return 0.0;
        }
        return m_MaxHeap.size() > m_MinHeap.size() ? m_MaxHeap.top() : (m_MaxHeap.top() + m_MinHeap.top()) / 2.0;
    }

private:
    std::priority_queue<int> m_MaxHeap{};
    std::priority_queue<int, std::vector<int>, std::greater<int>> m_MinHeap{};
};

int main()
{
    MedianFinder medianFinder;
    medianFinder.addNum(1);    // arr = [1]
    medianFinder.addNum(2);    // arr = [1, 2]
    double median1 = medianFinder.findMedian(); // 返回 1.5 ((1 + 2) / 2)
    std::println("Median 1: {}", median1);
    medianFinder.addNum(3);    // arr[1, 2, 3]
    double median2 = medianFinder.findMedian(); // return 2.0
    std::println("Median 2: {}", median2);

    return 0;
}
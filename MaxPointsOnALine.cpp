/*
    149. 直线上最多的点数
    给你一个数组 points ，其中 points[i] = [xi, yi] 表示 X-Y 平面上的一个点。求最多有多少个点在同一条直线上。

    示例 1：
    输入：points = [[1,1],[2,2],[3,3]]
    输出：3

    示例 2：
    输入：points = [[1,1],[3,2],[5,3],[4,1],[2,3],[1,4]]
    输出：4

    提示：
    1 <= points.length <= 300
    points[i].length == 2
    -104 <= xi, yi <= 104
    points 中的所有点 互不相同
*/

#include <vector>
#include <unordered_map>
#include <ranges>
#include <print>
#include <unordered_set>
#include <numeric>

struct Line
{
    int dx;
    int dy;

    bool operator==(const Line& other) const = default;
};

template<>
struct std::hash<Line>
{
    std::size_t operator()(const Line& line) const
    {
        auto a = std::hash<int>{}(line.dx);
        auto b = std::hash<int>{}(line.dy);
        return a * 131 + b;
    }
};


int maxPoints(std::vector<std::vector<int>>& points)
{
    if(points.size() <= 2){
        return points.size();
    }

    std::size_t max = 0;
    std::unordered_map<Line, std::size_t> mapping{};
    for(const auto& [i, point0] : points | std::views::enumerate){
        mapping.clear();
        for(std::size_t j = i + 1; j < std::size(points); ++j){
            auto point1 = points[j];

            Line line{ point1[0] - point0[0], point1[1] - point0[1] };
            auto g = std::gcd(line.dx, line.dy);
            line.dx /= g;
            line.dy /= g;
            if(line.dx < 0 || (line.dx == 0 && line.dy < 0)){
                line.dx = -line.dx;
                line.dy = -line.dy;
            }
            mapping[line]++;
        }

        if(!mapping.empty()){
            auto count = *std::ranges::max_element(mapping | std::views::values);
            max = std::max(max, count + 1);
        }
    }

    return max;
}

int main()
{
    std::vector<std::vector<int>> points{{1, 1}, {2, 2}, {3, 3}};
    std::println("{}", maxPoints(points));
    std::vector<std::vector<int>> points1{{1,1},{3,2},{5,3},{4,1},{2,3},{1,4}};
    std::println("{}", maxPoints(points1));
    std::vector<std::vector<int>> points2{{2,1},{2,2},{2,3},{3,1},{3,2},{3,3},{3,4}};
    std::println("{}", maxPoints(points2));
    return 0;
}
/*
    50. Pow(x, n)
    实现 pow(x, n) ，即计算 x 的整数 n 次幂函数（即，xn ）。

    示例 1：
    输入：x = 2.00000, n = 10
    输出：1024.00000
    
    示例 2：
    输入：x = 2.10000, n = 3
    输出：9.26100
    
    示例 3：
    输入：x = 2.00000, n = -2
    输出：0.25000
    解释：2-2 = 1/22 = 1/4 = 0.25
    

    提示：
    -100.0 < x < 100.0
    -231 <= n <= 231-1
    n 是一个整数
    要么 x 不为零，要么 n > 0 。
    -104 <= xn <= 104
*/

#include <cmath>
#include <print>
#include <string>

template <std::size_t Version = 0>
double MyPow(double x, int n);

template<>
double MyPow<0>(double x, int n)
{
    return std::pow(x, n);
}

template<>
double MyPow<1>(double x, int n)
{
    if(x == 1 || n == 0)
        return 1;
    ptrdiff_t exponent = n;
    if(exponent < 0){
        x = 1 / x;
        exponent = -exponent;
    }
    double result = x;
    for(int i = 1; i < exponent; ++i){
        result *= x;
    }
    return result;
}

template<>
double MyPow<2>(double x, int n)
{
    return x;
}

int main(int argc, char** argv)
{
    double x = 2.0;
    int n = 0;
    if(argc > 2){
        x = std::stod(argv[1]);
        n = std::stoi(argv[2]);
    }
    std::println("Input: x = {}, n = {}", x, n);
    double result = MyPow<1>(x, n);
    std::println("Result: {}", result);

    return 0;
}
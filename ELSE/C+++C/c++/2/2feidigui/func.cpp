<<<<<<< HEAD
/*
 * @FILE: func.cpp
 * @Description: 实现func.h中的fn和Cnr函数
 */
#include "func.h"
=======
#include "func.h"

>>>>>>> 4b973315162d27f01fa06261e78d6fb1c889420e
// 计算 n!
double fn(int n)
{
    double result = 1;
<<<<<<< HEAD
    for(int i = 2; i <= n; i++)// 从2开始，计算到n
=======
    for(int i = 2; i <= n; i++)
>>>>>>> 4b973315162d27f01fa06261e78d6fb1c889420e
    {
        result *= i;
    }
    return result;
}
<<<<<<< HEAD
=======

>>>>>>> 4b973315162d27f01fa06261e78d6fb1c889420e
// 计算从 n 个数中取 r 个数的组合数
double Cnr(int n, int r)
{
    double result = 1;
<<<<<<< HEAD
    for(int i = 1; i <= r; i++)// 从1开始，计算到r
=======
    for(int i = 1; i <= r; i++)
>>>>>>> 4b973315162d27f01fa06261e78d6fb1c889420e
    {
        result *= (n - r + i) / static_cast<double>(i);
    }
    return result;
}

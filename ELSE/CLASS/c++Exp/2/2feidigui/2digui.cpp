/*
 * @FILE: 2digui.cpp
 * @Description: 编写一个函数，求从 n 个不同的数中取r 个数的所有选择的个数。
 */
// g++ -o 2digui 2digui.cpp func.cpp
#include <iostream>
#include "func.h"
using namespace std;
int main()
{
    
    int n, r;
    while (true)
    {
        cout << "Input n and r:";
        cin >> n >> r;
        if (n == 0 && r == 0) // 输入0 0结束程序
        {
            break;
        }
        if (n < r || n < 1 || r < 1) // 输入错误提示
        {
            cout << "Input error" << endl;
            continue;
        }
        double result = Cnr(n, r); // 调用func.cpp中的Cnr函数
        cout << n << " " << r << " " << result << endl;
    }
    system("pause");
    return 0;
}

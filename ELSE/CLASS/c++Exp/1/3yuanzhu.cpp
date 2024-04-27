// include头文件，引入iostream标准输入输出流库
#include <iostream>
// 告诉编译器使用命名空间std，避免代码中多次使用std::
using namespace std;
// 定义一个常量PI，其值为3.14159
#define PI 3.14159
int main()
{
    // 定义两个double类型变量，分别表示半径和高
    double radius, high;
    // 定义一个double类型变量，表示体积
    double volume;
    // 输出提示信息，要求用户输入两个数字
    cout << "Please input two numbers:" << endl;
    // 从标准输入流中读取两个数字，分别赋值给半径和高
    cin >> radius >> high;
    // 判断半径和高是否小于0，如果是，则输出错误信息并退出程序
    if (radius < 0 || high < 0)
    {
        cout << "The radius or high is negative!" << endl;
        return 0;
    }
    // 计算体积，公式为 PI * radius * radius * high
    volume = PI * radius * radius * high;
    // 输出半径和高
    cout << "radius:" << radius << " high:" << high << endl;
    // 输出体积
    cout << "The volume is:" << volume << endl;
    // 程序正常结束，返回0
    return 0;
}
#include <iostream>
using namespace std;
void swap(int *p1, int *p2);
int main()
{
    cout << "------------------------------------" << endl;
    int iv1 = 888;
    int *pointer_1;                               // 定义一个指针变量
    pointer_1 = &iv1;                             // 将iv1的地址赋值给指针变量
    cout << "iv1      = " << iv1 << endl;         // 输出iv1的值
    cout << "*pointer_1= " << *pointer_1 << endl; // 输出指针变量所指向的值
    cout << "&iv1     = " << &iv1 << endl;        // 输出iv1的地址
    cout << "pointer_1= " << pointer_1 << endl;   // 输出指针变量的值

    cout << "------------------------------------" << endl;
    int iv2 = 666;
    int *pointer_2;                               // 定义一个指针变量
    pointer_2 = &iv2;                             // 将iv2的地址赋值给指针变量
    cout << "iv2      = " << iv2 << endl;         // 输出iv2的值
    cout << "*pointer_2= " << *pointer_2 << endl; // 输出指针变量所指向的值
    cout << "&iv2     = " << &iv2 << endl;        // 输出iv2的地址
    cout << "pointer_2= " << pointer_2 << endl;   // 输出指针变量的值

    cout << "------------------------------------" << endl;
    swap(pointer_1, pointer_2);                   // 交换两个指针变量所指向的值
    cout << "iv1      = " << iv1 << endl;         // 输出iv1的值
    cout << "iv2      = " << iv2 << endl;         // 输出iv2的值
    cout << "*pointer_1= " << *pointer_1 << endl; // 输出指针变量所指向的值
    cout << "*pointer_2= " << *pointer_2 << endl; // 输出指针变量所指向的值
    cout << "pointer_1= " << pointer_1 << endl;   // 输出指针变量的值
    cout << "pointer_2= " << pointer_2 << endl;   // 输出指针变量的值
    return 0;
}
void swap(int *p1, int *p2) // 交换两个指针变量所指向的值
{
    int temp;
    temp = *p1;
    *p1 = *p2;
    *p2 = temp;
}
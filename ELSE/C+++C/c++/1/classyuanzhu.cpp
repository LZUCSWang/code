// 头文件
#include <iostream>
using namespace std;
// 定义一个容器类
class container
{
protected:
    double radius; // 半径
public:
    container(double radius) // 构造函数
    {
        container::radius = radius; // 初始化半径
    }
    virtual double surface_area() = 0; // 求表面积的纯虚函数
    virtual double volume() = 0;       // 求体积的纯虚函数
};

// 定义一个正方体类
class cube : public container
{
public:
    cube(double radius) : container(radius){}; // 构造函数
    double surface_area()                      // 求表面积的函数
    {
        return radius * radius * 6; // 正方体表面积公式
    }
    double volume() // 求体积的函数
    {
        return radius * radius * radius; // 正方体体积公式
    }
};

// 定义一个球体类
class sphere : public container
{
public:
    sphere(double radius) : container(radius){}; // 构造函数
    double surface_area()                        // 求表面积的函数
    {
        return 4 * 3.1416 * radius * radius; // 球体表面积公式
    }
    double volume() // 求体积的函数
    {
        return 3.1416 * radius * radius * radius * 4 / 3; // 球体体积公式
    }
};

// 定义一个圆柱体类
class cylinder : public container
{
    double height; // 高度
public:
    cylinder(double radius, double height) : container(radius) // 构造函数
    {
        cylinder::height = height; // 初始化高度
    }
    double surface_area() // 求表面积的函数
    {
        return 2 * 3.1416 * radius * (height + radius); // 圆柱体表面积公式
    }
    double volume() // 求体积的函数
    {
        return 3.1416 * radius * radius * height; // 圆柱体体积公式
    }
};

int main()
{
    container *p;        // 定义一个容器类指针
    cube obj1(10);       // 创建一个正方体对象
    sphere obj2(6);      // 创建一个球体对象
    cylinder obj3(4, 5); // 创建一个圆柱体对象
    p = &obj1;           // 将指针指向正方体对象
    cout << "输出结果：" << endl;
    cout << "正方体表面积：" << p->surface_area() << endl; // 输出正方体表面积
    cout << "正方体体积：" << p->volume() << endl;         // 输出正方体体积
    p = &obj2;                                             // 将指针指向球体对象
    cout << "球体表面积：" << p->surface_area() << endl;   // 输出球体表面积
    cout << "球体体积：" << p->volume() << endl;           // 输出球体体积
    p = &obj1;                                             // 将指针指向正方体对象
    p = &obj3;                                             // 将指针指向圆柱体对象
    cout << "圆柱体表面积：" << p->surface_area() << endl; // 输出圆柱体表面积
    cout << "圆柱体体积：" << p->volume() << endl;
}
/*
 * @Author: 王贤义
 * @FilePath: \code\C+++C\c++\6\1picPlus.cpp
 * @Description: 设计一个图形基类：Shape，在此基础上派生Rectangle、Circle、Triangle 类。
1、Cirlce 类基本信息：圆心坐标、半径；
Rectangle 类基本信息：长、宽；
Triangle 类基本信息：三个顶点坐标；
其中：成员变量为 private 属性，成员函数为public 属性；
2、每个图形类有多个构造函数：缺省构造函数、带参数的构造函数；
3、每个图形类有计算图形的面积GetArea()，显示图形的基本信息函数Show()，修改基
本信息的函数Set(形参)。

 */

#include <iostream>
#include <cmath>
using namespace std;

#define M_PI 3.14159265358979323846 // 定义圆周率常量

class Shape // 形状基类
{
protected:
    double area; // 面积

public:
    Shape() {}                             // 默认构造函数
    virtual double GetArea() { return 0; } // 虚函数，计算面积
    virtual void Show() {}                 // 虚函数，显示形状信息
};

class Circle : public Shape // 圆形派生类，继承自Shape
{
private:
    double x, y, r; // 圆心坐标和半径

public:
    Circle() : x(0), y(0), r(0) {}                                   // 默认构造函数
    Circle(double x_, double y_, double r_) : x(x_), y(y_), r(r_) {} // 带参数的构造函数
    double GetArea() override { return M_PI * r * r; }               // 计算圆形的面积
    void Show() override                                             // 显示圆形的信息
    {
        cout << "Shape: Circle\n";
        cout << "Center: (" << x << ", " << y << ")\n";
        cout << "Radius: " << r << "\n";
        cout << "Diameter: " << r * 2 << "\n";
        cout << "Circumference: " << 2 * M_PI * r << "\n";
        cout << "Area: " << GetArea() << "\n";
    }
};

class Rectangle : public Shape // 矩形派生类，继承自Shape
{
private:
    double length, width; // 长度和宽度

public:
    Rectangle() : length(0), width(0) {}                                         // 默认构造函数
    Rectangle(double length_, double width_) : length(length_), width(width_) {} // 带参数的构造函数
    double GetArea() override { return length * width; }                         // 计算矩形的面积
    void Show() override                                                         // 显示矩形的信息
    {
        cout << "Shape: Rectangle\n";
        cout << "Length: " << length << "\n";
        cout << "Width: " << width << "\n";
        cout << "Perimeter: " << 2 * (length + width) << "\n";
        cout << "Area: " << GetArea() << "\n";
    }
};

class Triangle : public Shape // 三角形派生类，继承自Shape
{
private:
    double x1, y1, x2, y2, x3, y3; // 三个顶点的坐标

public:
    Triangle() : x1(0), y1(0), x2(0), y2(0), x3(0), y3(0) {} // 默认构造函数
    Triangle(double x1_, double y1_, double x2_, double y2_, double x3_, double y3_)
        : x1(x1_), y1(y1_), x2(x2_), y2(y2_), x3(x3_), y3(y3_) {} // 带参数的构造函数
    double GetArea() override                                     // 计算三角形的面积
    {
        double a = sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
        double b = sqrt((x3 - x2) * (x3 - x2) + (y3 - y2) * (y3 - y2));
        double c = sqrt((x1 - x3) * (x1 - x3) + (y1 - y3) * (y1 - y3));
        double p = (a + b + c) / 2;
        return sqrt(p * (p - a) * (p - b) * (p - c));
    }
    void Show() override // 显示三角形的信息
    {
        cout << "Shape: Triangle\n";
        cout << "Vertex 1: (" << x1 << ", " << y1 << ")\n";
        cout << "Vertex 2: (" << x2 << ", " << y2 << ")\n";
        cout << "Vertex 3: (" << x3 << ", " << y3 << ")\n";
        cout << "Perimeter: " << sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)) + sqrt((x3 - x2) * (x3 - x2) + (y3 - y2) * (y3 - y2)) + sqrt((x1 - x3) * (x1 - x3) + (y1 - y3) * (y1 - y3)) << "\n";
        cout << "Area: " << GetArea() << "\n";
    }
};

int main()
{
    Shape *s1 = new Circle(0, 0, 5);            // 创建一个圆形对象
    Shape *s2 = new Rectangle(3, 4);            // 创建一个矩形对象
    Shape *s3 = new Triangle(0, 0, 3, 0, 0, 4); // 创建一个三角形对象

    s1->Show(); // 显示圆形信息
    s2->Show(); // 显示矩形信息
    s3->Show(); // 显示三角形信息

    delete s1; // 释放内存
    delete s2;
    delete s3;

    return 0;
}

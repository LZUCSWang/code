/*
 * @Author: 王贤义
 * @FilePath: \code\C+++C\c++\6\1pic.cpp
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
#define M_PI 3.14159265358979323846
class Shape
{
protected:
    double area;

public:
    Shape() {}
    virtual double GetArea() { return 0; }
    virtual void Show() {}
};

class Circle : public Shape
{
private:
    double x, y, r;

public:
    Circle() : x(0), y(0), r(0) {}
    Circle(double x_, double y_, double r_) : x(x_), y(y_), r(r_) {}
    double GetArea() override { return M_PI * r * r; }
    void Show() override
    {
        cout << "Shape: Circle\n";
        cout << "Center: (" << x << ", " << y << ")\n";
        cout << "Radius: " << r << "\n";
        cout << "Diameter: " << r * 2 << "\n";
        cout << "Circumference: " << 2 * M_PI * r << "\n";
        cout << "Area: " << GetArea() << "\n";
    }
    void Set(double x_, double y_, double r_)
    {
        x = x_;
        y = y_;
        r = r_;
    }
};

class Rectangle : public Shape
{
private:
    double length, width;

public:
    Rectangle() : length(0), width(0) {}
    Rectangle(double length_, double width_) : length(length_), width(width_) {}
    double GetArea() override { return length * width; }
    void Show() override
    {
        cout << "Shape: Rectangle\n";
        cout << "Length: " << length << "\n";
        cout << "Width: " << width << "\n";
        cout << "Perimeter: " << 2 * (length + width) << "\n";
        cout << "Area: " << GetArea() << "\n";
    }
    void Set(double length_, double width_)
    {
        length = length_;
        width = width_;
    }
};

class Triangle : public Shape
{
private:
    double x1, y1, x2, y2, x3, y3;

public:
    Triangle() : x1(0), y1(0), x2(0), y2(0), x3(0), y3(0) {}
    Triangle(double x1_, double y1_, double x2_, double y2_, double x3_, double y3_)
        : x1(x1_), y1(y1_), x2(x2_), y2(y2_), x3(x3_), y3(y3_) {}
    double GetArea() override
    {
        double a = sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
        double b = sqrt((x3 - x2) * (x3 - x2) + (y3 - y2) * (y3 - y2));
        double c = sqrt((x1 - x3) * (x1 - x3) + (y1 - y3) * (y1 - y3));
        double p = (a + b + c) / 2;
        return sqrt(p * (p - a) * (p - b) * (p - c));
    }
    void Show() override
    {
        cout << "Shape: Triangle\n";
        cout << "Vertex 1: (" << x1 << ", " << y1 << ")\n";
        cout << "Vertex 2: (" << x2 << ", " << y2 << ")\n";
        cout << "Vertex 3: (" << x3 << ", " << y3 << ")\n";
        cout << "Perimeter: " << sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)) + sqrt((x3 - x2) * (x3 - x2) + (y3 - y2) * (y3 - y2)) + sqrt((x1 - x3) * (x1 - x3) + (y1 - y3) * (y1 - y3))
             << "\n";
        cout << "Area: " << GetArea() << "\n";
    }
    void Set(double x1_, double y1_, double x2_, double y2_, double x3_, double y3_)
    {
        x1 = x1_;
        y1 = y1_;
        x2 = x2_;
        y2 = y2_;
        x3 = x3_;
        y3 = y3_;
    }
};
int main()
{
    Shape *p;
    Circle c1(30, 45, 35);
    Circle c2(30, 89, 23);
    Rectangle r1(1, 2);
    Rectangle r2(28, 24);
    Triangle t1(34, 45, 89, 45, 54, 67);
    Triangle t2(22, 34, 67, 43, 86, 64);
    Shape *Shaplist[6] = {&c1, &c2, &r1, &r2, &t1, &t2};
    for (int i = 0; i < 6; i++)
    {
        p = Shaplist[i];
        p->Show();
    }
    return 0;
}
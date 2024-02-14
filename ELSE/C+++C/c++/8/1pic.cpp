/*
 * @Author: 王贤义
 * @FilePath: \code\C+++C\c++\8\1pic.cpp
 * @Description: 图形面积计算程序
 */

#include <iostream>
using namespace std;
#include <cmath>

class Shape
{
public:
    /**
     * @description: 计算图形面积的纯虚函数
     * @return {double} 图形的面积
     */
    virtual double getArea() = 0; // 纯虚函数
};

class Circle : public Shape
{
private:
    double radius, x_, y_;

public:
    /**
     * @description: Circle类的构造函数，初始化圆的半径和圆心坐标
     * @param {double} r 圆的半径
     * @param {double} x 圆心的x坐标
     * @param {double} y 圆心的y坐标
     */
    Circle(double r, double x, double y) : radius(r), x_(x), y_(y) {}

    /**
     * @description: Circle类的构造函数，只初始化圆的半径
     * @param {double} r 圆的半径
     */
    Circle(double r) : radius(r) {}

    /**
     * @description: 计算圆的面积
     * @return {double} 圆的面积
     */
    double getArea()
    {
        return 3.14 * radius * radius;
    }
};

class Rectangle : public Shape
{
private:
    double width, height, x_, y_;

public:
    /**
     * @description: Rectangle类的构造函数，初始化矩形的宽度、高度和左上角坐标
     * @param {double} w 矩形的宽度
     * @param {double} h 矩形的高度
     * @param {double} x 矩形左上角的x坐标
     * @param {double} y 矩形左上角的y坐标
     */
    Rectangle(double w, double h, double x, double y) : width(w), height(h), x_(x), y_(y) {}

    /**
     * @description: Rectangle类的构造函数，只初始化矩形的宽度和高度
     * @param {double} w 矩形的宽度
     * @param {double} h 矩形的高度
     */
    Rectangle(double w, double h) : width(w), height(h) {}

    /**
     * @description: 计算矩形的面积
     * @return {double} 矩形的面积
     */
    double getArea()
    {
        return width * height;
    }
};

class Triangle : public Shape
{
private:
    double x1_, y1_, x2_, y2_, x3_, y3_;

public:
    /**
     * @description: Triangle类的构造函数，初始化三角形的三个顶点坐标
     * @param {double} x1 第一个顶点的x坐标
     * @param {double} y1 第一个顶点的y坐标
     * @param {double} x2 第二个顶点的x坐标
     * @param {double} y2 第二个顶点的y坐标
     * @param {double} x3 第三个顶点的x坐标
     * @param {double} y3 第三个顶点的y坐标
     */
    Triangle(double x1, double y1, double x2, double y2, double x3, double y3) : x1_(x1), y1_(y1), x2_(x2), y2_(y2), x3_(x3), y3_(y3) {}

    /**
     * @description: 计算三角形的面积
     * @return {double} 三角形的面积
     */
    double getArea()
    {
        return 0.5 * abs((x1_ - x3_) * (y2_ - y3_) - (x2_ - x3_) * (y1_ - y3_));
    }
};

int main()
{
    Shape *shape;

    Circle circle(5); // 创建一个半径为5的圆对象
    Rectangle rectangle(4, 6); // 创建一个宽度为4、高度为6的矩形对象
    Triangle triangle(0, 0, 1, 0, 0, 1); // 创建一个顶点坐标为(0, 0)，(1, 0)，(0, 1)的三角形对象

    shape = &circle;
    cout << "Circle area: " << shape->getArea() << endl;

    shape = &rectangle;
    cout << "Rectangle area: " << shape->getArea() << endl;

    shape = &triangle;
    cout << "Triangle area: " << shape->getArea() << endl;

    return 0;
}

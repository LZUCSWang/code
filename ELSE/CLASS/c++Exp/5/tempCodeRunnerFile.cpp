/*
 * @Author: 王贤义
 * @FilePath: \code\C+++C\c++\5\1pic.cpp
 * @Description: 设计三个图形类：Circle（圆）、Rectangle（矩形）、Triangle（三角形）；
1、Cirlce 类基本信息：圆心坐标、半径；
Rectangle 类基本信息：长、宽；
Triangle 类基本信息：三个顶点坐标；
其中：成员变量为 private 属性，成员函数为public 属性；
2、每个图形类有多个构造函数：缺省构造函数、带参数的构造函数；
3、每个图形类有计算图形的面积GetArea()，显示图形的基本信息函数Show()，修改基本信息的函数Set(形参)。以Circle 类为例：通过GetArea()计算圆的面积，Show()函数中显示圆心坐标、直径、周长、面积等基本信息；Set(int x,int y, int r)函数可以修改圆心坐标和半径。

 */

#include <iostream>
#include <cmath>
using namespace std;
#define M_PI 3.14159265358979323846

// 圆形类
class Circle
{
private:
    double x, y; // 圆心坐标
    double r;    // 半径
public:
    Circle()
    {
        x = y = r = 0; // 默认构造函数，将圆心坐标和半径初始化为0
    }
    Circle(double x, double y, double r)
    {
        this->x = x;
        this->y = y;
        this->r = r; // 构造函数，根据给定的圆心坐标和半径进行初始化
    }
    double GetArea()
    {
        return M_PI * r * r; // 计算圆的面积
    }
    void Show()
    {
        cout << "Circle: Center=(" << x << "," << y << "), Radius=" << r << endl;
        cout << "Diameter=" << 2 * r << ", Circumference=" << 2 * M_PI * r << ", Area=" << GetArea() << endl;
        // 输出圆的信息，包括圆心、半径、直径、周长和面积
    }
    void Set(double x, double y, double r)
    {
        this->x = x;
        this->y = y;
        this->r = r; // 设置圆的圆心坐标和半径
    }
};

// 矩形类
class Rectangle
{
private:
    double length; // 长
    double width;  // 宽
public:
    Rectangle()
    {
        length = width = 0; // 默认构造函数，将长度和宽度初始化为0
    }
    Rectangle(double length, double width)
    {
        this->length = length;
        this->width = width; // 构造函数，根据给定的长度和宽度进行初始化
    }
    double GetArea()
    {
        return length * width; // 计算矩形的面积
    }
    void Show()
    {
        cout << "Rectangle: Length=" << length << ", Width=" << width << endl;
        cout << "Perimeter=" << 2 * (length + width) << ", Area=" << GetArea() << endl;
        // 输出矩形的信息，包括长度、宽度、周长和面积
    }
    void Set(double length, double width)
    {
        this->length = length;
        this->width = width; // 设置矩形的长度和宽度
    }
};

// 三角形类
class Triangle
{
private:
    double x1, y1; // 第一个顶点坐标
    double x2, y2; // 第二个顶点坐标
    double x3, y3; // 第三个顶点坐标
public:
    Triangle() {}
    bool isValid(double x1, double y1, double x2, double y2, double x3, double y3)
    {
        if (x1 == x2 && y1 == y2 || x1 == x3 && y1 == y3 || x2 == x3 && y2 == y3)
        {
            cerr << "Error: Invalid triangle!" << endl; // 输出无效三角形的错误信息
            return false;
        }
        return true;
    }
    Triangle(double x1, double y1, double x2, double y2, double x3, double y3)
    {
        if (!isValid(x1, y1, x2, y2, x3, y3))
        {
            return;
        }
        this->x1 = x1;
        this->y1 = y1;
        this->x2 = x2;
        this->y2 = y2;
        this->x3 = x3;
        this->y3 = y3; // 构造函数，根据给定的三个顶点坐标进行初始化
    }
    double GetArea()
    {
        return 0.5 * abs(x1 * y2 + x2 * y3 + x3 * y1 - x2 * y1 - x3 * y2 - x1 * y3); // 计算三角形的面积
    }
    void Show()
    {
        if (!isValid(x1, y1, x2, y2, x3, y3))
        {
            return;
        }
        cout << "Triangle: (" << x1 << "," << y1 << ") to (" << x2 << "," << y2 << ") to (" << x3 << "," << y3 << ")" << endl;
        cout << "Area=" << GetArea() << endl;
        // 输出三角形的信息，包括三个顶点坐标和面积
    }
    void Set(double x1, double y1, double x2, double y2, double x3, double y3)
    {
        if (!isValid(x1, y1, x2, y2, x3, y3))
        {
            return;
        }
        this->x1 = x1;
        this->y1 = y1;
        this->x2 = x2;
        this->y2 = y2;
        this->x3 = x3;
        this->y3 = y3; // 设置三角形的三个顶点坐标
    }
};

int main()
{
    Circle circle;
    Rectangle rectangle;
    Triangle triangle;
    int choice;

    while (true)
    {
        cout << "Choose the shape to create (1: Circle, 2: Rectangle, 3: Triangle, 0: Exit): ";
        cin >> choice;

        if (choice == 0)
        {
            break;
        }

        switch (choice)
        {
        case 1:
        {
            double x, y, r;
            cout << "Enter the center coordinates (x, y) and radius: ";
            cin >> x >> y >> r;
            circle.Set(x, y, r);
            circle.Show();
            break;
        }
        case 2:
        {
            double length, width;
            cout << "Enter the length and width: ";
            cin >> length >> width;
            rectangle.Set(length, width);
            rectangle.Show();
            break;
        }
        case 3:
        {
            double x1, y1, x2, y2, x3, y3;
            cout << "Enter the coordinates of the three vertices (x1, y1), (x2, y2), (x3, y3): ";
            cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
            triangle.Set(x1, y1, x2, y2, x3, y3);
            triangle.Show();
            break;
        }
        default:
            cout << "Invalid choice. Please try again." << endl;
            break;
        }
    }

    return 0;
}

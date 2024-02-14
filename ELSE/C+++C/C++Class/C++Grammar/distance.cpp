#include <bits/stdc++.h>
using namespace std;
#define MAX 10000

class Point
{
public:
    Point(double xi, double yi) : X(xi), Y(yi) {}
    double GetX() { return X; }
    double GetY() { return Y; }
    friend double Distance(Point &a, Point &b);

private:
    double X, Y;
};

double Distance(Point &a, Point &b)
{
    double dx = a.X - b.X;
    double dy = a.Y - b.Y;
    return sqrt(dx * dx + dy * dy);
}

class A
{

public:
    void Display() { cout << x << endl; }

private:
    friend class B; //友元类声明
    int x;
};
// class B
// {
// public:
//     void Set(int i) { Aobject.x = i; }
//     void Display() { Aobject.Display(); }

// private:
//     A Aobject;
// };
class B
{
public:
    void Set(A &Aobject, int i)
    {
        Aobject.x = i;
    }
    void Display(A &Aobject)
    {
        Aobject.Display();
    }
};
void test1()
{

    Point p1(3.0, 4.0), p2(6.0, 8.0);
    double d = Distance(p1, p2);
    cout << "The distance is:" << d << endl;
}
void test2()
{
    B b;
    A a;
    b.Set(a, 10);
    b.Display(a);
}
int main()
{
    test2();
    return 0;
}
#include <bits/stdc++.h>
using namespace std;
#define N 1e5
#define INF 2e9
#define MAX 10000000
#define ll long long
class Circle
{
public:
    Circle()
    {
        cout << "Circle()" << endl;
        r = 1;
    }
    Circle(double rr)
    {
        cout << "Circle(double r)" << endl;
        r = rr;
    }
    Circle(const Circle &c)
    {
        cout << "Circle (const Circle&c)" << endl;
        r = c.r;
    }
    ~Circle()
    {
        cout << "Destructor" << endl;
    }
    int r;
    double calPerimeter()
    {
        return 2 * 3.14 * r;
    }
};

int main()
{
    Circle m_Circle;
    m_Circle.r = 10;
    cout << m_Circle.calPerimeter() << endl;
}
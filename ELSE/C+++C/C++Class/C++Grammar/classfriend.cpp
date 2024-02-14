#include <bits/stdc++.h>
using namespace std;
#define MAX 10000

class A
{
public:
    A(int x) : a(x) {}
    int a;
};
class B
{
public:
    B(int x, int y) : aa(x), b(y) {}
    void out() { cout << "aa=" << aa.a << ",b=" << b << endl; }

private:
    int b;
    A aa;
};
int main()
{
    B objB(10, 20);
    objB.out();
}
#include <bits/stdc++.h>
using namespace std;
#define N 1e5
#define INF 2e9
#define MAX 10000000
#define ll long long

class Myprint
{
public:
    void operator()(string text)
    {
        cout << text << endl;
    }
};
void test1()
{
    Myprint myprint;
    myprint("hello");
}

class Myadd
{
public:
    int operator()(const int a, const int b)
    {
        return a + b;
    }
};
void test2()
{
    int a = 10, b = 100;
    Myadd myadd;
    cout << myadd(a, b) << endl;
}
int main()
{
    test1();
    test2();
}
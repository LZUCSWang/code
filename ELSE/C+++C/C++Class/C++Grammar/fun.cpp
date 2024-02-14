#include <iostream>
using namespace std;
void sample()
{
    cout << "test" << endl;
}
typedef void funtype();
typedef int (*callfuntype)(int, int);
inline int sum(int x, int y) { return x + y; };
inline int mul(int x, int y) { return x * y; };
inline void callfun(callfuntype funtypepoint, int a, int b)
{
    cout << funtypepoint(a, b) << endl;
}
void app(int *&pa, int n)
{
    pa = new int[n];
    if (pa == NULL)
    {
        cout << "error" << endl;
        return;
    }
    for (int i = 0; i < n; i++)
    {
        pa[i] = 0;
    }
}
int main()
{
    int (*pp)(int, int);

    sample();
    (&sample)();
    (*&sample)();
    funtype *p = sample;
    p();
    (*p)();
    int a, b;
    cin >> a >> b;
    pp = sum;
    cout << pp(a, b) << endl;
    pp = mul;
    callfun(sum, a, b);
    callfun(mul, a, b);
    cout << pp(a, b) << endl;
    cout << sample << endl;
    cout << &sample << endl;
    cout << *&sample << endl;
    a = 11, b = 22;
    int c = 33, *pi[3];
    pi[0] = &a;
    pi[1] = &b;
    pi[2] = &c;
    for (int i = 0; i < 3; i++)
        cout << *pi[i] << endl;
    double(*pf[3])[2]; //数组指针
    double aa[2] = {1.1, 2.2}, bb[2] = {3.3, 4.4}, cc[2] = {5.5, 6.6};
    pf[0] = &aa;
    pf[1] = &bb;
    pf[2] = &cc;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            cout << *(*pf[i] + j) << ' ';
        }
        cout << endl;
    }
    int *ary = NULL, *t, n;
    cin >> n;
    app(ary, n);
    for (int i = 0; i < n; i++)
    {
        ary[i] = 10 + i;
        cout << ary[i] << ' ';
    }
    cout << endl;
    delete[] ary;
}
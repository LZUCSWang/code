#include <bits/stdc++.h>
using namespace std;
#define N 1e5
#define INF 2e9
#define MAX 10000000
#define ll long long
int fun1(int a, int b, int c);
int fun1(int a, int b, int c, int d)
{
    return a + b + c + d;
}
int fun1(int a, int b = 10, int c = 100)
{
    return a + b + c;
}
int main()
{
    cout << fun1(1, 2, 3, 4) << endl;
    cout << fun1(1, 2, 3) << endl;
    cout << fun1(1) << endl;
}
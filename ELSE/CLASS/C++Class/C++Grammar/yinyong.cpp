#include <iostream>
using namespace std;
int &maxRef(int &, int &);
int main()
{
    int a, b;
    cout << "Input a,b";
    cin >> a >> b;
    cout << maxRef(a, b) << endl;
}
int &maxRef(int &x, int &y)
{
    // int temp = x;
    if (x > y)
        return x;
    else
        return y;
}
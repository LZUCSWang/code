#include <bits/stdc++.h>
using namespace std;
void digui(int n)
{
    for (int i = 14; i >= 0; i--)
    {
        int t = pow(2, i);
        if (n >= t)
        {
            if (i == 0)
                cout << "2(0)";
            else if (i == 1)
                cout << "2";
            else
            {
                cout<<"2(";
                digui(i);
                cout<<")";
            }
            n -= t;
            if (n)
            {
                cout << "+";
            }
        }
    }
}
int main(){
    int n;
    cin>>n;
    digui(n);
    return 0;
}
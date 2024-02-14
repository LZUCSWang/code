#include <bits/stdc++.h>
using namespace std;
int main()
{
    char ac[] = {'a', 'b', 'c', '\0'};
    char acc[] = {'a', 'b', 'c'};
    char accc[] = {'a', 'b', 'c'};
    cout << sizeof(acc) << endl;
    cout << sizeof(ac) << endl;
    char *s = "program";
    cout << (s + 1) << endl;
    for (int i = 0; i < 4; i++)
    {
        cout << i;
        cout << accc[i] << ' ';
        // cout<<'a';
    }
    cout << endl;
    cout << ac << endl;
    // char acc[]="abc";
    // cout<<acc<<endl;
}
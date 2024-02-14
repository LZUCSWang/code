#include <bits/stdc++.h>
#include <algorithm>
using namespace std;
#define MAX 100000
int main()
{
    int datas[11], k = 1, cnt = 0;
    for (int i = 1; i <= 11; i++)
    {
        char t;
        t = getchar();
        if (isdigit(t))
        {
            datas[k++] = t - '0';
            cnt += (t - '0') * (k - 1);
        }
    }
    getchar();
    char t=getchar();
    if (cnt % 11 == t - '0' || cnt%11 ==10 && t=='X')
        cout << "Right" << endl;
    else
    {
        cout << datas[1] << '-' << datas[2] << datas[3] << datas[4] << '-' << datas[5] << datas[6] << datas[7] << datas[8] << datas[9] << '-';
        if (cnt % 11 == 10)
            cout << "X";
        else
            cout << cnt % 11;
    }
    // cout<<datas[1]<<" "<<datas[2]<<" "<<datas[3]<<" "<<datas[4]<<" "<<datas[5]<<" "<<datas[6]<<" "<<datas[7]<<" "<<datas[8]<<" "<<datas[9]<<" "<<datas[10]<<endl;
}
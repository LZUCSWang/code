#include <bits/stdc++.h>
#include <algorithm>
using namespace std;
void sorttt()
{
    int datas[10] = {9, 6, 3, 8, 5, 2, 7, 4, 1, 0};
    for (int i = 0; i < 10; i++)
        cout << datas[i] << " ";

    sort(datas, datas + 10, greater<int>()); //第三个参数不用写（如果是从小到大排序的话）
    //大到小 greater<int>() 小到大 less<int>()
    sort(datas, datas + 10, [&](const int &datas, const int &b)
         { return datas < b; }); //自定义操作符
    cout << endl;
    for (int i = 0; i < 10; i++)
        cout << datas[i] << " ";
}
void binary()
{
    int datas[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    cout << upper_bound(datas, datas + 10, 5) - datas + 1 << endl;
    cout << lower_bound(datas, datas + 10, 5) - datas + 1 << endl;
    cout << binary_search(datas, datas + 5, 5) << endl;
}
int main()
{
    sorttt();
}
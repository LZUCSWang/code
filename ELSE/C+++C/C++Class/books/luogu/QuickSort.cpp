// #include <bits/stdc++.h>
// using namespace std;
// int datas[100009], n;
// int main()
// {
//     cin >> n;
//     for (int i = 1; i <= n; i++)
//         cin >> datas[i];
//     sort(datas + 1, datas + n + 1);
//     for (int i = 1; i <= n; i++)
//         cout << datas[i] << " ";
// }
#include<bits/stdc++.h>
using namespace std;
int n,datas[1000001];
void qsort(int l,int r){
    int mid=datas[(l+r)/2];
    int i=l,j=r;
    do{
        while (datas[i]<mid)i++;
        while (datas[j]>mid)j--;
        if (i<=j){
            swap(datas[i],datas[j]);
            i++;
            j--;

        }

    }while (i<=j);
    if (l<j)qsort(l,j);
    if (i<r)qsort(i,r);
}
int main(){
    cin>>n;
    for (int i=1;i<=n;i++)cin>>datas[i];
    qsort(1,n);
    for (int i=1;i<=n;i++)cout<<datas[i]<<" ";
}
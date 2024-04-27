#include<bits/stdc++.h>
using namespace std;
#define ll long long
int main(){
    ll datas,b,c;
    cin >> datas >> b >> c;
    ll d = b-datas;
    ll e = datas+(c-1)*d;
    cout << (datas+e)*c/2 << endl;
    return 0;
}
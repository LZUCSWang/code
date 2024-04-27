#include <bits/stdc++.h>
using namespace std;
#define N 100000
#define INF 2e9
#define MAX 30
int main()
{
    string s;
    cin >> s;
    int n = s.size();
    for (int i=n-1;i>=0;i--){
        if (s[i]=='a'){
            printf("%d",i+1);
            return 0;
        }
    }
    printf("-1");
}
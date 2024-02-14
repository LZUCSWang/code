#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define MAX 10000001
#define node pair<int, int>
node exgcd(int a, int b)
{
    if (b == 0)
    {
        return make_pair(1, 0);
    }
    node temp = exgcd(b, a % b);
    node ans = make_pair(temp.second, temp.first - a / b * temp.second);
    return ans;
}
int main()
{
    int a, b;
    cin >> a >> b;
    node ans = exgcd(a, b);
    printf("%d", (ans.first % b + b) % b);
}
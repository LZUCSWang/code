#include <bits/stdc++.h>
#include <algorithm>
using namespace std;
#define MAX 100000
int main()
{
    int num[] = {1, 2, 3};
    do
    {
        cout << num[0] << " " << num[1] << " " << num[2] << endl;
    } while (next_permutation(num, num + 3));
    return 0;
}
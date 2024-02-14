#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define MAX 100005
vector<int> orign_num;
int orign_table[MAX];
int flag_print;
// 11
// 33 1 13 12 34 38 27 22 32 -1 21
int n, orign_num_size;
int vis_num[MAX], vis_pos[MAX];
void input()
{
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        int a;
        cin >> a;
        orign_table[i] = a;
        if (a != -1)
        {
            orign_num.push_back(a);
        }
    }
    orign_num_size = orign_num.size();
    sort(orign_num.begin(), orign_num.end());
}
int MOD(int a, int p)
{
    while (a < 0)
        a += p;
    return a % p;
}
void print_without_space(int target)
{
    if (flag_print)
        printf(" ");
    printf("%d", target);
    flag_print = 1;
}
void print_orign()
{
    for (int i = 0; i < orign_num.size(); i++)
    {
        cout << orign_num[i] << " ";
    }
    cout << endl;
}
void main_work()
{
    while (true)
    {
        int i;
        for (i = 0; i < orign_num_size; i++)
        {
            if (vis_num[orign_num[i]] == 1)
            {
                continue;
            }
            if (orign_table[MOD(orign_num[i], n)] == orign_num[i])
            {
                // printf("%d ", orign_num[i]);
                print_without_space(orign_num[i]);
                vis_num[orign_num[i]] = vis_pos[MOD(orign_num[i], n)] = 1;
                break;
            }
            else
            {
                int flag = 0;
                for (int j = 0; j < n; j++)
                {
                    int next_pos = MOD(MOD(orign_num[i], n) + j, n);
                    if (vis_pos[next_pos] && orign_table[next_pos] != orign_num[i])
                        continue;
                    if (!vis_pos[next_pos] && orign_table[next_pos] != orign_num[i])
                        break;
                    // printf("%d ", orign_num[i]);
                    print_without_space(orign_num[i]);
                    vis_num[orign_num[i]] = vis_pos[next_pos] = flag = 1;
                    break;
                }
                if (flag)
                    break;
            }
        }
        if (i == orign_num_size)
            break;
    }
}
int main()
{
    input();
    // print_orign();
    main_work();
    return 0;
}
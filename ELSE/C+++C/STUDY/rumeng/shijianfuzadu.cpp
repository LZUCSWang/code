#include <bits/stdc++.h>
using namespace std;
#define N 1e5
#define INF 2e9
#define MAX 100000

string lines[MAX];
int idx;
bool used[150], ef[150];
int t, codes, ans_to_check;
int getfuza()
{
    string temp;
    int ans_ = 0;
    bool flag = false;
    cin >> temp;
    for (int i = 1; i <= temp.size(); i++)
    {
        if (temp[i] == 'n')
            flag = true;
        if (temp[i] >= '0' && temp[i] <= '9')
            ans_ = ans_ * 10 + temp[i] - '0';
    }
    return flag ? ans_ : 0;
}
int sread(int lineidx)
{
    string temp = lines[lineidx];
    int len = temp.length();
    int ans_ = 0;
    while (idx < len)
    {
        if (temp[idx] == 'n')
        {
            idx+=2;
            return 10000000;
        }
        if (temp[idx] >= '0' && temp[idx] <= '9')
        {
            while (temp[idx] >= '0' && temp[idx] <= '9')
            {
                ans_ = ans_ * 10 + temp[idx] - '0';
                idx++;
            }
        }
        if (temp[idx] == ' ')
        {
            idx++;
            break;
        }
    }
    return ans_;
}
int getans()
{
    stack<int> s;
    char flag = 0;
    int ret = 0, ret_temp = 0;
    memset(used, 0, sizeof(used));
    memset(ef, 0, sizeof(ef));
    for (int i = 1; i <= codes; i++)
    {
        if (lines[i][0] == 'F')
        {
            idx = 4;
            char c = lines[i][2];
            if (used[c])
                return -1;
            int a = sread(i), b = sread(i);
            used[c] = true;
            s.push(c);
            if (b - a > 1000)
            {
                if (!flag)
                {
                    ret_temp++;
                    ret = max(ret, ret_temp);
                    ef[c] = true;
                }
            }
            else if (a > b)
            {
                if (!flag)
                {
                    flag = c;
                }
            }
        }
        else if (lines[i][0] == 'E')
        {
            if (s.empty())
                return -1;
            char top = s.top();
            s.pop();
            used[top] = false;
            if (flag == top)
            {
                flag = 0;
            }
            if (ef[top])
            {
                ret_temp--;
                ef[top] = false;
            }
        }
    }
    if (s.size())
        return -1;
    return ret;
}
int main()
{
    cin >> t;
    int ans = 0;
    while (t--)
    {
        scanf("%d ", &codes);
        ans_to_check = getfuza();
        getchar();
        for (int i = 1; i <= codes; i++)
            getline(cin, lines[i]);
        if (codes & 1)
        {
            // cout << "ERR" << endl;
            printf("ERR\n");
            continue;
        }
        ans = getans();
        if (ans == -1)
            printf("ERR\n");
        else if (ans == ans_to_check)
            printf("Yes\n");
        else
            printf("No\n");
    }
    return 0;
}
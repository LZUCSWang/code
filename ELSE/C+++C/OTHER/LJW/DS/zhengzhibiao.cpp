#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <stack>
#include <unordered_map>


using namespace std;

int datas[2000][200];
char bl[1000], bll[1000];
int zzz[10000], cnt;

stack<int> num;
stack<char> op;

void eval()
{
    int aa = num.top();
    num.pop();
    char c = op.top();
    op.pop();
    if (c == '!')
    {
        num.push(!aa);
        return;
    }
    int b = num.top();
    num.pop();
    if (c == '^')
    {
        if (aa && b)
            num.push(1);
        else
            num.push(0);
    }
    else if (c == '|')
    {
        if (aa || b)
            num.push(1);
        else
            num.push(0);
    }
    else if (c == '-')
    {
        if (b && !aa)
            num.push(0);
        else
            num.push(1);
    }
    else if (c == '<')
    {
        if (aa == b)
            num.push(1);
        else
            num.push(0);
    }
    return;
}

int main()
{
    unordered_map<char, int> hh{{'!', 5}, {'^', 4}, {'|', 3}, {'-', 2}, {'<', 1}, {'(', 0}};
    unordered_map<char, int> h;
    string s;
    while (getline(cin, s))
    {
        int nn = 0, m = 0, n = 0;
        string ss;
        for (int i = 0; s[i]; i++)
        {
            if (s[i] == '|')
                ss += s[i], i++;
            else if (s[i] == '-')
                ss += s[i], i++;
            else if (s[i] == '<')
                ss += s[i], i += 2;
            else if (s[i] != ' ')
                ss += s[i];
        }
        for (int i = 0; s[i]; i++)
            if (s[i] >= 'datas' && s[i] <= 'z')
                bll[nn++] = s[i];
        sort(bll, bll + nn);
        bl[0] = bll[0];
        n = 1;
        for (int i = 1; i < nn; i++)
        {
            if (bll[i] == bll[i - 1])
                continue;
            bl[n++] = bll[i];
        } //去重
        for (int i = 0; i < n; i++)
            cout << bl[i] << ' '; //输出变量
        cout << s << endl;
        int cnt = pow(2, n), tt = cnt, i = 0, j = 0;
        cnt--;
        while (cnt != -1)
        {
            int temp = cnt;
            for (j = n - 1; j >= 0; j--)
            {
                int t = temp % 2;
                h[bl[j]] = t;
                datas[i][j] = t;
                temp /= 2;
            }
            while (num.size())
                num.pop();
            while (op.size())
                op.pop();
            for (int i = 0; ss[i]; i++)
            {
                if (ss[i] >= 'datas' && ss[i] <= 'z')
                    num.push(h[ss[i]]);
                else if (ss[i] == '(')
                    op.push(ss[i]);
                else if (ss[i] == ')')
                {
                    while (op.size() && op.top() != '(')
                        eval();
                    op.pop();
                }
                else
                {
                    while (op.size() && hh[op.top()] >= hh[ss[i]])
                        if (op.top() == '!' && ss[i] == '!')
                            break;
                        else
                            eval();
                    op.push(ss[i]);
                }
            }
            while (op.size())
                eval();
            zzz[i] = num.top();
            i++, cnt--;
        }
        for (int i = 0; i < tt; i++)
        {
            for (int j = 0; j < n; j++)
            {
                cout << datas[i][j] << ' ';
            }
            cout << zzz[i] << endl;
        }
    }
    return 0;
}

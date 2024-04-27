#include <bits/stdc++.h>
using namespace std;
#define MAX 100005
int hashs[MAX];
map<string, int> MAP;
int n, p;
string s;
int MOD(int a, int p)
{
    while (a < 0)
        a += p;
    return a % p;
}
int pow_index(int keys)
{
    int index = MOD(keys, p);
    if (hashs[index] == -1)
    {
        hashs[index] = keys;
        return index;
    }
    for (int i = 1;; i++)
    {
        if (index + i * i >= p)
        {
            int temp = MOD(index + i * i, p);
            if (hashs[temp] == -1)
            {
                hashs[temp] = keys;
                return temp;
            }
        }
        else
        {
            if (hashs[index + i * i] == -1)
            {
                hashs[index + i * i] = keys;
                return index + i * i;
            }
        }
        if (index - i * i < 0)
        {
            int temp = MOD(index - i * i, p);
            if (hashs[temp] == -1)
            {
                hashs[temp] = keys;
                return temp;
            }
        }
        else
        {
            if (hashs[index - i * i] == -1)
            {
                hashs[index - i * i] = keys;
                return index - i * i;
            }
        }
    }
    return index;
}

int hash_map()
{
    int s_len = s.length();
    int hash_val = 0;
    for (int i = s_len - 1; i > s_len - 4; i--)
    {
        if (i == -1)
        {
            break;
        }
        hash_val += (s[i] - 'A') * pow(32, s_len - 1 - i);
    }
    return hash_val;
}
void test_hash_map()
{
    s = "AZDEG";
    int hash_val = hash_map();
    cout << hash_val << endl;
}
// 4 11
// HELLO ANNK ZOE LOLI

int save[MAX];
int main()
{
    cin >> n >> p;
    getchar();
    while (n > p)
        n++;
    memset(hashs, -1, sizeof(hashs));
    for (int i = 1; i <= n; i++)
    {
        cin >> s;
        if (MAP[s] != 0)
        {
            printf("%d", save[MAP[s]]);
            if (i != n)
            {
                printf(" ");
            }
            continue;
        }
        save[i] = pow_index(hash_map());
        printf("%d", save[i]);
        if (i != n)
        {
            printf(" ");
        }
        MAP[s] = i;
    }
    // // test_hash_map();
    // for (int i = 1; i <= n; i++)
    // {
    //     printf("%d", save[i]);
    //     if (i != n)
    //     {
    //         printf(" ");
    //     }
    // }
}
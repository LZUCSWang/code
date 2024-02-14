#include <bits/stdc++.h>
using namespace std;
int V, len, now, cnt[27], sum[27];
int get_max(int len)
{
    return ((len - (len / 26 + 1)) * (len / 26 + 1) * (len % 26) + (26 - len % 26) * (len / 26) * (len - len / 26)) / 2;
}
bool check(int x, int n)
{                                // 当前位置i放x字母后，后面的n个位置是否符合要求
    memset(cnt, 0, sizeof(cnt)); // cnt记录后面n个位置放置的对应字符数量
    int add1 = 0, add2 = 0;
    for (int j = 26; j >= x + 1; j--)
        add1 += sum[j]; // 1~i-1里边比当前插入字符大的字符数量
    sum[x]++;           // 当前字符数量增加1
    for (int L = 1; L <= n; L++)
    { // 当前位置i放了x,看当前位置i后面剩下的n个位置能不能放好字母使得达到V的条件，这是一个预测过程
        // ma保存i位置后面的n个位置能增加的最大逆序对个数 L-1-cnt[j]+num
        // L-1-cnt[j]是当前字符之后的比当前字符小的字符数量的最大值
        // num是1~pos+L-1前的比当前放置字符字典序大的字符数量
        int ma = -1, pos = 0, num = 0;
        for (int j = 26; j >= 1; j--)
        { // 枚举i位置后面的n个位置，每个位置放什么字母
            if (L - 1 - cnt[j] + num > ma)
            { // L - 1是算i+1到i+L的个数(不算i+L自己)
                // - cnt[j] 如果在i+1到当前位置i+L前有放过字母j，然后当前位置i+L也尝试放j，
                // 那当前位置不和前面放j的位置构成逆序对 要减掉前面放j的位置个数
                ma = L - 1 - cnt[j] + num;
                pos = j; // 在L这个位置放上字母j
            }
            num += sum[j]; // num是从1-i位置里大于等于j的数的个数
            // 因为j是从26逆着放到1的 到下一轮循环时，j--假设记为j'，那要求的1-i里比j'大的数就是num
            // 那么这个j'会和前面已经确定好的所有属于26~(j'+1)的数构成逆序对
            // 其实最后的num是算的所有大于等于1的个数，但是没关系，它不会更新到ma里
        }
        add2 += ma, cnt[pos]++; // L这个位置确定下来，放pos这个字母
    }
    if (now + add1 + add2 >= V)
    { // now是i这个位置以前的所有逆序对个数,
        // add1是i位置放进x后,x与前面所有字母构成的逆序对
        // add2是i位置放进x后，后面的位置的所有数能增加的逆序对个数，分为2部分，
        // 1、后面位置所有的数与1~i部分的数构成的逆序对个数
        // 2、后面所有位置L，分别与从i+1~i+L-1之间的数构成的逆序对个数，然后这些逆序对的和
        now += add1; // now更新i位置确定好放字母x后，从1~i位置所有逆序对个数
        return true;
    }
    else
    { // i这个位置放x不能使逆序对个数>=V
        sum[x]--;
        return false;
    }
}
signed main()
{
    string ans = "";
    cin >> V;
    for (int i = 1;; i++)
    {
        if (get_max(i) >= V)
        { // i这个长度的字符串最多能有get_max(i)个逆序对 如果get_max(i) >= V，
            // 那么i这个长度就是我们需要的最短长度
            len = i;
            break;
        }
    }
    for (int i = 1; i <= len; i++)
    { // 按长度从左往右尝试放字母
        for (int j = 1; j <= 26; j++)
        { // 按顺序'a'-'z' 26个字母放   先用1-26代表这26个字母
            if (check(j, len - i))
            {                             // 现在是在第i位放j字母  看i后面的len-i个字母能否符合条件
                ans += char(j + 'a' - 1); // 符合条件就把j放在i这个位置
                break;                    // 然后尝试放下一个位置
            }
        }
    }
    cout << ans << '\n';
    return 0;
}

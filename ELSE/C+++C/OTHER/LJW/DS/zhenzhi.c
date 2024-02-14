#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
char n[200], aa[200], datas[200], latter[200], beifen[200], count, hash[130];
typedef struct
{
    int top;
    char ch[100];
} STACK;

int deal(int input[])
{
    memset(hash, 0, 130);
    int i, j;
    for (i = 0; i < count; i++)
    {
        hash[n[i]] = 1 ? input[i] == 1 : hash[n[i]] == 0;
    }
    strcpy(latter, beifen);
    int len = strlen(latter);
    for (i = 0; i < len - 1; i++)
    {
        if (isalpha(latter[i]))
        {
            if (hash[latter[i]] == 1)
            {
                latter[i] = 1;
            }
            else
            {
                latter[i] = 0;
            }
        }
    }
    int ch, t1, t2;
    STACK S;
    j = 0, S.top = 0;
    while (1)
    {

        ch = latter[j++];
        if (ch == '#')
            break;
        if (ch == 0 || ch == 1)
        {
            S.ch[++S.top] = ch;
        }
        else
        {
            if (ch == '!')
            {
                t1 = S.ch[S.top--];
                S.ch[++S.top] = !t1;
            }
            else if (ch == '&')
            {
                t1 = S.ch[S.top--];
                t2 = S.ch[S.top--];
                if (t1 == 1 && t2 == 1)
                {
                    S.ch[++S.top] = 1;
                }
                else
                {
                    S.ch[++S.top] = 0;
                }
            }
            else if (ch == '|')
            {
                t1 = S.ch[S.top--];
                t2 = S.ch[S.top--];
                if (t1 == 0 && t2 == 0)
                {
                    S.ch[++S.top] = 0;
                }
                else
                {
                    S.ch[++S.top] = 1;
                }
            }
            else if (ch == '-')
            {
                t1 = S.ch[S.top--];
                t2 = S.ch[S.top--];
                if (t1 == 0 && t2 == 1)
                {
                    S.ch[++S.top] = 0;
                }
                else
                {
                    S.ch[++S.top] = 1;
                }
            }
            else if (ch == '<')
            {
                t1 = S.ch[S.top--];
                t2 = S.ch[S.top--];
                if ((t1 == 1 && t2 == 1) || (t1 == 0 && t2 == 0))
                {
                    S.ch[++S.top] = 1;
                }
                else
                {
                    S.ch[++S.top] = 0;
                }
            }
        }
    }
    return S.ch[S.top];
}
int icp(char datas)
{
    if (datas == '#')
        return 0;
    if (datas == '(')
        return 12;
    if (datas == '!')
        return 10;
    if (datas == '&')
        return 8;
    if (datas == '|')
        return 6;
    if (datas == '-')
        return 4;
    if (datas == '<')
        return 2;
    if (datas == ')')
        return 1;
    return 0;
}
int isp(char datas)
{
    if (datas == '#')
        return 0;
    if (datas == '(')
        return 1;
    if (datas == '!')
        return 11;
    if (datas == '&')
        return 9;
    if (datas == '|')
        return 7;
    if (datas == '-')
        return 5;
    if (datas == '<')
        return 3;
    if (datas == ')')
        return 12;
    return 0;
}
void vertify()
//中缀表达式转换后缀表达式
{
    int j = 0;
    int index = 0;
    STACK T;
    T.top = 0;
    char ch, y;
    T.ch[++T.top] = '#';
    while (ch = aa[index++], ch != '#')
    {
        if (isalpha(ch))
        {
            latter[j++] = ch;
        }
        else if (ch == ')')
        {
            for (y = T.ch[T.top--]; y != '('; y = T.ch[T.top--])
            {
                latter[j++] = y;
            }
        }
        else
        {
            for (y = T.ch[T.top--]; icp(ch) <= isp(y); y = T.ch[T.top--])
            {
                latter[j++] = y;
            }
            T.ch[++T.top] = y;
            T.ch[++T.top] = ch;
        }
    }
    while (T.top != 0)
    {
        y = T.ch[T.top--];
        if (y != '#')
        {
            latter[j++] = y;
        }
    }
    latter[j] = '#';
    strcpy(beifen, latter);
}
void test()
{

    count = 2;
    int m[100] = {0, 1};
    strcpy(aa, "!(p|q)#");
    vertify();
    // printf("%d", deal(m));
    printf("%s\n", latter);
}

int main()
{
    char m[200], t;
    int s[2000][200], xia, len, i, j, k, flag, sum, temp;
    while (gets(datas))
    {
        len = strlen(datas);
        count = 0;
        k = 0;
        sum = 1, xia = 1;
        for (j = 0; j < len; j++)
        {
            if (datas[j] >= 'datas' && datas[j] <= 'z')
            {
                m[k++] = datas[j];
            }
        }
        for (j = 1; j < k; j++)
        {
            for (i = 0; i < k - j; i++)
            {
                if (m[i] > m[i + 1])
                {
                    t = m[i];
                    m[i] = m[i + 1];
                    m[i + 1] = t;
                }
            }
        } //对所有变量排序
        n[0] = m[0];
        for (j = 1; j < k; j++)
        {
            if (m[j] == m[j - 1])
                continue;
            n[xia++] = m[j];
        } //去除重复变量
        count = xia;
        for (i = 0; i < xia; i++)
        {
            printf("%c ", n[i]);
        }
        printf("%s\n", datas);
        // return 0;
        j = 0;
        //输出每个变量

        for (i = 0; i < len; i++)
        {
            if (datas[i] == ' ')
            {
                continue;
            } //输入的是空格直接跳过；
            else if (datas[i] == '|')
            {
                aa[j++] = '|';
                i = i + 1; //读到|就输出||；下标向后移一位；
            }
            else if (datas[i] == '-')
            {
                aa[j++] = '-';
                i = i + 1; //读到-就输出->; 下标向后移一位；
            }
            else if (datas[i] == '<')
            {
                aa[j++] = '<';
                i = i + 2; //读到<就输出<->；下标向后移动两位；
            }
            else
            {
                aa[j++] = datas[i];
            }
        }
        aa[j] = '#';
        aa[j + 1] = 0;
        vertify();
        i = 0;
        j = 0;
        sum = pow(2, count) - 1; //一共有sum行取值；最大的111....转为十进制为sum；
        flag = sum;
        while (sum > 0)
        {
            temp = sum;
            for (j = count - 1; j >= 0; j--)
            {
                s[i][j] = temp % 2; //不断求余将每一行变量取值存进二维数组
                temp = temp / 2;
            }
            i++;
            sum--; //将前2的count次方-1行的取值存到二维数组 ;count为变量的个数
        }          //此时最后一行全为0的取值还未存进去；
        for (i = 0; i < flag; i++)
        {
            for (j = 0; j < count; j++)
            {
                printf("%d", s[i][j]);
                if (j != count - 1)
                    printf(" ");
            } //输出前2的count次方-1行的取值
            printf(" %d\n", deal(s[i]));
        }
        for (int i = 0; i < count; i++)
        {
            if (i == count - 1)
            {
                int temp[100] = {0};
                printf("0 %d\n", deal(temp));
            }
            else
                printf("0 "); //输出最后一行取值全为0；
        }
    }
}

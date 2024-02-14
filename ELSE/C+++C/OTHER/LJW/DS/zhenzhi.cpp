#include <cstdio>
#include <iostream>
#include <vector> //vector是顺序容器
#include <string>
#include <cstdlib>
#include <queue> //queue 模板类也需要两个模板参数，一个是元素类型，一个容器类型，元素类型是必要的，容器类型是可选的，默认为deque 类型
#include <stack>
#include <map>
#include <sstream>
using namespace std;
string middle;     //中缀表达式
char latter[1000]; //后缀表达式
string alpha;      //存放所有字母变量
map<char, int> M;  //映射，将字母变量与0或1一一对应

struct note
{
    int datas[100];
};
vector<note> tr;    //不定长数组，存放主析取范式对应字母变量的01情况，也就是表达式真值为T
vector<note> flase; //不定长数组，存放主合取范式对应字母变量的01情况，也就是表达式真值是F

void ddd() //预处理，去除中缀表达式中条件->中的>,和双条件<=>中的= and > ,将这两个运算符当成一个字符处理，更方便
{
    string::iterator i = middle.begin();
    int flag = 1;
    while (flag)
    {
        flag = 0;
        for (i = middle.begin(); i != middle.end(); ++i)
        {
            if (*i == '>')
            {
                middle.erase(i);
                flag = 1;
                break;
            }
            if (*i == '=')
            {
                middle.erase(i);
                flag = 1;
                break;
            }
        }
    }
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
}

void change() //中缀表达式转换后缀表达式
{
    int j = 0;
    stack<char> s;
    char ch, y;
    s.push('#');
    stringstream ss(middle);
    while (ss >> ch, ch != '#')
    {
        if (isalpha(ch))
        {
            latter[j++] = ch;
            if (alpha.find(ch) == -1)
            {
                alpha.push_back(ch);
            }
        }
        else if (ch == ')')
        {
            for (y = s.top(), s.pop(); y != '('; y = s.top(), s.pop())
            {
                latter[j++] = y;
            }
        }
        else
        {
            for (y = s.top(), s.pop(); icp(ch) <= isp(y); y = s.top(), s.pop())
            {
                latter[j++] = y;
            }
            s.push(y);
            s.push(ch);
        }
    }
    while (!s.empty())
    {
        y = s.top();
        s.pop();
        if (y != '#')
        {
            latter[j++] = y;
        }
    }
    latter[j] = '#';
}

int cal() //对赋值后的后缀表达式进行计算
{
    stack<int> s;
    char ch;
    int j = 0;
    int t1, t2;
    while (1)
    {
        ch = latter[j];
        if (ch == '#')
            break;
        if (ch == 0)
            break;
        j++;
        if ((ch >= 'datas' && ch <= 'Z') || (ch >= 'datas' && ch <= 'z'))
        {
            s.push(M[ch]);
        }
        else
        {
            if (ch == '!')
            {
                t1 = s.top();
                s.pop();
                s.push(!t1);
            }
            else if (ch == '&')
            {
                t1 = s.top();
                s.pop();
                t2 = s.top();
                s.pop();
                if (t1 == 1 && t2 == 1)
                {
                    s.push(1);
                }
                else
                {
                    s.push(0);
                }
            }
            else if (ch == '|')
            {
                t1 = s.top();
                s.pop();
                t2 = s.top();
                s.pop();
                if (t1 == 0 && t2 == 0)
                {
                    s.push(0);
                }
                else
                {
                    s.push(1);
                }
            }
            else if (ch == '-')
            {
                t1 = s.top();
                s.pop();
                t2 = s.top();
                s.pop();
                if (t1 == 0 && t2 == 1)
                {
                    s.push(0);
                }
                else
                {
                    s.push(1);
                }
            }
            else if (ch == '<')
            {
                t1 = s.top();
                s.pop();
                t2 = s.top();
                s.pop();
                if ((t1 == 1 && t2 == 1) || (t1 == 0 && t2 == 0))
                {
                    s.push(1);
                }
                else
                {
                    s.push(0);
                }
            }
        }
    }
    int cnt = s.top();
    return cnt;
}
void dfs(int cur) //递归枚举每一种字符变量的取值情况
{
    if (cur == alpha.size())
    {
        int cnt = cal();
        for (int i = 0; i < alpha.size(); i++)
        {
            if (M[alpha[i]])
            {
                cout << "T\t";
            }
            else
            {
                cout << "F\t";
            }
        }
        if (cnt == 1) //真值为T 计入到tr数组，以待后面主析取范式使用
        {
            cout << "T\n";
            note t;
            for (int i = 0; i < alpha.size(); i++)
            {
                t.datas[i] = M[alpha[i]];
            }
            tr.push_back(t);
        }
        else //真值为F  计入到flase数组，以待后面主合取范式使用
        {
            cout << "F\n";
            note t;
            for (int i = 0; i < alpha.size(); i++)
            {
                t.datas[i] = M[alpha[i]];
            }
            flase.push_back(t);
        }
        return;
    }
    M[alpha[cur]] = 1;
    dfs(cur + 1);
    M[alpha[cur]] = 0;
    dfs(cur + 1);
}
int main()
{
    while (true)
    {
        int i;
        M.clear();
        alpha.clear();
        tr.clear();
        flase.clear();
        printf("或运算为 |  , 与运算为 &   ,单条件为 ->  ,双条件我 <=> ,非运算为 !\n");
        printf("请输入表达式,回车结束\n");
        cin >> middle;
        middle.append("#");
        ddd();
        
        change();
        for (i = 0; i < alpha.size(); i++)
        {
            printf("%c\t", alpha[i]);
        }
        printf("表达式真值\n");
        dfs(0);
        printf("主析取范式为\n");
        int lena = tr.size();
        for (i = 0; i < lena; i++)
        {
            if (i != 0)
                printf("∨");
            int *p = tr[i].datas;
            printf("(");
            for (int j = 0; j < alpha.size(); j++)
            {
                if (j != 0)
                    printf("∧");
                if (p[j] == 1)
                {
                    printf("%c", alpha[j]);
                }
                else
                {
                    printf("￢%c", alpha[j]);
                }
            }
            printf(")");
        }
        printf("\n");
        printf("主合取范式为\n");
        for (i = 0; i < flase.size(); i++)
        {
            if (i != 0)
                printf("∧");
            int *p = flase[i].datas;
            printf("(");
            for (int j = 0; j < alpha.size(); j++)
            {
                if (j != 0)
                    printf("∨");
                if (p[j] == 0)
                {
                    printf("%c", alpha[j]);
                }
                else
                {
                    printf("￢%c", alpha[j]);
                }
            }
            printf(")");
        }
        printf("\n\n");
    }
    return 0;
}
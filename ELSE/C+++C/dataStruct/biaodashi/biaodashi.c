#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define N 40000
int you(char datas) //优先级
{
    switch (datas)
    {
    case '(':
        return 0;
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
        return 2;
    case '^':
        return 3;
    case ')':
        return 4;
    }
}
int yunsuan(char c, int datas, int b) //运算
{
    switch (c)
    {
    case '+':
        return datas + b;
    case '-':
        return datas - b;
    case '*':
        return datas * b;
    case '/':
        return datas / b;
    case '^':
        return pow(datas, b);
    }
}
int main()
{
    FILE *f = fopen("input.txt", "r");
    int stack1[N], flag = 0, k, t1 = 0, t2 = 0;
    char stack2[N], input[N], temp[N];
    fscanf(f, "%s", input); //全读入
    fclose(f);
    for (int i = 0; i < strlen(input); i++)
    {
        k = 0;
        if (input[i] == '(') //左括号直接入栈
        {
            stack2[++t2] = '(';
            continue;
        }
        while (i == 0 || isdigit(input[i]) != 0 || input[i - 1] == '(') //读数据，第一个，是数字，或前是左括号
        {
            temp[k++] = input[i++]; //将读入的数字暂存，（用于读多位）
            flag = 1;
        }
        temp[k] = '\0';
        if (flag == 1)
        {
            stack1[++t1] = atoi(temp); //将读入的数字转换为整数，并入栈
            flag = 0;
        }
        if (input[i] == '#') //结束符
        {
            int cnt;
            while (t2 > 0)
            {
                if (stack2[t2] == ')' || stack2[t2] == '(')
                {
                    t2--;
                    continue;
                }
                cnt = yunsuan(stack2[t2--], stack1[t1 - 1], stack1[t1]);
                t1 -= 1;
                stack1[t1] = cnt;
            }
            f = fopen("output.txt", "w");
            fprintf(f, "int ");
            fprintf(f, "%d", cnt);
            fclose(f);
            return 0;
        }

        if (isdigit(input[i]) == 0) //如果不是数字
        {
            if (t2 == 0 || you(input[i]) > you(stack2[t2])) //判断优先级
                stack2[++t2] = input[i];
            else
            {
                if (stack2[t2] == ')') //右括号
                {
                    t2--;
                    while (stack2[t2] != '(') //直到栈顶为左括号
                    {
                        stack1[t1 - 1] = yunsuan(stack2[t2], stack1[t1 - 1], stack1[t1]);
                        t1--;
                        t2--;
                    }
                }
                else
                {
                    stack1[t1 - 1] = yunsuan(stack2[t2], stack1[t1 - 1], stack1[t1]);
                    t1--;
                }
                stack2[t2] = input[i];
                while (t2 > 1 && you(stack2[t2]) <= you(stack2[t2 - 1])) //直到栈顶优先级大于栈顶前一个
                {
                    stack1[t1 - 1] = yunsuan(stack2[t2 - 1], stack1[t1 - 1], stack1[t1]);
                    stack2[t2 - 1] = stack2[t2];
                    t1--;
                    t2--;
                }
            }
        }
    }
}
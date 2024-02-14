#include <stdio.h>
#define MAX 10000000
struct stack //定义一个栈
{
    int top;        //用top来储存栈顶
    char data[MAX]; //用数组data来存储栈中的元素
} S1;
//清空栈
void init()
{
    S1.top = -1;
}
//入栈
void push(char x)
{
    S1.data[++S1.top] = x;
}
//出栈
void pop()
{
    S1.top--;
}
//判断栈是否为空
int empty()
{
    if (S1.top == -1)
        return 1;
    else
        return 0;
}
//获得栈顶元素
char top()
{
    return S1.data[S1.top];
}
int main()
{
    char c;
    init();//先将栈初始化
    while (scanf("%c", &c)) //判断括号是否匹配
    {
        if (c == '$')//如果输入的是$，则结束
            break;
        if (c == '(' || c == '[' || c == '{')//如果输入的是左括号，则入栈
            push(c);
        if (c == ')')//如果输入的是),判断栈顶元素是否为(
        {
            if (empty() || top() != '(')//如果栈不为空且栈顶元素不为(,则不匹配
            {
                printf("NO");
                return 0;
            }
            pop();//弹出已经匹配好的栈顶元素
        }
        if (c == ']')//同上
        {
            if (empty() || top() != '[')
            {
                printf("NO");
                return 0;
            }
            pop();
        }
        if (c == '}')//同上
        {
            if (empty() || top() != '{')
            {
                printf("NO");
                return 0;
            }
            pop();
        }
    }
    empty() ? printf("YES") : printf("NO");
    return 0;
}

/*
@Author: 王贤义
 * @FilePath: \code\C+++C\c++\10\1stack.cpp
@Description: 堆栈实现及括号匹配检查
*/
#include <iostream>
#include <vector>
using namespace std;
const int MaxSize = 100; // 定义堆栈最大容量

typedef char ElemType;

class Stack
{
private:
    ElemType stack[MaxSize]; // 堆栈数组
    int top;                 // 堆栈指针，指向栈顶元素

public:
    Stack()
    { // 构造函数，初始化堆栈指针
        top = -1;
    }
    void InitStack()
    { // 初始化堆栈
        top = -1;
    }

    bool IsEmpty()
    { // 判断堆栈是否为空
        return top == -1;
    }

    bool IsFull()
    { // 判断堆栈是否已满
        return top == MaxSize - 1;
    }

    void push(ElemType item)
    { // 元素进栈
        if (IsFull())
        {
            cout << "Stack is full" << endl;
            return;
        }
        top++;
        stack[top] = item;
    }

    ElemType pop()
    { // 弹出栈顶元素并返回其值
        if (IsEmpty())
        {
            cout << "Stack is empty" << endl;
            return -1;
        }
        ElemType item = stack[top];
        top--;
        return item;
    }

    ElemType peek()
    { // 返回栈顶元素的值，但不移动栈顶指针
        if (IsEmpty())
        {
            cout << "Stack is empty" << endl;
            return -1;
        }
        return stack[top];
    }

    void ClearStack()
    { // 清空堆栈
        top = -1;
    }
};

/**

@description: 检查括号匹配
@param {string} exp 待检查的表达式
@return {bool}
*/
bool checkBalance(string exp)
{
    Stack s;
    for (int i = 0; i < exp.size(); i++)
    {
        char c = exp[i];
        if (c == '(' || c == '{' || c == '[')
        {
            s.push(c);
        }
        else if (c == ')' || c == '}' || c == ']')
        {
            if (s.IsEmpty())
            {
                return false;
            }
            char top = s.pop();
            if ((c == ')' && top != '(') || (c == '}' && top != '{') || (c == ']' && top != '['))
            {
                return false;
            }
        }
    }
    return s.IsEmpty();
}
int main()
{
    string exp;
    while (true)
    {
        cout << "Please input an expression (input 'exit' to exit): ";
        cin >> exp;
        if (exp == "exit")
        {
            break;
        }
        cout << checkBalance(exp) << endl;
    }
    return 0;
}
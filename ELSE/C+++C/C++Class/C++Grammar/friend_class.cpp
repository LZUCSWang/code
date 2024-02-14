#include <bits/stdc++.h>
using namespace std;
#define MAX 10000

class A
{
private:
    int i;
    friend void FriendFun(A *, int);//友元函数声明

public:
    void MemberFun(int);
};

void FriendFun(A *ptr, int x)
{
    ptr->i = x;
};

void A::MemberFun(int x)
{
    i = x;
};


#include <bits/stdc++.h>
using namespace std;
#define MAX 10000

class X
{
    int DatMen;

public:
    static void Stafun(int i, X *ptr);
};

void X::Stafun(int i, X *ptr)
{
    // this->DatMen = i; this 只能用于非静态成员函数
    ptr->DatMen = i;
}

void g()
{
    X obj;
    X::Stafun(10, &obj); //这种比较好
    obj.Stafun(10, &obj);
}

class Goods
{
public:
    Goods(int w)
    {
        weight = w;
        total_weight += 2;
    }
    ~Goods()
    {
        total_weight -= weight;
    }
    static int TotalWeight()
    {
        return total_weight;
    }
    Goods *next;

private:
    int weight;
    static int total_weight;
};
int Goods::total_weight = 0; //静态成员变量的定义，初始化。

void purchase(Goods *&f, Goods *&r, int w)
{
    Goods *p = new Goods(w);
    p->next = NULL;
    if (f = NULL)
        f = r = p;
    else
    {
        r->next = p;
        r = r->next;
    }
}

void sale(Goods *&f, Goods *&r)
{
    if (f == NULL)
        cout << "No any goods!" << endl;
    Goods *q = f;
    f = f->next;
    delete q;
    cout << "saled." << endl;
}
#include <bits/stdc++.h>
using namespace std;
class location
{
public:
    location(int x = 0, int y = 0)
    {
        this->A = x;
        this->B = y;
        cout << "hello" << endl;
    }
    location(const location &p)
    {
        this->A = p.A;
        this->B = p.B;
        cout << "bye" << endl;
    }
    int get_A()
    {
        return A;
    }
    int get_B()
    {
        return B;
    }
    ~location()
    {
        cout << "bye" << endl;
    }

private:
    int A, B;
};
class loca
{
public:
    loca(int x = 0, int y = 0)
    {
        this->A = x;
        this->B = y;
        cout << "hello" << endl;
    }
    int get_A()
    {
        return A;
    }
    int get_B()
    {
        return B;
    }

private:
    int A, B;
};

void f(location p)
{
    cout << p.get_A() << endl;
}
void test1()
{
    location p1(1, 2);
    location p2(p1);
    cout << p2.get_A() << ' ' << p2.get_B() << endl;
    // return 0;
}
void test2()
{
    location p1(1, 2);
    f(p1);
}
location pp()
{
    cout << "pp" << endl;
    int a;
    // cin >> a;
    location p1(1, 2);
    cin >> a;
    return p1;
}
void test3()
{
    location p1;
    int a;
    cin >> a;
    p1 = pp();
}
void test4()
{
    loca p1(1, 2);
    loca p2 = p1;
    cout << &p1 << ' ' << &p2 << endl;
}
class name
{
public:
    name(char *pn);
    ~name();
    int get_len()
    {
        return size;
    }
    void print()
    {
        cout << pname << endl;
    }

protected:
    char *pname;
    int size;
};
name ::name(char *pn)
{
    cout << "Constructing  " << pn << endl;
    pname = new char[strlen(pn) + 1];
    if (pname != 0)
        strcpy(pname, pn);
    size = strlen(pn);
}
name ::~name()
{
    cout << "Destructing  " << pname << endl;
    delete[] pname;
    size = 0;
}
void test5()
{
    name p1("hello");
    name p2 = p1;
    cout << p1.get_len() << endl;
    cout << p2.get_len() << endl;
    p1.print();
    p1.~name();
    system("pause");
    p2.print();
    // p2 = p1;
}
int main()
{
    test5();
    return 0;
}
#include <bits/stdc++.h>
using namespace std;
#define N 1e5
#define INF 2e9
#define MAX 10000000
#define ll long long

class Person
{
    friend ostream &operator<<(ostream &out, const Person &p)
    {
        out << p.a << p.b;
        return out;
    }
    friend istream &operator>>(istream &in, Person &p)
    {
        in >> p.a >> p.b;
        return in;
    }

private: 
    int a,
        b;

public:
    Person() {}
    Person(int a, int b) : a(a), b(b) {}
};
int main()
{
    Person p(1, 2);
    Person p2;
    cout << p << endl;
    cin >> p2;
    cout << p2 << endl;
    return 0;
}
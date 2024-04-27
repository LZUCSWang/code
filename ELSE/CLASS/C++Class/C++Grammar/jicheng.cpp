#include <bits/stdc++.h>
using namespace std;
#define N 1e5
#define INF 2e9
#define MAX 10000000
#define ll long long

class BasePage
{
public:
    void header()
    {
        cout << "head" << endl;
    }
    void footer()
    {
        cout << "footer" << endl;
    }
    void left()
    {
        cout << "left list" << endl;
    }
};

class Java : public BasePage
{
public:
    void content()
    {
        cout << "Java Page" << endl;
    }
};
class Python : public BasePage
{
public:
    void content()
    {
        cout << "Python Page" << endl;
    }
};
void test1()
{
    Java java;
    java.header();
    java.footer();
    java.left();
    java.content();

    Python python;
    python.header();
    python.footer();
    python.left();
    python.content();
}
int main()
{
    test1();
}
#include <bits/stdc++.h>
using namespace std;
#define N 1e5
#define INF 2e9
#define MAX 10000000
#define ll long long

class Building;
class Gay
{
public:
    Gay();
    void vis();
    void supervis();

private:
    Building *building;
};
class Building
{
    friend void Gay::supervis();

public:
    Building();
    string livingroom;

private:
    string bedroom;
};
Building::Building()
{
    bedroom = "woshi";
    livingroom = "keting";
}
void Gay::supervis()
{
    cout << building->bedroom << endl;
}
Gay::Gay()
{
    building = new Building;
}
void test0()
{
    Gay gg;
    gg.supervis();
}
int main()
{
    test0();
    return 0;
}
#include <bits/stdc++.h>
using namespace std;
#define N 1e5
#define INF 2e9
#define MAX 10000000
#define ll long long
class Building;
class goodGay
{
public:
    goodGay();
    void visit();

private:
    Building *building;
};
class Building
{
    friend class goodGay;

public:
    Building();
    string m_SittingRoom;

private:
    string m_BedRoom;
};
Building ::Building()
{
    this->m_SittingRoom = "客厅";
    this->m_BedRoom = "卧室";
}
goodGay::goodGay()
{
    building = new Building;
}
void goodGay::visit()
{
    cout << "goodGay visit" << building->m_BedRoom << endl;
}

void test91()
{
    goodGay gg;
    gg.visit();
}
int main()
{
    test91();
    return 0;
}
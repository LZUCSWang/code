#include <bits/stdc++.h>
using namespace std;
#define MAX 10000

class counter
{

    static int num; //不依赖于任何一个对象，只依赖于类本身，
    //在类创建的时候就已经分配了内存，不需要对象来调用
public:
    void setnum(int i) { num = i; }
    void shownum() { cout << num << endl; }
};

int counter::num = 0;
int main()
{
    counter a, b;
    // a.setnum(10);
    a.shownum();
    b.shownum();
    a.setnum(10);
    // counter::num=100;
    a.shownum();
    b.shownum();
    return 0;
}
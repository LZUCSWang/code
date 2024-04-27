#include <bits/stdc++.h>
using namespace std;
#define N 1e5
#define INF 2e9
#define MAX 10000000
#define ll long long

class Score
{

    int math;
    int chinese;

public:
    int getMath() const
    {
        return math;
    }
    int getChinese() const
    {
        return chinese;
    }
    Score(int math, int chinese) : math(math), chinese(chinese) {}
    Score() : math(0), chinese(0) {} // chongzai
    Score operator+(const Score &B)
    {
        Score temp;
        temp.math = this->math + B.math;
        temp.chinese = this->chinese + B.chinese;
        return temp;
    }
};
void test0()
{
    Score a1(10, 20), a2(30, 40);
    Score a3 = a1 + a2;
    cout << a3.getChinese() << endl;
    cout << a3.getMath() << endl;
}
int main()
{
    test0();
    return 0;
}
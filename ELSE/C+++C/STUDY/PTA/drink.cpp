#include <bits/stdc++.h>
using namespace std;
#define MAXN 100000
int a[MAXN];
int n;
int A, B;
int main()
{
    ios::sync_with_stdio(false);
    cin >> A >> B >> n;
    int a = A, b = B;
    int i = 0;
    bool Aflag, Bflag;
    int Ahan, Ahua, Bhan, Bhua;
    while (i++ < n)
    {
        Aflag = Bflag = false;
        cin >> Ahan >> Ahua >> Bhan >> Bhua;
        int total = Ahan + Bhan;
        if (total == Ahua)
        {
            Aflag = true;
        }
        if (total == Bhua)
        {
            Bflag = true;
        }
        if (Aflag == Bflag)
        {
            continue;
        }
        else if (Aflag)
        {
            if (!(A--))
            {
                cout << "A" << endl
                     << b - B;
                return 0;
            }
        }
        else if (Bflag)
        {
            if (!(B--))
            {
                cout << "B" << endl
                     << a - A;
                return 0;
            }
        }
    }
}
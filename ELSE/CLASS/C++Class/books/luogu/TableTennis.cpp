#include <bits/stdc++.h>
using namespace std;
int record[10000000] = {0};
int main()
{
    char temp;
    int k = 0;
    while (1)
    {
        cin >> temp;
        if (temp == 'E' && k == 0)
        {
            cout << "0:0" << endl;
            cout << endl;
            cout << "0:0" << endl;
            return 0;
        }
        if (temp == 'E')
            break;
        if (temp == 'W')
            record[k++] = 1;
        else if (temp == 'L')
            record[k++] = 2;
    }
    int sa = 0, sb = 0;
    for (int i = 0; i < k; i++)
    {
        if (record[i] == 1)
            sa++;
        else if (record[i] == 2)
            sb++;
        if ((sa >= 11 || sb >= 11) && (abs(sa - sb) >= 2))
        {
            printf("%d:%d\n", sa, sb);
            sa = 0, sb = 0;
        }
        if (i == k - 1)
        {
            printf("%d:%d\n", sa, sb);
            sa = 0, sb = 0;
        }
    }
    printf("\n");
    for (int i = 0; i < k; i++)
    {
        if (record[i] == 1)
            sa++;
        else if (record[i] == 2)
            sb++;
        if ((sa >= 21 || sb >= 21) && (abs(sa - sb) >= 2))
        {
            printf("%d:%d\n", sa, sb);
            sa = 0, sb = 0;
        }
        if (i == k - 1)
        {
            printf("%d:%d\n", sa, sb);
            sa = 0, sb = 0;
        }
    }
}
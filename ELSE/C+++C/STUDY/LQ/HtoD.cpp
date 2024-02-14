#include <bits/stdc++.h>
using namespace std;
// #define MAXN 1000000
int n;
string a;
int main()
{
    cin >> n;
    while (n--)
    {
        cin >> a;
        int len = a.length();
        string res1 = "";
        for (int i = 0; i < len; i++)
        {
            switch (a[i])
            {
            case '0':
                res1 += "0000";
                break;
            case '1':
                res1 += "0001";
                break;
            case '2':
                res1 += "0010";
                break;
            case '3':
                res1 += "0011";
                break;
            case '4':
                res1 += "0100";
                break;
            case '5':
                res1 += "0101";
                break;
            case '6':
                res1 += "0110";
                break;
            case '7':
                res1 += "0111";
                break;
            case '8':
                res1 += "1000";
                break;
            case '9':
                res1 += "1001";
                break;
            case 'A':
                res1 += "1010";
                break;
            case 'B':
                res1 += "1011";
                break;
            case 'C':
                res1 += "1100";
                break;
            case 'D':
                res1 += "1101";
                break;
            case 'E':
                res1 += "1110";
                break;
            case 'F':
                res1 += "1111";
                break;
            }
        }
        int len2 = res1.length();
        switch (len2 % 3)
        {
        case 1:
            res1 = "00" + res1;
            break;
        case 2:
            res1 = "0" + res1;
            break;
        }
        string res2 = "";
        len2 = res1.length();
        for (int i = 0; i < len2; i += 3)
        {
            string temp = res1.substr(i, 3);
            if (i == 0 && temp == "000")
                res2 += "";
            else
                res2 += (temp == "000" ? "0" : temp == "001" ? "1"
                                           : temp == "010"   ? "2"
                                           : temp == "011"   ? "3"
                                           : temp == "100"   ? "4"
                                           : temp == "101"   ? "5"
                                           : temp == "110"   ? "6"
                                           : temp == "111"   ? "7"
                                                             : "");
        }
        cout << res2 << endl;
    }
}

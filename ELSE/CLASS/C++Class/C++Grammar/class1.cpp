#include <iostream>
#include <string>
#include <algorithm>

using namespace std;
// transform()
enum colour
{
    red,
    gree,
    blue,
    white,
    black
};
int main()
{
    string s1("Hello world!");
    colour c = red;
    for (; c < black; c = (colour)(c + 1))
    {
        cout << c << endl;
    }
    transform(s1.begin(), s1.end(), s1.begin(), ::toupper);
    cout << s1 << endl;
    // for (int i = 1; i = 300; i++)
    // {
    //     cout <<'\a';
    // }
}
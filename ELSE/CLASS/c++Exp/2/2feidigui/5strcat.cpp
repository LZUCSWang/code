#include <iostream>
#include <cstring>

using namespace std;

int main()
{
    char str1[20] = "Hello";
    char str2[10] = "World";

    strcat(str1, str2);

    cout << "Æ´½ÓºóµÄ×Ö·û´®£º" << str1 << endl;

    return 0;
}

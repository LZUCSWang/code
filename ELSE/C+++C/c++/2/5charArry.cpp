<<<<<<< HEAD
/*
 * @Author: 王贤义
 * @FilePath: \code\C+++C\c++\2\5charArry.cpp
 * @Description:
 */
=======
>>>>>>> 4b973315162d27f01fa06261e78d6fb1c889420e
#include <iostream>
#include <cstring>

using namespace std;

int main()
{
    char str1[20] = "Hello";
    char str2[10] = "World";
<<<<<<< HEAD
    int len1 = strlen(str1);
    int len2 = strlen(str2);

    // 使用字符数组的拷贝函数
=======

    // �ҵ�str1��ĩβ
    int len1 = strlen(str1);
    int len2 = strlen(str2);

    // ��str2���ַ���ӵ�str1��ĩβ
>>>>>>> 4b973315162d27f01fa06261e78d6fb1c889420e
    for (int i = 0; i < len2; i++)
    {
        str1[len1 + i] = str2[i];
    }
<<<<<<< HEAD
    str1[len1 + len2] = '\0';

    cout << "Using arry to copy:" << str1 << endl;
=======

    // ȷ��str1ĩβ��'\0'
    str1[len1 + len2] = '\0';

    cout << "ƴ�Ӻ���ַ�����" << str1 << endl;
>>>>>>> 4b973315162d27f01fa06261e78d6fb1c889420e

    return 0;
}

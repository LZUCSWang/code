/*
 * @Author: 王贤义
 * @FilePath: \code\C+++C\c++\2\5char.cpp
 * @Description: 编一程序，将两个字符串连接起来。结果取代第一个字符串。要求
                1、用字符数组，不用strcat 函数；
                2、用C 标准中的strcat 函数；
                3、用string 方法定义字符串变量；
 */

#include <iostream>
#include <cstring>

using namespace std;
int main()
{
    // Method 1: Using character arrays
    char str1[100] = "Hello";
    char str2[] = "World";
    int i = 0, j = 0;
    while (str1[i] != '\0')
    {
        i++;
    }
    while (str2[j] != '\0')
    {
        str1[i] = str2[j];
        i++;
        j++;
    }
    str1[i] = '\0';

    // Method 2: Using strcat function
    char str3[100] = "Hello";
    char str4[] = "World";
    strcat(str3, str4);

    // Method 3: Using string method
    string str5 = "Hello";
    string str6 = "World";
    str5 += str6;

    // Comparing the three methods
    cout << "Method 1: " << str1 << endl;
    cout << "Method 2: " << str3 << endl;
    cout << "Method 3: " << str5 << endl;
}
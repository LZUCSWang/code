/*
 * @Author: 王贤义
 * @FilePath: \code\C+++C\c++\9\1document.cpp
 * @Description: 该程序用于对用户输入的字符串进行加密和解密操作，并将加密后的数据保存到文件中。用户可以输入包含大小写字母、空格和数字的字符串，以'#'作为字符串输入的结束条件。程序将输入的字符进行加密，加密规则为将字母A变成E，a变成e，即将字母变成其后的第4个字母，W变A，X变成B，Y变成C，Z变成D，w变a，x变成b，y变成c，z变成d。保存加密后的数据时，以二进制文件方式保存。用户可以输入保存路径，如：C:\file.txt。在打开文件时，程序会对加密文件进行解密并显示在屏幕上。
 */

#include <iostream>
#include <fstream>
using namespace std;

// 加密函数
/**
 * @description: 将字符进行加密
 * @param {char} c 待加密的字符
 * @return {char} 加密后的字符
 */
char encrypt(char c)
{
    if (c >= 'A' && c <= 'Z')
    {
        return (c - 'A' + 4) % 26 + 'A';
    }
    else if (c >= 'a' && c <= 'z')
    {
        return (c - 'a' + 4) % 26 + 'a';
    }
    else
    {
        return c;
    }
}

// 解密函数
/**
 * @description: 将字符进行解密
 * @param {char} c 待解密的字符
 * @return {char} 解密后的字符
 */
char decrypt(char c)
{
    if (c >= 'A' && c <= 'Z')
    {
        return (c - 'A' + 22) % 26 + 'A';
    }
    else if (c >= 'a' && c <= 'z')
    {
        return (c - 'a' + 22) % 26 + 'a';
    }
    else
    {
        return c;
    }
}

int main()
{
    // 打开文件并写入加密数据
    ofstream fout;
    fout.open(".\\file.txt", ios::binary);
    if (!fout)
    {
        cout << "Failed to open file." << endl;
        return 1;
    }

    cout << "Please input the string you want to encrypt, end with '#':" << endl;
    char c;
    while (cin.get(c) && c != '#')
    {
        c = encrypt(c);
        fout.write((char *)&c, sizeof(char));
    }
    fout.close();

    // 读取加密数据并解密
    ifstream fin;
    fin.open(".\\file.txt", ios::binary);
    if (!fin)
    {
        cout << "Failed to open file." << endl;
        return 1;
    }

    cout << "The decrypted string is:" << endl;
    while (fin.read((char *)&c, sizeof(char)))
    {
        c = decrypt(c);
        cout << c;
    }
    fin.close();

    return 0;
}

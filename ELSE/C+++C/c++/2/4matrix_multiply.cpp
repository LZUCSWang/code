<<<<<<< HEAD
/*
 * @Author: 王贤义
 * @FilePath: \code\C+++C\c++\2\4matrix_multiply.cpp
 * @Description: 计算两个3*3矩阵的乘积
 */

#include <iostream>
using namespace std;

/**
 * @description: 计算矩阵乘法
 * @param {int} a 第一个矩阵A
 * @param {int} b 第二个矩阵B
 * @param {int} c 结果矩阵C
 * @return {*}
 */
void matrix_multiply(int a[3][3], int b[3][3], int c[3][3])
{
    for (int i = 0; i < 3; i++) // i表示行
    {
        for (int j = 0; j < 3; j++) // j表示列
        {
            c[i][j] = 0; // 初始化
            for (int k = 0; k < 3; k++)
            {
                c[i][j] += a[i][k] * b[k][j]; // 矩阵乘法
=======
#include <iostream>

using namespace std;

void matrix_multiply(int a[3][3], int b[3][3], int c[3][3])
{
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            c[i][j] = 0;
            for(int k=0;k<3;k++)
            {
                c[i][j] += a[i][k]*b[k][j];
>>>>>>> 4b973315162d27f01fa06261e78d6fb1c889420e
            }
        }
    }
}

int main()
{
    int a[3][3], b[3][3], c[3][3];
<<<<<<< HEAD
    cout << "Input A matrix(3*3)" << endl;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
=======
    cout << "�������a��" << endl;
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
>>>>>>> 4b973315162d27f01fa06261e78d6fb1c889420e
        {
            cin >> a[i][j];
        }
    }
<<<<<<< HEAD
    cout << "Input B matrix(3*3)" << endl;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
=======
    cout << "�������b��" << endl;
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
>>>>>>> 4b973315162d27f01fa06261e78d6fb1c889420e
        {
            cin >> b[i][j];
        }
    }
    matrix_multiply(a, b, c);
<<<<<<< HEAD
    cout << "The answer of A*B" << endl;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
=======
    cout << "����a�����b�ĳ˻�Ϊ��" << endl;
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
>>>>>>> 4b973315162d27f01fa06261e78d6fb1c889420e
        {
            cout << c[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}

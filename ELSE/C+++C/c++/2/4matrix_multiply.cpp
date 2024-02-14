<<<<<<< HEAD
/*
 * @Author: çŽ‹è´¤ä¹‰
 * @FilePath: \code\C+++C\c++\2\4matrix_multiply.cpp
 * @Description: è®¡ç®—ä¸¤ä¸ª3*3çŸ©é˜µçš„ä¹˜ç§¯
 */

#include <iostream>
using namespace std;

/**
 * @description: è®¡ç®—çŸ©é˜µä¹˜æ³•
 * @param {int} a ç¬¬ä¸€ä¸ªçŸ©é˜µA
 * @param {int} b ç¬¬äºŒä¸ªçŸ©é˜µB
 * @param {int} c ç»“æžœçŸ©é˜µC
 * @return {*}
 */
void matrix_multiply(int a[3][3], int b[3][3], int c[3][3])
{
    for (int i = 0; i < 3; i++) // iè¡¨ç¤ºè¡Œ
    {
        for (int j = 0; j < 3; j++) // jè¡¨ç¤ºåˆ—
        {
            c[i][j] = 0; // åˆå§‹åŒ–
            for (int k = 0; k < 3; k++)
            {
                c[i][j] += a[i][k] * b[k][j]; // çŸ©é˜µä¹˜æ³•
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
    cout << "ÊäÈë¾ØÕóa£º" << endl;
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
    cout << "ÊäÈë¾ØÕób£º" << endl;
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
    cout << "¾ØÕóaÓë¾ØÕóbµÄ³Ë»ýÎª£º" << endl;
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

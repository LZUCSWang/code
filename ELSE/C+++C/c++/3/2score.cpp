<<<<<<< HEAD
/*
 * @Author: 王贤义
 * @FilePath: \code\C+++C\c++\3\2score.cpp
 * @Description: 一个班有 5 名学生，每个学生修了五门课，1）求每个学生的平均成绩，并输出每个学生的学号，每门课程的成绩及平均值。2）求某门课程的平均分；
 */

#include <iostream>
using namespace std;

/**
 * @description: 计算每个学生的平均分
 * @param {int} sco 二维数组，表示每个学生的每门课程的成绩
 * @param {int} avsco 一维数组，表示每个学生的平均分
 * @return {*}
 */
=======
#include <iostream>
using namespace std;

>>>>>>> 4b973315162d27f01fa06261e78d6fb1c889420e
void averscore(int sco[][5], int avsco[]) // 二维数组的行数可以省略,但是列数不能省略
{
    for (int i = 0; i < 5; i++) // 遍历每个学生
    {
        int sum = 0;
        for (int j = 0; j < 5; j++) // 遍历每个学生的每门课程
        {
            sum += sco[i][j]; // 求每个学生的总分
        }
        avsco[i] = sum / 5; // 求每个学生的平均分
    }
}

<<<<<<< HEAD
/**
 * @description: 计算每门课程的平均分
 * @param {int} n 课程的编号
 * @return {*} 返回课程的平均分
 */
=======
>>>>>>> 4b973315162d27f01fa06261e78d6fb1c889420e
int avercourse(int (*psco)[5], int n) // 二维数组的行数不能省略,但是列数可以省略
{
    int sum = 0;
    for (int i = 0; i < 5; i++) // 遍历每个学生
    {
        sum += psco[i][n - 1]; // 求每门课程的总分
    }
    return sum / 5; // 求每门课程的平均分
}
int main()
{
    int num[5] = {1, 2, 3, 4, 5};
    int sco[5][5] = {0};
    int avsco[5] = {0};
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            cout << "Student " << num[i] << ", Course " << j + 1 << ": ";
            cin >> sco[i][j];
        }
    }
    averscore(sco, avsco);      // 求每个学生的平均分
    for (int i = 0; i < 5; i++) // 输出每个学生的平均分
    {
        cout << "Student " << num[i] << "'s scores: ";
        for (int j = 0; j < 5; j++)
        {
            cout << sco[i][j] << " ";
        }
        cout << "Average: " << avsco[i] << endl;
    }
    int t;
    cout << "Which course do you want to know the average score of? ";
    cin >> t;
    cout << "Average score of Course " << t << ": " << avercourse(sco, t) << endl; // 求课程的平均分
    return 0;
}

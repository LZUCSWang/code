<<<<<<< HEAD
/*
 * @Author: 王贤义
 * @FilePath: \code\C+++C\c++\4\2score\student.cpp
 * @Description: 功能函数实现，包括输入信息函数，计算平均分函数，查找最高分函数
 */

=======
>>>>>>> 4b973315162d27f01fa06261e78d6fb1c889420e
#include <iostream>
#include "student.h"

using namespace std;

<<<<<<< HEAD
/**
 * @description: 输入学生信息
 * @param {Student} stu 要输入学生的结构体数组
 * @param {int} number 要输入的学生数量
 * @return {*}
 */
=======
>>>>>>> 4b973315162d27f01fa06261e78d6fb1c889420e
void input_students(Student stu[], int number)
{
    for (int i = 0; i < number; i++)
    {
        cout << "Please enter NO." << i << " student info: num name class score1 score2 score3" << endl;
        cin >> stu[i].num >> stu[i].name >> stu[i].classname;
        cin >> stu[i].score[0] >> stu[i].score[1] >> stu[i].score[2];
    }
}

<<<<<<< HEAD
/**
 * @description: 计算每个学生各科的平均分，并存入到结构体数组中
 * @param {Student} stu 学生结构体数组
 * @param {int} number  学生数量
 * @return {*}
 */
=======
>>>>>>> 4b973315162d27f01fa06261e78d6fb1c889420e
void calculate_average_score(Student stu[], int number)
{
    for (int i = 0; i < number; i++)
    {
        stu[i].aver_score = (stu[i].score[0] + stu[i].score[1] + stu[i].score[2]) / 3.0;
    }
}

<<<<<<< HEAD
/**
 * @description: 顺序查找寻找平均分最高的学生
 * @param {Student} stu 学生结构体数组
 * @param {int} number  学生数量
 * @return {*}  返回平均分最高的学生的下标
 */
=======
>>>>>>> 4b973315162d27f01fa06261e78d6fb1c889420e
int find_highest_average_score(Student stu[], int number)
{
    int max_index = 0;
    float max_score = stu[0].aver_score;
    for (int i = 1; i < number; i++)
    {
        if (stu[i].aver_score > max_score)
        {
            max_index = i;
            max_score = stu[i].aver_score;
        }
    }
    return max_index;
}
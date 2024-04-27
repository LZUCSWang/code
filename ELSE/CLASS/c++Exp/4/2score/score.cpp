<<<<<<< HEAD
/*
 * @Author: 王贤义
 * @FilePath: \code\C+++C\c++\4\2score\score.cpp
 * @Description: 分析学生成绩总函数，包括输入学生信息、计算平均分、查找最高分等
 */

//g++ -o score score.cpp student.cpp
=======
>>>>>>> 4b973315162d27f01fa06261e78d6fb1c889420e
#include <iostream>
#include "student.h"

using namespace std;

int main()
{
    int number = 5;
    Student stu[20];
    // cout << "Please enter student number: ";
    // cin >> number;
    input_students(stu, number);
    calculate_average_score(stu, number);
    int max_index = find_highest_average_score(stu, number);
    cout << "Average scores:" << endl;
    for (int i = 0; i < number; i++)
    {
        cout << "Student " << i << ": " << stu[i].aver_score << endl;
    }
    cout << "The student with the highest average score:" << endl;
    cout << "Num: " << stu[max_index].num << endl;
    cout << "Name: " << stu[max_index].name << endl;
    cout << "Class: " << stu[max_index].classname << endl;
    cout << "Scores: " << stu[max_index].score[0] << " " << stu[max_index].score[1] << " " << stu[max_index].score[2] << endl;
    cout << "Average score: " << stu[max_index].aver_score << endl;
    system("pause");
    return 0;
}

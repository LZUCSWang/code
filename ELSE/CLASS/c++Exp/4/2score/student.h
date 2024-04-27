<<<<<<< HEAD
/*
 * @Author: 王贤义
 * @FilePath: \code\C+++C\c++\4\2score\student.h
 * @Description: 头文件，包括Student结构体定义和各功能函数声明
 */

// student.h

#ifndef STUDENT_H
#define STUDENT_H

// typedef struct Student
// {
//     int num;
//     char name[20];
//     char classname[20];
//     float score[3];
//     float aver_score;
// } Student;
#include <string>
typedef struct Student
{
    int num;
    std::string name;
    std::string classname;
=======
// student.h
#ifndef STUDENT_H
#define STUDENT_H

typedef struct Student
{
    int num;
    char name[20];
    char classname[20];
>>>>>>> 4b973315162d27f01fa06261e78d6fb1c889420e
    float score[3];
    float aver_score;
} Student;

void input_students(Student stu[], int number);
void calculate_average_score(Student stu[], int number);
int find_highest_average_score(Student stu[], int number);

#endif
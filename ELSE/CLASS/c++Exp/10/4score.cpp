#include<bits/stdc++.h>

using namespace std;

// 学生基本信息结构体
struct StudentInfo {
    string studentID;
    string name;
    string gender;
    string dormitory;
    string phoneNumber;
};

// 学生成绩结构体
struct StudentScore {
    string studentID;
    string courseCode;
    string courseName;
    int credit;
    int regularScore;
    int labScore;
    int examScore;
    double compositeScore;
};

// 函数声明
void loadData(vector<StudentInfo>& students, vector<StudentScore>& scores);
void saveData(const vector<StudentInfo>& students, const vector<StudentScore>& scores);
void inputData(vector<StudentScore>& scores);
void printStudentInfo(const StudentInfo& student);
void printScoreInfo(const StudentScore& score);
void searchStudentInfo(const vector<StudentInfo>& students);
void searchScoreInfo(const vector<StudentScore>& scores);
void deleteStudent(vector<StudentInfo>& students, vector<StudentScore>& scores);
bool compareByCompositeScore(const StudentScore& score1, const StudentScore& score2);
bool compareByCredit(const StudentScore& score1, const StudentScore& score2);
void sortScores(vector<StudentScore>& scores);

int main() {
    vector<StudentInfo> students;
    vector<StudentScore> scores;

    loadData(students, scores);

    int choice;
    do {
        cout << "====== 学籍管理系统 ======" << endl;
        cout << "1. 数据录入功能" << endl;
        cout << "2. 学生基本情况查询" << endl;
        cout << "3. 成绩查询" << endl;
        cout << "4. 删除功能" << endl;
        cout << "5. 排序功能" << endl;
        cout << "0. 退出" << endl;
        cout << "请输入选项：";
        cin >> choice;

        switch (choice) {
            case 1:
                inputData(scores);
                saveData(students, scores);
                break;
            case 2:
                searchStudentInfo(students);
                break;
            case 3:
                searchScoreInfo(scores);
                break;
            case 4:
                deleteStudent(students, scores);
                saveData(students, scores);
                break;
            case 5:
                sortScores(scores);
                break;
            case 0:
                saveData(students, scores);
                cout << "已退出学籍管理系统。" << endl;
                break;
            default:
                cout << "无效的选项，请重新输入。" << endl;
                break;
        }

        cout << endl;
    } while (choice != 0);

    return 0;
}

// 加载数据
void loadData(vector<StudentInfo>& students, vector<StudentScore>& scores) {
    ifstream studentFile("A.txt");
    ifstream scoreFile("B.txt");

    if (!studentFile.is_open() || !scoreFile.is_open()) {
        cout << "无法打开文件。" << endl;
        return;
    }

    // 加载学生基本信息
    while (!studentFile.eof()) {
        StudentInfo student;
        studentFile >> student.studentID >> student.name >> student.gender >> student.dormitory >> student.phoneNumber;
        students.push_back(student);
    }

    // 加载学生成绩信息
    while (!scoreFile.eof()) {
        StudentScore score;
        scoreFile >> score.studentID >> score.courseCode >> score.courseName >> score.credit >> score.regularScore >> score.labScore >> score.examScore;
        
        if (score.labScore == -1) {
            score.compositeScore = score.regularScore * 0.3 + score.examScore * 0.7;
        } else {
            score.compositeScore = score.regularScore * 0.15 + score.labScore * 0.15 + score.examScore * 0.7;
        }

        scores.push_back(score);
    }

    studentFile.close();
    scoreFile.close();
}

// 保存数据
void saveData(const vector<StudentInfo>& students, const vector<StudentScore>& scores) {
    ofstream studentFile("A.txt");
    ofstream scoreFile("B.txt");

    if (!studentFile.is_open() || !scoreFile.is_open()) {
        cout << "无法保存数据到文件。" << endl;
        return;
    }

    // 保存学生基本信息
    for (const auto& student : students) {
        studentFile << student.studentID << " " << student.name << " " << student.gender << " " << student.dormitory << " " << student.phoneNumber << endl;
    }

    // 保存学生成绩信息
    for (const auto& score : scores) {
        scoreFile << score.studentID << " " << score.courseCode << " " << score.courseName << " " << score.credit << " " << score.regularScore << " " << score.labScore << " " << score.examScore << endl;
    }

    studentFile.close();
    scoreFile.close();
}

// 录入数据
void inputData(vector<StudentScore>& scores) {
    string studentID, courseCode, courseName;
    int credit, regularScore, labScore, examScore;

    cout << "请输入学生学号：";
    cin >> studentID;

    // 检查学号是否存在
    auto it = find_if(scores.begin(), scores.end(), [&studentID](const StudentScore& score) {
        return score.studentID == studentID;
    });

    if (it != scores.end()) {
        cout << "该学生已存在，请输入其他学号。" << endl;
        return;
    }

    cout << "请输入课程编号：";
    cin >> courseCode;
    cout << "请输入课程名称：";
    cin >> courseName;
    cout << "请输入学分：";
    cin >> credit;
    cout << "请输入平时成绩：";
    cin >> regularScore;
    cout << "请输入实验成绩（无实验请输-1）：";
    cin >> labScore;
    cout << "请输入卷面成绩：";
    cin >> examScore;

    StudentScore score;
    score.studentID = studentID;
    score.courseCode = courseCode;
    score.courseName = courseName;
    score.credit = credit;
    score.regularScore = regularScore;
    score.labScore = labScore;
    score.examScore = examScore;

    if (labScore == -1) {
        score.compositeScore = regularScore * 0.3 + examScore * 0.7;
    } else {
        score.compositeScore = regularScore * 0.15 + labScore * 0.15 + examScore * 0.7;
    }

    scores.push_back(score);
}

// 打印学生基本信息
void printStudentInfo(const StudentInfo& student) {
    cout << "学号：" << student.studentID << " 姓名：" << student.name << " 性别：" << student.gender << " 宿舍号码：" << student.dormitory << " 电话号码：" << student.phoneNumber << endl;
}

// 打印学生成绩信息
void printScoreInfo(const StudentScore& score) {
    cout << "学号：" << score.studentID << " 课程编号：" << score.courseCode << " 课程名称：" << score.courseName << " 综合成绩：" << score.compositeScore << " 实得学分：" << score.credit << endl;
}

// 学生基本情况查询
void searchStudentInfo(const vector<StudentInfo>& students) {
    int choice;
    cout << "请选择查询方式：" << endl;
    cout << "1. 根据学号查询" << endl;
    cout << "2. 根据姓名查询" << endl;
    cin >> choice;

    string key;
    if (choice == 1) {
        cout << "请输入学号：";
        cin >> key;
    } else if (choice == 2) {
        cout << "请输入姓名：";
        cin >> key;
    } else {
        cout << "无效的选项。" << endl;
        return;
    }

    bool found = false;
    for (const auto& student : students) {
        if (choice == 1 && student.studentID == key) {
            printStudentInfo(student);
            found = true;
            break;
        } else if (choice == 2 && student.name == key) {
            printStudentInfo(student);
            found = true;
        }
    }

    if (!found) {
        cout << "未找到相关学生信息。" << endl;
    }
}

// 成绩查询
void searchScoreInfo(const vector<StudentScore>& scores) {
    string studentID;
    cout << "请输入学号：";
    cin >> studentID;

    bool found = false;
    double totalCredits = 0.0;
    double totalCompositeScore = 0.0;

    for (const auto& score : scores) {
        if (score.studentID == studentID) {
            printScoreInfo(score);
            totalCredits += score.credit;
            totalCompositeScore += score.compositeScore;
            found = true;
        }
    }

    if (!found) {
        cout << "未找到该学生的成绩信息。" << endl;
    } else {
        cout << "共修：" << scores.size() << " 科，实得总学分为：" << totalCredits << endl;
    }
}

// 删除学生信息
void deleteStudent(vector<StudentInfo>& students, vector<StudentScore>& scores) {
    string studentID;
    cout << "请输入学号：";
    cin >> studentID;

    // 删除学生基本信息
    students.erase(remove_if(students.begin(), students.end(), [&studentID](const StudentInfo& student) {
        return student.studentID == studentID;
    }), students.end());

    // 删除学生成绩信息
    scores.erase(remove_if(scores.begin(), scores.end(), [&studentID](const StudentScore& score) {
        return score.studentID == studentID;
    }), scores.end());
}

// 按综合成绩升序排序
bool compareByCompositeScore(const StudentScore& score1, const StudentScore& score2) {
    return score1.compositeScore < score2.compositeScore;
}

// 按实得学分升序排序
bool compareByCredit(const StudentScore& score1, const StudentScore& score2) {
    return score1.credit < score2.credit;
}

// 排序功能
void sortScores(vector<StudentScore>& scores) {
    int choice;
    cout << "请选择排序方式：" << endl;
    cout << "1. 按综合成绩升序排序" << endl;
    cout << "2. 按实得学分升序排序" << endl;
    cin >> choice;

    if (choice == 1) {
        sort(scores.begin(), scores.end(), compareByCompositeScore);
    } else if (choice == 2) {
        sort(scores.begin(), scores.end(), compareByCredit);
    } else {
        cout << "无效的选项。" << endl;
        return;
    }

    cout << "排序完成。" << endl;
}

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;

// 学生信息结构体
struct Student
{
    string name;
    string id;
    int chinese;
    int math;
    int english;
};

// 读取学生信息文件
vector<Student> read_student_file(string filename, vector<Student> &students)
{

    fstream infile(filename, ios::in);
    if (!infile.is_open())
    {
        cerr << "Error: can't open file " << filename << endl;
        return students;
    }

    string line;
    while (getline(infile, line))
    {
        istringstream iss(line);
        string name, id;
        string dummy;
        int chinese, math, english;
        if (!(iss >> name >> dummy >> id >> dummy >> chinese >> dummy >> math >> dummy >> english))
        {
            cerr << "Error: invalid student file format" << endl;
            return students;
        }
        students.push_back({name, id, chinese, math, english});
    }

    infile.close();
    return students;
}

// 写入学生信息文件
void write_student_file(string filename, vector<Student> &students)
{
    ofstream outfile(filename);
    if (!outfile.is_open())
    {
        cerr << "Error: can't open file " << filename << endl;
        return;
    }

    for (const auto &s : students)
    {
        outfile << s.name << " , " << s.id << " , " << s.chinese << " , " << s.math << " , " << s.english << endl;
    }

    outfile.close();
}

// 根据姓名查找学生
vector<Student> find_student_by_name(vector<Student> &students, string name)
{
    vector<Student> result;
    for (const auto &s : students)
    {
        if (s.name == name)
        {
            result.push_back(s);
        }
    }
    return result;
}
// 根据学号查找学生
Student *find_student_by_id(vector<Student> &students, string id)
{
    for (const auto &s : students)
    {
        if (s.id == id)
        {
            return (Student *)&s;
        }
    }
    return NULL;
}
// 添加学生信息
void add_student(vector<Student> &students)
{
    string name, id;
    int chinese, math, english;
    cout << "Enter student name: ";
    cin >> name;
    cout << "Enter student id: ";
    cin >> id;
    cout << "Enter Chinese score: ";
    cin >> chinese;
    cout << "Enter Math score: ";
    cin >> math;
    cout << "Enter English score: ";
    cin >> english;
    students.push_back({name, id, chinese, math, english});
    cout << "Student " << name << " added." << endl;
}
// 删除学生信息
void delete_student(vector<Student> &students)
{
    string id;
    cout << "Enter student id: ";
    cin >> id;
    std::vector<Student>::iterator it = remove_if(students.begin(), students.end(), [id](const Student &s)
                                                  { return s.id == id; });
    if (it != students.end())
    {
        students.erase(it, students.end());
        cout << "Student " << id << " deleted." << endl;
    }
    else
    {
        cout << "Error: student " << id << " not found." << endl;
    }
}

// 修改学生信息
void modify_student(vector<Student> &students)
{
    string id;
    cout << "Enter student id: ";
    cin >> id;
    auto s = find_student_by_id(students, id);
    if (s == nullptr)
    {
        cout << "Error: student " << id << " not found." << endl;
        return;
    }
    // 修改学生信息
    int chinese, math, english;
    cout << "Enter Chinese score [" << s->chinese << "]: ";
    cin >> chinese;
    cout << "Enter Math score [" << s->math << "]: ";
    cin >> math;
    cout << "Enter English score [" << s->english << "]: ";
    cin >> english;
    if (chinese != -1)
    {
        s->chinese = chinese;
    }
    if (math != -1)
    {
        s->math = math;
    }
    if (english != -1)
    {
        s->english = english;
    }
    cout << "Student " << s->name << " modified." << endl;
}
void score_statistics(vector<Student> &students)
{
    string course;
    int low, high;
    cout << "Enter course name: ";
    cin >> course;
    cout << "Enter score range [low high]: ";
    cin >> low >> high;
    int count = 0;
    for (const Student &s : students)
    {
        int score;
        if (course == "Chinese")
        {
            score = s.chinese;
        }
        else if (course == "Math")
        {
            score = s.math;
        }
        else if (course == "English")
        {
            score = s.english;
        }
        else
        {
            cout << "Error: invalid course name." << endl;
            return;
        }

        if (score >= low && score <= high)
        {
            count++;
        }
    }

    cout << "There are " << count << " students with " << course << " scores between " << low << " and " << high << "." << endl;
}
void sort_students(vector<Student> &students)
{
    string course;
    int order;
    cout << "Enter course name: ";
    cin >> course;
    cout << "Enter sort order (0 for ascending, 1 for descending): ";
    cin >> order; // 按成绩排序
    if (course == "Chinese")
    {
        if (order == 0)
        {
            sort(students.begin(), students.end(), [](const Student &a, const Student &b)
                 { return a.chinese < b.chinese; });
        }
        else
        {
            sort(students.begin(), students.end(), [](const Student &a, const Student &b)
                 { return a.chinese > b.chinese; });
        }
    }
    else if (course == "Math")
    {
        if (order == 0)
        {
            sort(students.begin(), students.end(), [](const Student &a, const Student &b)
                 { return a.math < b.math; });
        }
        else
        {
            sort(students.begin(), students.end(), [](const Student &a, const Student &b)
                 { return a.math > b.math; });
        }
    }
    else if (course == "English")
    {
        if (order == 0)
        {
            sort(students.begin(), students.end(), [](const Student &a, const Student &b)
                 { return a.english < b.english; });
        }
        else
        {
            sort(students.begin(), students.end(), [](const Student &a, const Student &b)
                 { return a.english > b.english; });
        }
    }
    else
    {
        cout << "Error: invalid course name." << endl;
        return;
    }

    // 输出排序结果
    cout << "Name\tID\tChinese\tMath\tEnglish" << endl;
    for (const Student &s : students)
    {
        // 输出学生信息
        cout << s.name << "\t" << s.id << "\t" << s.chinese << "\t" << s.math << "\t" << s.english << endl;
    }
}
// 计算平均分
void average_score(vector<Student> &students)
{
    string course;
    cout << "Enter course name: ";
    cin >> course;
    double sum = 0;
    for (const Student &s : students)
    {
        int score;
        if (course == "Chinese")
        {
            score = s.chinese;
        }
        else if (course == "Math")
        {
            score = s.math;
        }
        else if (course == "English")
        {
            score = s.english;
        }
        else
        {
            cout << "Error: invalid course name." << endl;
            return;
        }
        sum += score;
    }
    cout << "The average score of " << course << " is " << sum / students.size() << "." << endl;
}
void search_students(vector<Student> &students)
{
    int choice = 0;
    cout << "1. Search by name" << endl;
    cout << "2. Search by id" << endl;
    cout << "Enter your choice [1-2]: ";
    cin >> choice;
    if (choice == 1)
    {
        string name;
        cout << "Enter student name: ";
        cin >> name;
        vector<Student> result = find_student_by_name(students, name);
        if (result.empty())
        {
            cout << "Error: student " << name << " not found." << endl;
            return;
        }
        // 输出学生信息
        cout << "Name\tID\tChinese\tMath\tEnglish" << endl;
        for (const auto &s : result)
        {
            cout << s.name << "\t" << s.id << "\t" << s.chinese << "\t" << s.math << "\t" << s.english << endl;
        }
    }
    else if (choice == 2)
    {
        string id;
        cout << "Enter student id: ";
        cin >> id;
        Student *s = find_student_by_id(students, id);
        if (s == NULL)
        {
            cout << "Error: student " << id << " not found." << endl;
            return;
        }
        // 输出学生信息
        cout << "Name\tID\tChinese\tMath\tEnglish" << endl;
        cout << s->name << "\t" << s->id << "\t" << s->chinese << "\t" << s->math << "\t" << s->english << endl;
    }
    else
    {
        cout << "Error: invalid choice." << endl;
    }
}
void show_all_students(vector<Student> &students)
{
    // 输出学生信息
    cout << "Name\tID\tChinese\tMath\tEnglish" << endl;
    for (const auto &s : students)
    {
        cout << s.name << "\t" << s.id << "\t" << s.chinese << "\t" << s.math << "\t" << s.english << endl;
    }
}
int main()
{
    // 从文件中读取学生信息
    vector<Student> students;
    read_student_file("students.txt", students); // 显示菜单并处理用户输入
    while (true)
    {
        int choice;
        cout << endl
             << "1. Add student" << endl
             << "2. Delete student" << endl
             << "3. Modify student information" << endl
             << "4. Search students" << endl
             << "5. Score statistics" << endl
             << "6. Sort students" << endl
             << "7. Show all students" << endl
             << "8. Count average score" << endl
             << "9. Exit" << endl
             << "Enter your choice [1-8]: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            add_student(students);
            break;
        case 2:
            delete_student(students);
            break;
        case 3:
            modify_student(students);
            break;
        case 4:
            search_students(students);
            break;
        case 5:
            score_statistics(students);
            break;
        case 6:
            sort_students(students);
            break;
        case 7:
            show_all_students(students);
            break;
        case 8:
            average_score(students);
            break;
        case 9:
            // 保存学生信息到文件并退出程序
            write_student_file("students.txt", students);
            return 0;
        default:
            cout << "Error: invalid choice." << endl;
            break;
        }
    }
}
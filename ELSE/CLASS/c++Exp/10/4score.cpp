#include<bits/stdc++.h>

using namespace std;

// ѧ��������Ϣ�ṹ��
struct StudentInfo {
    string studentID;
    string name;
    string gender;
    string dormitory;
    string phoneNumber;
};

// ѧ���ɼ��ṹ��
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

// ��������
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
        cout << "====== ѧ������ϵͳ ======" << endl;
        cout << "1. ����¼�빦��" << endl;
        cout << "2. ѧ�����������ѯ" << endl;
        cout << "3. �ɼ���ѯ" << endl;
        cout << "4. ɾ������" << endl;
        cout << "5. ������" << endl;
        cout << "0. �˳�" << endl;
        cout << "������ѡ�";
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
                cout << "���˳�ѧ������ϵͳ��" << endl;
                break;
            default:
                cout << "��Ч��ѡ����������롣" << endl;
                break;
        }

        cout << endl;
    } while (choice != 0);

    return 0;
}

// ��������
void loadData(vector<StudentInfo>& students, vector<StudentScore>& scores) {
    ifstream studentFile("A.txt");
    ifstream scoreFile("B.txt");

    if (!studentFile.is_open() || !scoreFile.is_open()) {
        cout << "�޷����ļ���" << endl;
        return;
    }

    // ����ѧ��������Ϣ
    while (!studentFile.eof()) {
        StudentInfo student;
        studentFile >> student.studentID >> student.name >> student.gender >> student.dormitory >> student.phoneNumber;
        students.push_back(student);
    }

    // ����ѧ���ɼ���Ϣ
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

// ��������
void saveData(const vector<StudentInfo>& students, const vector<StudentScore>& scores) {
    ofstream studentFile("A.txt");
    ofstream scoreFile("B.txt");

    if (!studentFile.is_open() || !scoreFile.is_open()) {
        cout << "�޷��������ݵ��ļ���" << endl;
        return;
    }

    // ����ѧ��������Ϣ
    for (const auto& student : students) {
        studentFile << student.studentID << " " << student.name << " " << student.gender << " " << student.dormitory << " " << student.phoneNumber << endl;
    }

    // ����ѧ���ɼ���Ϣ
    for (const auto& score : scores) {
        scoreFile << score.studentID << " " << score.courseCode << " " << score.courseName << " " << score.credit << " " << score.regularScore << " " << score.labScore << " " << score.examScore << endl;
    }

    studentFile.close();
    scoreFile.close();
}

// ¼������
void inputData(vector<StudentScore>& scores) {
    string studentID, courseCode, courseName;
    int credit, regularScore, labScore, examScore;

    cout << "������ѧ��ѧ�ţ�";
    cin >> studentID;

    // ���ѧ���Ƿ����
    auto it = find_if(scores.begin(), scores.end(), [&studentID](const StudentScore& score) {
        return score.studentID == studentID;
    });

    if (it != scores.end()) {
        cout << "��ѧ���Ѵ��ڣ�����������ѧ�š�" << endl;
        return;
    }

    cout << "������γ̱�ţ�";
    cin >> courseCode;
    cout << "������γ����ƣ�";
    cin >> courseName;
    cout << "������ѧ�֣�";
    cin >> credit;
    cout << "������ƽʱ�ɼ���";
    cin >> regularScore;
    cout << "������ʵ��ɼ�����ʵ������-1����";
    cin >> labScore;
    cout << "���������ɼ���";
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

// ��ӡѧ��������Ϣ
void printStudentInfo(const StudentInfo& student) {
    cout << "ѧ�ţ�" << student.studentID << " ������" << student.name << " �Ա�" << student.gender << " ������룺" << student.dormitory << " �绰���룺" << student.phoneNumber << endl;
}

// ��ӡѧ���ɼ���Ϣ
void printScoreInfo(const StudentScore& score) {
    cout << "ѧ�ţ�" << score.studentID << " �γ̱�ţ�" << score.courseCode << " �γ����ƣ�" << score.courseName << " �ۺϳɼ���" << score.compositeScore << " ʵ��ѧ�֣�" << score.credit << endl;
}

// ѧ�����������ѯ
void searchStudentInfo(const vector<StudentInfo>& students) {
    int choice;
    cout << "��ѡ���ѯ��ʽ��" << endl;
    cout << "1. ����ѧ�Ų�ѯ" << endl;
    cout << "2. ����������ѯ" << endl;
    cin >> choice;

    string key;
    if (choice == 1) {
        cout << "������ѧ�ţ�";
        cin >> key;
    } else if (choice == 2) {
        cout << "������������";
        cin >> key;
    } else {
        cout << "��Ч��ѡ�" << endl;
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
        cout << "δ�ҵ����ѧ����Ϣ��" << endl;
    }
}

// �ɼ���ѯ
void searchScoreInfo(const vector<StudentScore>& scores) {
    string studentID;
    cout << "������ѧ�ţ�";
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
        cout << "δ�ҵ���ѧ���ĳɼ���Ϣ��" << endl;
    } else {
        cout << "���ޣ�" << scores.size() << " �ƣ�ʵ����ѧ��Ϊ��" << totalCredits << endl;
    }
}

// ɾ��ѧ����Ϣ
void deleteStudent(vector<StudentInfo>& students, vector<StudentScore>& scores) {
    string studentID;
    cout << "������ѧ�ţ�";
    cin >> studentID;

    // ɾ��ѧ��������Ϣ
    students.erase(remove_if(students.begin(), students.end(), [&studentID](const StudentInfo& student) {
        return student.studentID == studentID;
    }), students.end());

    // ɾ��ѧ���ɼ���Ϣ
    scores.erase(remove_if(scores.begin(), scores.end(), [&studentID](const StudentScore& score) {
        return score.studentID == studentID;
    }), scores.end());
}

// ���ۺϳɼ���������
bool compareByCompositeScore(const StudentScore& score1, const StudentScore& score2) {
    return score1.compositeScore < score2.compositeScore;
}

// ��ʵ��ѧ����������
bool compareByCredit(const StudentScore& score1, const StudentScore& score2) {
    return score1.credit < score2.credit;
}

// ������
void sortScores(vector<StudentScore>& scores) {
    int choice;
    cout << "��ѡ������ʽ��" << endl;
    cout << "1. ���ۺϳɼ���������" << endl;
    cout << "2. ��ʵ��ѧ����������" << endl;
    cin >> choice;

    if (choice == 1) {
        sort(scores.begin(), scores.end(), compareByCompositeScore);
    } else if (choice == 2) {
        sort(scores.begin(), scores.end(), compareByCredit);
    } else {
        cout << "��Ч��ѡ�" << endl;
        return;
    }

    cout << "������ɡ�" << endl;
}

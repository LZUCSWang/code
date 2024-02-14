#include<bits/stdc++.h>
using namespace std;

class student {
public:
    char name[10];
    int deg1, deg2, deg3;
    student() {
        deg1 = deg2 = deg3 = 0;
    }
    student(char na[], int d1, int d2, int d3) {
        strcpy(name, na);
        deg1 = d1;
        deg2 = d2;
        deg3 = d3;
    }
    friend student operator+(student s1, student s2) {
        student s;
        strcpy(s.name, "Total");
        s.deg1 = s1.deg1 + s2.deg1;
        s.deg2 = s1.deg2 + s2.deg2;
        s.deg3 = s1.deg3 + s2.deg3;
        return s;
    }
    friend void avg(student& s, int n) {
        cout << s.name << "\t" << s.deg1 / n << "\t" << s.deg2 / n << "\t" << s.deg3 / n << endl;
    }
};

int main() {
    // student s[5] = { {"Tom", 80, 90, 70}, {"Jerry", 85, 75, 90}, {"Mickey", 90, 80, 85}, {"Minnie", 95, 85, 80}, {"Donald", 75, 90, 85} };
    student s[5];
    cout<<"Please input the name, deg1, deg2, deg3 of 5 students:"<<endl;
    for(int i=0;i<5;i++){
        cin>>s[i].name>>s[i].deg1>>s[i].deg2>>s[i].deg3;
    }
    student total;
    for (int i = 0; i < 5; i++) {
        cout << s[i].name << "\t" << s[i].deg1 << "\t" << s[i].deg2 << "\t" << s[i].deg3 << endl;
        total = total + s[i];
    }
    avg(total, 5);
    cout << "Average\t";
    avg(total, 5);
    return 0;
}

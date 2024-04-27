#include<bits/stdc++.h>
using namespace std;
int main(){
    set<int> s;
    s.insert(123);
    s.insert(456);
    s.insert(789);
    s.find(123);
    set<int>::iterator t;
    t=s.find(456);
    if (t!=s.end())
    cout<<"456"<<endl;
    if ((t=s.find(789))!=s.end())cout<<"789"<<endl;
}
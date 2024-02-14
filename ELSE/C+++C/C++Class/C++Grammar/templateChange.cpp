#include <bits/stdc++.h>
using namespace std;

int myAdd01(int a,int b){
    return a+b;
}
template <typename T>
T myAdd02(T a,T b){
    return a+b;
}

void test01(){
    int a=10,b=20;
    char c='c';
    cout<<myAdd01(a,b)<<endl;
    cout<<myAdd02(a,b)<<endl;
    // cout<<myAdd02(a,c)<<endl;//error 隐式不会自动转换会错
    cout<<myAdd02<int>(a,c)<<endl;//ok 显示转换不会错
}

void myPrint(int a,int b){
    cout<<"普通函数"<<endl;
}
template <typename T>
void myPrint(T a,T b){
    cout<<"模板函数"<<endl;
}
template <typename T>
void myPrint(T a,T b,T c){
    cout<<"模板函数重载"<<endl;
}
void test02(){
    int a=10,b=20,c=30;
    myPrint(a,b);
    myPrint(a,b,c);
    myPrint<>(a,b);
}

int main(){
    test01();
    test02();
}
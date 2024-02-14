#include<iostream>
#include<string>
using namespace std;
const int MAX_SIZE=10;
string principle[MAX_SIZE],temp[MAX_SIZE];
 
int main()
{
    int i=0,count=0;
    void removeDirect(int i, int count2);
    void removeIndirect(int i,int j);
    string DFS(string start,string *principle,int count,int temp);
    cout<<"输入规则的个数："<<endl;
    cin>>count;
    cout<<"请输入"<<count<<"个规则："<<endl;
    for(i=0;i<count;i++)
        cin>>principle[i];
    cout<<"原文法为："<<endl;
    int loc = 0;
    for(i=0;cout<<principle[i]<<endl,i<3;i++);
    cout<<endl;
    int start=0, end=0;
    int count2=0;
    for(i=0;i<count;i++)
    {
        for(int j=0;j<i;j++)
        {
            removeIndirect(i,j);//间接左递归变直接左递归
        }
        removeDirect(i, count2);//消除直接左递归
    }
    //cout<<"消除后的式子为："<<endl;
    //for(i=0;cout<<principle[i]<<endl,i<count-1;i++);
    //for(i=0;cout<<temp[i]<<endl,i<count2-1;i++);
    cout<<"消除后的式子为："<<endl;
    string sss=DFS(principle[2],principle,count,0);
    for(i=0;i<count;i++){
        if(sss.find(principle[i][0])<100)
            cout<<principle[i]<<endl;
    }
    for(i=0;cout<<temp[i]<<endl,i<count2-1;i++);
    return 0;
}
 
string DFS(string start,string *principle,int count,int temp){
    string x = "";
    temp++;
    for(int i=0;i<start.length();i++){
        if(start[i]>='A'&&start[i]<='Z'&&temp<count){
            x+=start[i];
            for(int j = 0;j<count-1;j++){
                if(principle[j][0]==start[i]){
                    x+=DFS(principle[j],principle,count,temp);
                }
            }
        }
    }
    return x;
}
 
 
void removeDirect(int i, int count2){
    //消除直接左递归，即将形如A->Ab|c 的转化为 A->cA'和A'->bA'|~
    string p1="",p2="";
    size_t flag1=3,flag2=0;
    char ch=principle[i][0];
    bool last=false; //判断是否结束
    while(flag1!=string::npos) //寻找文法中的|符号，如果h找不到则退出
    {
        flag2=principle[i].find_first_of("|",flag1+1); //在文法中找到第flag+1个|
        if(flag2==string::npos)flag2=principle[i].length(); //只有一个|
        if(principle[i][flag1]==ch)
        {
            last=true;
            p1+=principle[i].substr(flag1+1,flag2-flag1-1)+ch+"\'|";//加上‘
        }
        else
        {
            p2+=principle[i].substr(flag1,flag2-flag1)+ch+"\'|";//加上’
        }
        flag1=principle[i].find_first_not_of("|",flag2+1);
    }
    p2[p2.length()-1]='\0';
    if(last)  //结束时加上空~
    {
        temp[count2]=ch+("\'->"+p1+"~");
        count2++;
        principle[i].replace(3,principle[i].length()-3,p2);
    }
}
 
 
void removeIndirect(int i,int j){
    //间接左递归变直接左递归
    int start=2;
    char aj=principle[j][0];
    //修改产生式
    bool rgt=false;
    int count1=0;
    string tt[MAX_SIZE];
    size_t s=0,e=0;
    do
    {
        start++;
        if(principle[i][start]==aj)//如果满足Ai->Aj*
        {
            size_t es=principle[i].find_first_of("|",start+1);
            if(es==string::npos)
                es=principle[i].length();
            string te=principle[i].substr(start+1,es-start-1);
            if(!rgt)
            {
                s=principle[j].find_first_not_of("|",3);
                while(s!=string::npos)
                {
                    e=principle[j].find_first_of("|",s+1);
                    if(e==string::npos)
                        e=principle[j].length();
                    tt[count1]=principle[j].substr(s,e-s);
                    count1++;
                    s=principle[j].find_first_not_of("|",e+1);
                }
                rgt=true;
            }
            int k=0;
            string ttl="\0";
            for(;k<count1-1;k++)
                ttl+=tt[k]+te+"|";
            ttl+=tt[k]+te;
            principle[i].replace(start,es-start,ttl);
        }
        start = principle[i].find_first_of("|",start+1);
    }while(start!=string::npos);
}
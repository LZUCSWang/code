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
    cout<<"�������ĸ�����"<<endl;
    cin>>count;
    cout<<"������"<<count<<"������"<<endl;
    for(i=0;i<count;i++)
        cin>>principle[i];
    cout<<"ԭ�ķ�Ϊ��"<<endl;
    int loc = 0;
    for(i=0;cout<<principle[i]<<endl,i<3;i++);
    cout<<endl;
    int start=0, end=0;
    int count2=0;
    for(i=0;i<count;i++)
    {
        for(int j=0;j<i;j++)
        {
            removeIndirect(i,j);//�����ݹ��ֱ����ݹ�
        }
        removeDirect(i, count2);//����ֱ����ݹ�
    }
    //cout<<"�������ʽ��Ϊ��"<<endl;
    //for(i=0;cout<<principle[i]<<endl,i<count-1;i++);
    //for(i=0;cout<<temp[i]<<endl,i<count2-1;i++);
    cout<<"�������ʽ��Ϊ��"<<endl;
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
    //����ֱ����ݹ飬��������A->Ab|c ��ת��Ϊ A->cA'��A'->bA'|~
    string p1="",p2="";
    size_t flag1=3,flag2=0;
    char ch=principle[i][0];
    bool last=false; //�ж��Ƿ����
    while(flag1!=string::npos) //Ѱ���ķ��е�|���ţ����h�Ҳ������˳�
    {
        flag2=principle[i].find_first_of("|",flag1+1); //���ķ����ҵ���flag+1��|
        if(flag2==string::npos)flag2=principle[i].length(); //ֻ��һ��|
        if(principle[i][flag1]==ch)
        {
            last=true;
            p1+=principle[i].substr(flag1+1,flag2-flag1-1)+ch+"\'|";//���ϡ�
        }
        else
        {
            p2+=principle[i].substr(flag1,flag2-flag1)+ch+"\'|";//���ϡ�
        }
        flag1=principle[i].find_first_not_of("|",flag2+1);
    }
    p2[p2.length()-1]='\0';
    if(last)  //����ʱ���Ͽ�~
    {
        temp[count2]=ch+("\'->"+p1+"~");
        count2++;
        principle[i].replace(3,principle[i].length()-3,p2);
    }
}
 
 
void removeIndirect(int i,int j){
    //�����ݹ��ֱ����ݹ�
    int start=2;
    char aj=principle[j][0];
    //�޸Ĳ���ʽ
    bool rgt=false;
    int count1=0;
    string tt[MAX_SIZE];
    size_t s=0,e=0;
    do
    {
        start++;
        if(principle[i][start]==aj)//�������Ai->Aj*
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
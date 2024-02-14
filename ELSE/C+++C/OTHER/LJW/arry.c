#include<stdio.h>
void firsttosecond(int *,int,int *,int,int *,int *);
int main(){
    int n1,n2,flag=0,k=0;
    scanf("%d",&n1);
    int arry1[n1];
    for(int i=0;i<n1;i++){
        scanf("%d",&arry1[i]);
    }
    scanf("%d",&n2);
    int arry2[n2];
    int cnt[(n1>n2)?n1:n2];
    for(int i=0;i<n2;i++){
        scanf("%d",&arry2[i]);
    }
    firsttosecond(arry1,n1,arry2,n2,cnt,&k);
    firsttosecond(arry2,n2,arry1,n1,cnt,&k);
    
    for(int i=0;i<k;i++)printf("%d ",cnt[i]);
}
void firsttosecond(int *f,int lf,int *s,int ls,int *cnt,int *k){
    int flag=0;
    for(int i=0;i<lf;i++){
        for(int j=0;j<ls;j++){
            if(f[i]==s[j]){
                flag=1;
                break;
            }}
    if(flag==0){
        cnt[*k]=f[i];
        (*k)++;
    }
    flag=0;
}   
}
#include<stdio.h>
int main(){
    int n,flag=1;
    while(scanf("%d",&n)==1)
    for(long long int i=1;;i++){
        long long int target=i*n,target1=target;
        while(target>0){
            int p=target%10;
            if(p!=1&&p!=0){
                flag=0;
                break;
            }
            target/=10;
        }
        if(flag==1){
            printf("%lld\n",target1);
            break;
        }
        flag=1;
    }
}
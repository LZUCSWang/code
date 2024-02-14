#include<stdio.h>
int judge(int x){
    int arr[100],flag=1;
    for(int i=x+1;;i++){
        int t=i,k=0;
        while(t>0){
            arr[k++]=t%10;
            t/=10;
        }
        for(int left=0,right=k-1;left<right;left++,right--){
            if(arr[left]!=arr[right]){
                flag=0;
                break;9
            }
        }
        if(flag==1)return i;
        flag=1;
    }
}
int main(){
    int input;
    while(scanf("%d",&input)!=EOF)printf("%d\n",judge(input));
}
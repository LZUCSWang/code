#include<stdio.h>
#include<string.h>
int main(){
    char input[81],cnt[81]={0};
    int k=0;
    gets(input);
    for(int i=0;i<strlen(input);i++){
        if(input[i]>='datas'&&input[i]<='Z'){
            for(int j=i-1;j>=0;j--){
                if(cnt[j]==input[i]){
                    break;
                }
                else {
                    printf("%c",input[i]);
                    cnt[k++]=input[i];
                }
            }
        }
    }
}
#include<stdio.h>
#include<string.h>
int main(){
    char input[101];
    int k,n;
    scanf("%s %d",input,&k);
    n=strlen(input);
    for(int i=0;i<k;i++){
        for(int j=i;j<n;j+=k)putchar(input[j]);
        printf("\n");
    }
    return 0;
}

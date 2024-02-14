#include<stdio.h>
int main(){
    int cen=0,i=0,j=0,n,count=1;
    scanf("%d",&n);
    int cnt[n][n];
    while(cen<=(n-1)/2){
        i=0,j=0;
        for(i+=cen,j+=cen;j<n-cen;j++){
            if(count>(n*n))break;
            cnt[i][j]=count++;
        }
        for(i++,j--;i<n-cen;i++){
            if(count>(n*n))break;
            cnt[i][j]=count++;
        }
        for(i--,j--;j>=cen;j--){
            if(count>(n*n))break;
            cnt[i][j]=count++;
        }
        for(i--,j++;i>=cen+1;i--){
            if(count>(n*n))break;
            cnt[i][j]=count++;
        }
        cen++;
    }
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            printf("%10d  ",cnt[i][j]);
        }
        printf("\n");
    }
}
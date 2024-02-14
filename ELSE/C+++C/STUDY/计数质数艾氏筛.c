#include<stdio.h>
int countPrimes(int n){
    int record[n+1],sum=0;
    for(int i=0;i<n;i++){
        record[i]=0;
    }
    for(int i=2;i<n;i++){
        if(record[i]==0){
            sum++;
            for(int j=i*2;j<n;j+=i){
                record[j]=1;
            }
        }
    }
    return sum;
}
int countPrimes1(int n){
    if (n==0 || n==1){
        return 0;
    }
    int record[n];
    for (int i=0;i<n;i++){
        record[i] = 1;
    }
    int sum = 0;
    for (int i=2;i<n;i++){
        if (record[i]==1){
            sum++;
            for (int j=i*2;j<n;j=j+i){
                record[j] = 0;
            }
        }
    }
    for(int i=0;i<n;i++){
        if(record[i]==1)printf("%d*",i);
    }
    return sum;

}
int main(){
    int n;
    scanf("%d",&n);
    printf("%d",countPrimes(n));
}
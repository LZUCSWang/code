#include<stdio.h>
int distributeCandies(int* candyType, int candyTypeSize){
    int i,j,k=0,flag=0;
    for(i=0;i<candyTypeSize;i++){
        for(j=k-1;j>=0;j--){
            if(candyType[i]==candyType[j]){
                flag=1;
                break;
            }
        }
        if(flag==0){
            candyType[k]=candyType[i];
            k++;
        }
        flag=0;
    }
    return (k<candyTypeSize/2)?k:candyTypeSize/2;
}
int main(){
    int arr[]={1,1,2,3};
    printf("%d",distributeCandies(arr,4));
}
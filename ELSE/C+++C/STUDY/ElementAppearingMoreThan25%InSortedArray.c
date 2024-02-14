#include<stdio.h>
int findSpecialInteger(int* arr, int arrSize){
    int i;double count=1.0;
    for(i=0;i<arrSize;i++){
        if(arr[i]==arr[i+1]){
            count+=1.0;
        }
        else {
            count=1.0;
        }
        if(count>(arrSize*0.25)){
            break;
        }
    }
    return arr[i];
}
int main(){
    int arr[]={1,2,2,6,6,6,6,7,10};
    printf("%d",findSpecialInteger(arr,9));
}
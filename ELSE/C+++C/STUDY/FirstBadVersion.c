#include<stdio.h>
#include<stdbool.h>
// The API isBadVersion is defined for you.
bool isBadVersion(int version);

int firstBadVersion(int n) {
    int left=1,right=n;
    int mid=(left+right)/2;
    while(1){
        if(isBadVersion(mid)){
            if(!isBadVersion(mid+1))return mid+1;
            else{
                left=mid;
            }
        }
        else{
            if(isBadVersion(mid-1))return mid;
            else{
                right=mid;
            }
        }
        mid=(right+left)/2;
    }
}
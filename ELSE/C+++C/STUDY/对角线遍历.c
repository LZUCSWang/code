#include<stdio.h>
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* findDiagonalOrder(int** mat, int matSize, int* matColSize, int* returnSize){
    *returnSize=matSize*(*matColSize);
    int *cnt=(int *)malloc(sizeof(int)*(*returnSize));
    if(matSize==1){
        return mat[0];
    }
    else if(*matColSize==1){
        for(int i=0;i<*returnSize;i++){
            cnt[i]=mat[i][0];
            return cnt;
        }
    }
    int i=0,j=0,k=0,flag=0;
    while(k<*returnSize){
        cnt[k++]=mat[i][j];
        if(i==0||j==*matColSize-1){
            flag=1;
            if(j<*matColSize-1){
                j++;
            }
            else{
                i++;
            }
            cnt[k++]=mat[i][j];
        }
        else if(i==matSize-1||j==0){
            flag=0;
            if(i<matSize-1){
                i++;
            }
            else {
                j++;
            }
            cnt[k++]=mat[i][j];
        }
        if(flag==1){
            i++;j--;
        }
        else{
            i--;j++;
        }
    }
    return cnt;
}
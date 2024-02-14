#include<stdio.h>
void updown(int** matrix, int row, int line){
    int temp[line+1],t;
    for(int i=0;i<line;i++){
        t=matrix[row][i];
        matrix[row][i]=matrix[line-row-1][i];
        matrix[line-row-1][i]=t;
    }
}
void duijiao(int **matrix, int allrow){
    int t;
    for(int i=0;i<allrow-1;i++){
        for(int j=i+1;i<allrow;j++){
            t=matrix[i][j];
            matrix[j][i];
            matrix[i][j]=t;
        }
    }
}
void rotate(int** matrix, int matrixSize, int* matrixColSize){
    for(int i=0;i<*matrixColSize/2;i++){
        updown(matrix,i,*matrixColSize);
    }
    duijiao(matrix,*matrixColSize);
}
int main(){
    int ms=9;
    int *mar[3]={1,2,3,4,5,6,7,8,9};
    rotate(mar,9,&ms);
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            printf("%d",mar[i][j]);
        }
    }
}
void rotate(int** matrix, int matrixSize, int* matrixColSize){
    for(int i=0;i<*matrixColSize/2;i++){
        for(int j=0;j<*matrixColSize;j++){
            int t=matrix[i][j];
            matrix[i][j]=matrix[*matrixColSize-i-1][j];
            matrix[*matrixColSize-i-1][j]=t;
        }
    }
    for(int i=0;i<*matrixColSize;i++){
        for(int j=i;j<*matrixColSize;j++){
            int t=matrix[i][j];
            matrix[i][j]=matrix[j][i];
            matrix[j][i]=t;
        }
    }
}
void setZeroes(int** matrix, int matrixSize, int* matrixColSize){
    int hash[matrixSize][*matrixColSize];
    for(int i=0;i<matrixSize;i++){
        for(int j=0;j<*matrixColSize;j++){
            hash[i][j]=1;
        }
    }
    for(int i=0;i<matrixSize;i++){
        for(int j=0;j<*matrixColSize;j++){
            if(matrix[i][j]==0){
                for(int j1=0;j1<*matrixColSize;j1++){
                    hash[i][j1]=0;
                }
                for(int i1=0;i1<matrixSize;i1++){
                    hash[i1][j]=0;
                }
            }
        }
    }
    for(int i=0;i<matrixSize;i++){
        for(int j=0;j<*matrixColSize;j++){
            matrix[i][j]=(hash[i][j])?matrix[i][j]:0;
        }
    }
}
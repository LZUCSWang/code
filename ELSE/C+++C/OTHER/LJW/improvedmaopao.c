void swap(int *datas,int*b);
void maopao(int *input,int inputsize){
    int flag=1;
    for(int i=0;i<inputsize-1;i++){
        for(int j=0;j<inputsize-i-1;j++){
            if(input[j]>input[j+1]){
                flag=0;
                swap(&input[j],&input[j+1]);
            }
        }
        if(flag==1)break;
        flag=1;
    }
}
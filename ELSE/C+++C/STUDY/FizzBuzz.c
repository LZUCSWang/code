/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char ** fizzBuzz(int n, int* returnSize){
    //申请一个3行2列的整型数组  
    char (*datas)[9]=(char(*)[9])malloc(sizeof(char)*n*9);
    for(int i=1;i<=n;i++){
        if(i%3==0&&i%5==0)datas[i-1][0]="FizzBuzz";
        else if(i%3==0)*datas[i-1]="Fizz";
        else if(i%5==0)*datas[i-1]="Buzz";
        else sprintf(*datas[i-1],"%d",i);
    }
    return datas;
}
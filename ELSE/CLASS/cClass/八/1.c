#include<stdio.h>
void main(){
    FILE *fp;
    int datas[10]={1,2,3},i,n;
    fp=fopen("d1.dat","w");
    for(i=0;i<3;i++)fprintf(fp,"%d",datas[i]);
    fprintf(fp,"\n");
    fclose(fp);
    fp=fopen("d1.dat","r");
    fscanf(fp,"%d",&n);
    fclose(fp);
    printf("%d\n",n);
}
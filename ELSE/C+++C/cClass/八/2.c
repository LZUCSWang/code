#include<stdio.h>
int main(){
    FILE *fp;
    int i,datas[10]={1,2,3,0,0};
    fp=fopen("d2.dat","wb");
    fwrite(datas,sizeof(int),5,fp);
    fwrite(datas,sizeof(int),5,fp);
    fclose(fp);
    fp=fopen("d2.dat","rb");
    fread(datas,sizeof(int),10,fp);
    fclose(fp);
    for(i=0;i<10;i++)printf("%d",datas[i]);
}
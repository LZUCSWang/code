#include<stdio.h>
int tem(int temper){
    if(temper<=0)return 3;
    else if(temper<=15)return 2;
    else if(temper<=30)return 1;
    else return 0;
}
int main(){
    int sets,days,sum=0,sumdown=0;
    scanf("%d",&sets);getchar();
    for(int i=0;i<sets;i++){
        scanf("%d",&days);getchar();
        int evertem[days+1];
        evertem[0]=2;
        for(int j=1;j<=days;j++){
            scanf("%d",&evertem[j]);
            evertem[j]=tem(evertem[j]);
            if(evertem[j]>evertem[j-1])sum+=evertem[j]-evertem[j-1];
            else if(evertem[j]<evertem[j-1])sumdown+=evertem[j-1]-evertem[j];
        }
        printf("%d %d",sum,sumdown);
        sum=0;
        sumdown=0;
    }
}
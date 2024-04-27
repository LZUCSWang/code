#include<stdio.h>
#include<string.h>
#include<stdlib.h>
struct month
{
    char name[15];
    char ab[4];
    int days;
    int num;
};
struct month list[12] =
{
    {
        "January", "Jan", 31, 1
    },
    {
        "February", "Feb", 28, 2
    },
    {
        "March", "Mar", 31, 3
    },
    {
        "April", "Apr", 30, 4
    },
    {
        "May", "May", 31, 5
    }  ,
    {
        "June", "Jun", 30, 6
    },
    {
        "July", "Jul", 31, 7
    },
    {
        "August", "Aug", 31, 8
    },
    {
        "September", "Sep", 30, 9
    },
    {
        "October", "Oct", 31, 10
    },
    {
        "November", "Nov", 30, 11
    },
    {
        "December", "Dec", 31, 12
    }
};
int main(){
    int sum=0,thatday;
    char input[10];
    scanf("%s",input);
    scanf("%d",&thatday);
    for(int i=0;i<12;i++){
        if(strcmp(list[i].name,input)==0||strcmp(list[i].ab,input)==0||list[i].num==atoi(input)){
            sum+=thatday;
            break;
        }
        sum+=list[i].days;
    }
    printf("%d",sum);
}
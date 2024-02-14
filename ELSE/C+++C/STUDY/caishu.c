#include<stdio.h>
void stepq(int *left,int j,int *flag){
    if(*left==j){//如果左边值正好为老师给的
        *flag=1;
    }
    else *left++;//不是则左区间前移
}
void stepz(int *left,int *right,int j,int *flag){
    int mid=(*left+*right)/2;
    if(mid==j){//同上
        *flag=1;
    }
    else if(mid<j)*left=mid+1;//调整左右区间
    else *right=mid-1;
}
void stepc(int *right,int j,int *flag){
    if(*right==j){
        *flag=1;
    }
    else *right++;
}
int main(){
    int sets;
    scanf("%d",&sets);
    getchar();//输入set组数据
    for(int i=0;i<sets;i++){//每组数据一个一个来
        int n,nq=0,nz=0,nc=0;
        scanf("%d",&n);//获取范围的左端点
        int left=1,right=n;
        for(int x=left;x<=right;x++){//循环每次老师给出的数
            int tr=right,tl=left,flag=0;//每次将区间的左右暂存好来改变，重置flag的值
            while(1){//循环直到某人找到老师给出的数
                stepq(&tl,x,&flag);//q操作，判断并改变区间值
                if(flag){//如果找到，就给q记1分
                    nq++;
                    break;//此时退出while也进行下一个for的循环，
                }
                stepz(&tl,&tr,x,&flag);
                if(flag){
                    nz++;
                    break;
                }
                stepc(&tr,x,&flag);
                if(flag){
                    nc++;
                    break;
                }
            }
        }
        printf("%d %d %d",nq,nz,nc);
    }
}
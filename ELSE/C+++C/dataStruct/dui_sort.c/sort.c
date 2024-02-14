#include<stdio.h>
#define N 100
int list[N],lenth;
void head_adjust(int index){
    while (2*index<lenth){
        int maxindex=index*2;
        if (index*2+1<lenth){
            if (list[index*2+1]>list[index*2]){
                maxindex=index*2+1;
            }
        }
        if (list[index])
    }
}
int main(){
}
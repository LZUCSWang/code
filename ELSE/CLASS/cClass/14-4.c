#include<stdio.h>
struct name {
    char firstname[10];
    char lastname[10];
    char mid[10];
};
struct test {
    int num;
    struct name n;
};
struct test arr[5]={
    {
        11111,"wang","xian"
    },
    {
        11112,"Liu","xin","yu"
    },
    {
        11113,"Li","ding","jian"
    },
    {
        11114,"Liu","mei","ren"
    },
    {
        11115,"Li","xue","fen"
    },
};
void show(struct test person){
    if(person.n.mid==NULL){
        printf("%s, %s-- %d",person.n.firstname,person.n.lastname,person.num);
    }
    else printf("%s, %s %c.-- %d",person.n.firstname,person.n.lastname,person.n.mid[0],person.num);
}
int main(){
    for(int i=0;i<5;i++){
        show(arr[i]);
        printf("\n");
    }
}
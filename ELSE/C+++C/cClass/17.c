//修改程序清单17.2，让该程序既能正序也能逆序显示电影列表。一种方法是修改链表的定义，可以双向遍历链表。另一种方法是用递归
/* films2.c -- 使用结构链表 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define TSIZE 45
struct film{
    char title[TSIZE];
    int rating;
    struct film *per;
    struct film *next;
};
char *s_gets(char *st,int n);
int main(){
    struct film *head = NULL;
    struct film *prev,*current;
    char input[TSIZE];
    puts("Enter first movie title:");
    while(s_gets(input,TSIZE) != NULL && input[0] != '\0'){
        current =(struct film *)malloc(sizeof(struct film));
        if(head ==NULL){
            head = current;
            current->per=NULL;
        }
        else {
            prev->next = current;
            current->per =prev;
        }
        current ->next =NULL;
        strcpy(current->title , input);
        puts("Enter your rating <0-10>:");
        scanf("%d",&current->rating);
        while(getchar()!='\n')
        continue;
        puts("Enter next movie title (empty line to stop):");
        prev = current;
    }
    if(head == NULL)printf("No data entered.");
    else printf("Here is the movie list:\n");
    current = head;
    while(1){
        printf("Movie: %s Rating: %d\n",current->title,current->rating);
        if(current->next==NULL)break;
        current = current->next;
    }
    while(current != NULL){
        printf("Movie: %s Rating: %d\n",current->title,current->rating);
        current = current->per;
    }
    current = head;
    head = current->next;
    free(current);
    printf("Bye !\n");
    return 0;
}
char * s_gets(char *st,int n){
    char * ret_val;
    char * find;
    ret_val = fgets(st, n, stdin);
    if(ret_val){
        find = strchr(st, '\n');
        if(find)*find='\0';
        else while(getchar()!='\n');
    }
    return ret_val;
}

/*修改程序清单 14.2 中的图书目录程序，使其按照输入图书的顺序输出图书的信息，然后按照标题字母的声明输出图书的信息，
最后按照价格的升序输出图书的信息。
程序清单14.2 manybook.c程序*/

/* manybook.c -- 包含多本书的图书目录 */

#include <stdio.h>

#include <string.h>

char * s_gets(char * st, int n);

#define MAXTITL 40

#define MAXAUTL 40

#define MAXBKS 100/* 书籍的最大数量 */

struct book { /* 简历 book 模板　　*/

char title[MAXTITL];

char author[MAXAUTL];

float value;

};
void intitle(struct book *library,int count){
    struct book temp;
    for(int i=0;i<count-1;i++){
        for(int j=0;j<count-1-i;j++){
            if(strcmp(library[j].title,library[j+1].title)>0){
                temp=library[j];
                library[j]=library[j+1];
                library[j+1]=temp;
            }
        }
    }
}
void invalue(struct book *library,int count){
    struct book temp;
    for(int i=0;i<count-1;i++){
        for(int j=0;j<count-1-i;j++){
            if(library[j].value>library[j+1].value){
                temp=library[j];
                library[j]=library[j+1];
                library[j+1]=temp;
            }
        }
    }
}
void show(struct book *library,int count){
    int index;
    for (index = 0; index < count; index++)

printf("%s by %s: $%.2f\n", library[index].title,

library[index].author, library[index].value);
}
int main(void)

{

struct book library[MAXBKS];/* book 类型结构的数组 */

int count = 0;

int index;

printf("Please enter the book title.\n");

printf("Press [enter] at the start of datas line to stop.\n");

while (count < MAXBKS && s_gets(library[count].title, MAXTITL) != NULL

&& library[count].title[0] != '\0')

{

printf("Now enter the author.\n");

s_gets(library[count].author, MAXAUTL);

printf("Now enter the value.\n");

scanf("%f", &library[count++].value);

while (getchar() != '\n')

continue; /* 清理输入行*/

if (count < MAXBKS)

printf("Enter the next title.\n");

}

if (count > 0)

{
printf("Here is the list of your books:(by input order\n");
show(library,count);
printf("Here is the list of your books:(for char)\n");
intitle(library,count);
show(library,count);
printf("Here is the list of your books:(by value up)\n");
invalue(library,count);
show(library,count);
}

else

printf("No books? Too bad.\n");


return 0;

}

char * s_gets(char * st, int n)

{

char * ret_val;

char * find;

ret_val = fgets(st, n, stdin);

if (ret_val)

{

find = strchr(st, '\n'); // 查找换行符

if (find)// 如果地址不是 NULL，

*find = '\0';// 在此处放置一个空字符

else

while (getchar() != '\n')

continue;// 处理输入行中剩余的字符

}

return ret_val;

}
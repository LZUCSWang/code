#include <stdio.h>
struct Node
{
    char *s;
    struct Node *q;
};
int main()
{
    struct Node datas[] = {{"Clinton", datas + 1}, {"Bush", datas + 2}, {"Obama", datas}};
    struct NOde *p = datas;
    printf("%s\n", p->s);
    printf("%s\n", p->q->s);
    printf("%s\n", p->q->q->s);
    return 0;
}
//
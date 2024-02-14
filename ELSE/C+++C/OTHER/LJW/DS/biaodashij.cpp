#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
typedef struct node
{
    char data[100];
    struct node *lson, *rson;
} Node;
void creattree(Node **tree)
{
    char temp, str[100], k = 0;
    char ch[100], flag = 1;
    while ((temp = getchar()) != ' ' && temp != '\n')
    {
        if (temp == '+' || temp == '-' || temp == '*' || temp == '/' || temp == '#')
        {
            flag = 0;
            ch[0] = temp;
            ch[1] = '\0';
            continue;
        }
        str[k++] = temp;
    }
    if (flag)
    {
        str[k] = '\0';
        strcpy(ch, str);
    }
    if (strcmp(ch, "#") == 0)
    {
        *tree = NULL;
    }
    else
    {
        *tree = (Node *)malloc(sizeof(Node));
        strcpy((*tree)->data, ch);
        creattree(&((*tree)->lson));
        creattree(&((*tree)->rson));
    }
};
void inOrder(Node *tree)
{
    if (tree != NULL)
    {
        if (tree->data[0] == '+' || tree->data[0] == '-' || tree->data[0] == '*' || tree->data[0] == '/')
        {
            putchar('(');
            inOrder(tree->lson);
            printf("%s", tree->data);
            inOrder(tree->rson);
            putchar(')');
        }
        else
        {
            inOrder(tree->lson);
            printf("%s", tree->data);
            inOrder(tree->rson);
        }
    }
}
int deal(Node *T){
    if (T == NULL)
        return 0;
    if (T->data[0] == '+'){
        return deal(T->lson) + deal(T->rson);
    }
    if (T->data[0] == '-'){
        return deal(T->lson) - deal(T->rson);
    }
    if (T->data[0] == '*'){
        return deal(T->lson) * deal(T->rson);
    }
    if (T->data[0] == '/'){
        return deal(T->lson) / deal(T->rson);
    }
    return atoi(T->data);
}
int main()
{
    Node *tree;
    Node *T;
    char t;
    while ((t = getchar()) != EOF)
    {
        char temp, str[100], k = 0;
        str[k++]=t;
        while ((temp = getchar()) != ' ' && temp != '\n')
        {
            str[k++] = temp;
        }
        str[k] = '\0';
        tree = (Node *)malloc(sizeof(Node));
        strcpy((tree)->data, str);
        creattree(&((tree)->lson));
        creattree(&((tree)->rson));
        inOrder(tree);
         printf("=%d\n", deal(tree));
        // putchar('\n');
    }
    return 0;
}
// + 13 # # * 5 # # 9 # #
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct node
{
    char data[100];
    struct node *lson, *rson;
} Node;
int high = 0;
void startcreat(Node **tree)
{
}
void creattree(Node **tree)
{
    char temp, str[100], k = 0;
    while ((temp = getchar()) != ' ' && temp != '\n')
    {
        str[k++] = temp;
    }
    str[k] = '\0';
    if (strcmp(str, "#") == 0)
    {
        *tree = NULL;
    }
    else
    {
        *tree = (Node *)malloc(sizeof(Node));
        strcpy((*tree)->data, str);
        creattree(&((*tree)->lson));
        creattree(&((*tree)->rson));
    }
}
void righorder(Node *tree)
{
    if (tree == NULL)
        return;
    high++;
    righorder(tree->rson);
    for (int i = 1; i < high; i++)
    {
        printf("    ");
    }
    printf("%s\n", tree->data);
    righorder(tree->lson);
    high--;
}
int main()
{
    Node *tree;
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
        // creattree(&tree);
        righorder(tree);
        putchar('\n');
        // main();
    }
    return 0;
}
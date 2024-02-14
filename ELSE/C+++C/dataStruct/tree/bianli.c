#include <stdio.h>
#include <stdlib.h>
typedef struct node
{
    char data;
    struct node *lchild;
    struct node *rchild;
} node;
node *creat_tree(node *root, FILE *file);
void zhongxu(node *T, FILE *file);
void levelOrder(node *T, FILE *file);
void qianxu(node *T, FILE *file);
void houxu(node *T, FILE *file);
void zhongxunone(node *T, FILE *file);
void qianxunone(node *T, FILE *file);
void houxunone(node *T, FILE *file);
int deeptree(node *T);
int main()
{
    FILE *fipt = fopen("input.txt", "r"), *fopt = fopen("output.txt", "w");
    node *nt;
    nt = creat_tree(nt, fipt);
    fprintf(fopt, "Preorder recursion:\t\t");
    qianxu(nt, fopt);
    fputc('\n', fopt);
    fprintf(fopt, "Medium order recursion:\t\t");
    zhongxu(nt, fopt);
    fputc('\n', fopt);
    fprintf(fopt, "Postorder recursion:\t\t");
    houxu(nt, fopt);
    fputc('\n', fopt);
    fprintf(fopt, "Preorder none recursion:\t");
    qianxunone(nt, fopt);
    fputc('\n', fopt);
    fprintf(fopt, "Medium order none recursion:\t");
    zhongxunone(nt, fopt);
    fputc('\n', fopt);
    fprintf(fopt, "Postorder none recursion:\t");
    houxunone(nt, fopt);
    fputc('\n', fopt);
    fprintf(fopt, "level traversal:\t\t");
    levelOrder(nt, fopt);
    fputc('\n', fopt);
    fprintf(fopt, "depth of tree:\t\t\t%d\n", deeptree(nt));
    fclose(fipt);
    fclose(fopt);
}
node *creat_tree(node *root, FILE *fipt)
{
    char data;
    data = fgetc(fipt);
    if (data == '#')
        return NULL;
    root = (node *)malloc(sizeof(node));
    root->data = data;
    root->lchild = creat_tree(root->lchild, fipt);
    root->rchild = creat_tree(root->rchild, fipt);
    return root;
}
void zhongxu(node *T, FILE *fopt)
{
    if (T == NULL)
        return;
    zhongxu(T->lchild, fopt);
    fprintf(fopt, "%c", T->data);
    zhongxu(T->rchild, fopt);
}
void qianxu(node *T, FILE *fopt)
{
    if (T == NULL)
        return;
    fprintf(fopt, "%c", T->data);
    qianxu(T->lchild, fopt);
    qianxu(T->rchild, fopt);
}
void qianxunone(node *T, FILE *fopt)
{
    if (T == NULL)
    {
        fprintf(fopt, "none\n");
        return;
    }
    int i = 0;
    node *stack[100];
    node *p = T;
    while (p != NULL || i != 0)
    {
        while (p != NULL)
        {
            fprintf(fopt, "%c", p->data);
            stack[++i] = p;
            p = p->lchild;
        }
        if (i != 0)
        {
            p = stack[i--];
            p = p->rchild;
        }
    }
}
void zhongxunone(node *T, FILE *fopt)
{
    if (T == NULL)
    {
        fprintf(fopt, "none\n");
        return;
    }
    int i = 0;
    node *stack[100];
    node *p = T;
    while (p != NULL || i != 0)
    {
        while (p != NULL)
        {
            stack[++i] = p;
            p = p->lchild;
        }
        if (i != 0)
        {
            p = stack[i--];
            fprintf(fopt, "%c", p->data);
            p = p->rchild;
        }
    }
}
void houxu(node *T, FILE *fopt)
{
    if (T == NULL)
        return;
    houxu(T->lchild, fopt);
    houxu(T->rchild, fopt);
    fprintf(fopt, "%c", T->data);
}
void houxunone(node *T, FILE *fopt)
{
    node *last = NULL, *stack[100];
    int i = 0;
    stack[++i] = T;
    while (i != 0)
    {
        T = stack[i];
        if ((T->lchild == NULL && T->rchild == NULL) || (last != NULL && (last == T->lchild || last == T->rchild)))
        {
            fprintf(fopt, "%c", T->data);
            i--;
            last = T;
        }
        else
        {
            if (T->rchild != NULL)
                stack[++i] = T->rchild;
            if (T->lchild != NULL)
                stack[++i] = T->lchild;
        }
    }
}
void levelOrder(node *T, FILE *fopt)
{
    node *queue[100];
    int front = 0, rear = 1;
    while (T != NULL)
    {
        fprintf(fopt, "%c", T->data);
        if (T->lchild != NULL)
            queue[rear++] = T->lchild;
        if (T->rchild != NULL)
            queue[rear++] = T->rchild;
        if (front + 1 == rear)
            break;
        T = queue[++front];
    }
}
int deeptree(node *T)
{
    if (T == NULL)
        return 0;
    int left = deeptree(T->lchild), right = deeptree(T->rchild);
    return left > right ? left + 1 : right + 1;
}
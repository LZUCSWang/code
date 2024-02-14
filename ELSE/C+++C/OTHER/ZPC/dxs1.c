#include <stdio.h>
#include <stdlib.h>
typedef struct Node
{
    int coef;
    int expon;
    struct Node *next;
} node;

node *createnode();
node *add(node *, node *);
node *minus(node *, node *);

void show(node *,FILE *file);
void memory(node *,FILE *file);

int main()
{
    node *temp1, *temp2, *p;
    node *head1 = createnode();
    node *head2 = createnode();
    temp1 = head1;
    temp2 = head2;
    FILE *file1=fopen("input.txt","r");
    FILE *file2=fopen("output.txt","w");
    memory(temp1,file1);
    p = head1->next;
    memory(temp2,file1);
    p = head2->next;

    //相加
    p = add(head1, head2);
    fprintf(file2,"datas(x)+B(x) = ");
    show(p,file2);

    // 相减
    p = minus(head1, head2);
    fprintf(file2,"datas(x)-B(x) = ");
    show(p,file2);
    fclose(file1);
    fclose(file2);
    return 0;
}
node *add(node *s1, node *s2)
{
    node *p = s1->next;
    node *q = s2->next;
    node *head = createnode();
    node *temp = head;
    while (p != NULL && q != NULL)
    {
        node *result = createnode();
        if (p->expon == q->expon)
        {
            result->coef = p->coef + q->coef;
            result->expon = p->expon;
            p = p->next;
            q = q->next;
        }

        else if (p->expon > q->expon)
        {
            result->coef = p->coef;
            result->expon = p->expon;
            p = p->next;
        }
        else
        {
            result->coef = q->coef;
            result->expon = q->expon;
            q = q->next;
        }
        temp->next = result;
        temp = result;
    }
    while (p != NULL)
    {
        node *result = createnode();
        result->coef = p->coef;
        result->expon = p->expon;
        p = p->next;
        temp->next = result;
        temp = result;
    }
    while (q != NULL)
    {
        node *result = createnode();
        result->coef = q->coef;
        result->expon = q->expon;
        q = q->next;
        temp->next = result;
        temp = result;
    }
    return head->next;
}
node *minus(node *s1, node *s2)
{
    node *p = s1->next;
    node *q = s2->next;
    node *head = createnode();
    node *temp = head;
    while (p != NULL && q != NULL)
    {
        node *result = createnode();
        if (p->expon == q->expon)
        {
            result->coef = p->coef - q->coef;
            result->expon = p->expon;
            p = p->next;
            q = q->next;
        }

        else if (p->expon > q->expon)
        {
            result->coef = p->coef;
            result->expon = p->expon;
            p = p->next;
        }
        else
        {
            result->coef = -q->coef;
            result->expon = q->expon;
            q = q->next;
        }
        temp->next = result;
        temp = result;
    }
    while (p != NULL)
    {
        node *result = createnode();
        result->coef = p->coef;
        result->expon = p->expon;
        p = p->next;
        temp->next = result;
        temp = result;
    }
    while (q != NULL)
    {
        node *result = createnode();
        result->coef = -q->coef;
        result->expon = q->expon;
        q = q->next;
        temp->next = result;
        temp = result;
    }
    return head->next;
}
node *createnode()
{
    node *P = (node *)malloc(sizeof(node));
    P->next = NULL;
    return P;
}
void show(node *head,FILE *file)
{
    int c = 1;
    node *p = head;
    while (p != NULL)
    {
        if (p->coef == 0)
            p = p->next;
        else if (p->coef == 1)
        {
            if (c++ != 1)
            {
                if (p->expon == 1)
                    fprintf(file,"+x");
                else if (p->expon == 0)
                    fprintf(file,"%+d ", p->coef);
                else
                    fprintf(file,"+x^%d ", p->expon);
            }
            else
            {
                if (p->expon == 1)
                    fprintf(file,"x");
                else if (p->expon == 0)
                    fprintf(file,"%+d ", p->coef);
                else
                    fprintf(file,"x^%d ", p->expon);
            }
            p = p->next;
        }
        else if (p->coef == -1)
        {
            if (p->expon == 1)
                fprintf(file,"-x");
            else if (p->expon == 0)
                fprintf(file,"%+d ", p->coef);
            else
                fprintf(file,"-x^%d ", p->expon);
            p = p->next;
            c++;
        }
        else
        {
            if (c++ == 1)
            {
                if (p->expon == 1)
                    fprintf(file,"%dx", p->coef);
                else if (p->expon == 0)
                    fprintf(file,"%d ", p->coef);
                else
                    fprintf(file,"%dx^%d ", p->coef, p->expon);
            }

            else
            {
                if (p->expon == 1)
                    fprintf(file,"%+dx ", p->coef);
                else if (p->expon == 0)
                    fprintf(file,"%+d ", p->coef);
                else
                    fprintf(file,"%+dx^%d ", p->coef, p->expon);
            }
            p = p->next;
        }
    }
    fprintf(file,"\n");
}
void memory(node *temp,FILE * file)
{
    int datas, b;
    node *p;
    while (fscanf(file,"%d %d", &datas, &b) && datas != 0)
    {
        p = createnode();
        p->coef = datas;
        p->expon = b;
        temp->next = p;
        temp = p;
    }
}
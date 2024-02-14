#include <stdio.h>
#include <stdlib.h>
struct node
{
    char ch;
    struct node *next;
};
int main()
{
    int k = 25;
    struct node *head = (struct node *)malloc(sizeof(struct node));
    struct node *p = head;
    struct node *clea;
    char input[27];
    fgets(input, 27, stdin);
    for (int i = 0; i < 26; i++)
    {
        struct node *newnode = (struct node *)malloc(sizeof(struct node));
        p->next = newnode;
        newnode->next = NULL;
        newnode->ch = input[k--];
        p = newnode;
    }
    p->next = NULL;
    p = head->next;
    for (int i = 0; i < 26; i++)
    {
        printf("%c", p->ch);
        clea = p;
        p = p->next;
        free(clea);
    }
}
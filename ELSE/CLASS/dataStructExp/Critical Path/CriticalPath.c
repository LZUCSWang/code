#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define Max 20
int dutt[Max];
typedef struct Node
{
    int Point;
    int distance;
    struct Node *next;
} Node, list[Max];
typedef struct
{
    list biao;
    int points, sides;
} Graph;
typedef struct
{
    int data[100];
    int top;
} STACK;
STACK S, T;
void CreateGraph(Graph *G)
{
    int i, j, k, w, v1, v2;
    Node *p;
    FILE *fipt = fopen("input.txt", "r");
    memset(dutt, 0, sizeof(dutt));
    fscanf(fipt, "%d %d", &(*G).points, &(*G).sides);
    for (i = 1; i <= (*G).points; i++)
    {
        (*G).biao[i].Point = i;
        (*G).biao[i].next = NULL;
    }
    for (k = 1; k <= (*G).sides; k++)
    {
        fscanf(fipt, "%d %d %d", &v1, &v2, &w);
        p = (Node *)malloc(sizeof(Node));
        p->Point = v2;
        p->distance = w;
        p->next = (*G).biao[v1].next;
        (*G).biao[v1].next = p;
        dutt[v2]++;
    }
    S.top = 0;
    for (int i = 1; i <= (*G).points; i++)
    {
        if (dutt[i] == 0)
            S.data[++S.top] = i;
    }
    fclose(fipt);
}
void CriticalPath(Graph *G)
{
    int i, k, e, l, Ve[Max] = {0}, Vl[Max];
    FILE *fopt = fopen("output.txt", "w");
    Node *p;
    T.top = 0;
    while (S.top > 0)
    {
        i = S.data[S.top--];
        Node *p = (*G).biao[i].next;
        while (p != NULL)
        {
            k = p->Point;
            if (Ve[i] + p->distance > Ve[k])
                Ve[k] = Ve[i] + p->distance;
            dutt[k]--;
            if (dutt[k] == 0)
                S.data[++S.top] = k;
            p = p->next;
        }
        T.data[++T.top] = i;
    }
    for (i = 1; i <= (*G).points; i++)
        Vl[i] = Ve[(*G).points];
    while (T.top > 0)
    {
        i = T.data[T.top--];
        p = (*G).biao[i].next;
        while (p != NULL)
        {
            k = p->Point;
            if (Vl[k] - p->distance < Vl[i])
                Vl[i] = Vl[k] - p->distance;
            p = p->next;
        }
    }
    for (i = 1; i <= (*G).points; i++)
    {
        p = (*G).biao[i].next;
        if (p == NULL)
            fprintf(fopt, "%d ", i);
        while (p != NULL)
        {
            k = p->Point;
            if (Ve[i] == Vl[k] - p->distance)
            {
                fprintf(fopt, "%d ", i);
                break;
            }
            p = p->next;
        }
    }
    fclose(fopt);
}

int main()
{
    Graph G;
    CreateGraph(&G);
    CriticalPath(&G);
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct node
{
    int data;
    struct node *next;
} node;
int visited[100], graph[100][100], n, m;
node list[100];
void dfs_search2(int now, FILE *fopt)
{
    for (int i = 1; i <= n; i++)
    {
        if (i != now && graph[now][i] == 1 && visited[i] == 0)
        {
            fprintf(fopt, "%d ", i);
            visited[i] = 1;
            dfs_search2(i, fopt);
        }
    }
}
void dfs2(FILE *fopt, int start) //邻接矩阵 深搜
{
    memset(visited, 0, sizeof(visited));
    fprintf(fopt, "DFS_2 start from:%d\t", start);
    fprintf(fopt, "%d ", start);
    visited[start] = 1;
    dfs_search2(start, fopt);
    for (int i = 1; i <= n; i++)
    {
        if (visited[i] == 0)
        {
            fprintf(fopt, "%d ", list[i].data);
            visited[i] = 1;
            dfs_search2(i, fopt);
        }
    }
    fprintf(fopt, "\n");
}
void dfs_search1(node *T, FILE *fopt)
{

    while (T != NULL)
    {
        if (visited[T->data] == 0)
        {
            fprintf(fopt, "%d ", T->data);
            visited[T->data] = 1;
            dfs_search1(&list[T->data], fopt);
        }
        T = T->next;
    }
}
void dfs1(FILE *fopt, int start) //邻接表 深搜
{
    memset(visited, 0, sizeof(visited));
    fprintf(fopt, "DFS_1 start from:%d\t", start);
    fprintf(fopt, "%d ", list[start].data);
    visited[start] = 1;
    dfs_search1(&list[start], fopt);
    for (int i = 1; i <= n; i++)
    {
        if (visited[i] == 0)
        {
            fprintf(fopt, "%d ", list[i].data);
            visited[i] = 1;
            dfs_search1(&list[i], fopt);
        }
    }
    fprintf(fopt, "\n");
}
void bfs1(FILE *fopt, int start)
{
    int front = 0, rear = 1;
    node *queue[100], *T;
    queue[rear++] = &list[start];
    while (front + 1 != rear)
    {
        T = queue[++front];
        if (visited[T->data] == 1)
            continue;
        fprintf(fopt, "%d ", T->data);
        visited[T->data] = 1;
        while (T->next != NULL)
        {
            if (visited[T->next->data] == 0)
                // visited[T->next->data] = 1;
                queue[rear++] = &list[T->next->data];
            T = T->next;
        }
    }
    // fprintf(fopt, "\n");
}
void bfs2(FILE *fopt, int start)
{
    int queue[100];
    int front = 0, rear = 1;
    queue[rear++] = start;
    while (front + 1 != rear)
    {
        int now = queue[++front];
        if (visited[now] == 1)
            continue;
        fprintf(fopt, "%d ", now);
        visited[now] = 1;
        for (int i = 1; i <= n; i++)
        {
            if (graph[now][i] == 1 && visited[i] == 0)
            {
                queue[rear++] = i;
            }
        }
    }
}
void bfs22(FILE *fopt, int start) //邻接矩阵 广搜
{
    memset(visited, 0, sizeof(visited));
    fprintf(fopt, "BFS_2 start from:%d\t", start);
    bfs2(fopt, start);
    for (int i = 1; i <= n; i++)
    {
        if (visited[i] == 0)
        {
            bfs2(fopt, i);
        }
    }
}
void getinfo1(FILE *fipt) //读取邻接表
{
    rewind(fipt);
    node *p;
    char temp;
    char c;
    fscanf(fipt, "%d %d", &n, &m);
    fgetc(fipt);
    for (int i = 1; i <= n; i++)
    {
        temp = fgetc(fipt);
        list[i].data = temp - '0';
        list[i].next = NULL;
        p = &list[i];
        fgetc(fipt);
        while ((c = fgetc(fipt)) != '\n')
        {
            p->next = (node *)malloc(sizeof(node));
            p = p->next;
            p->data = c - '0';
            p->next = NULL;
            if (fgetc(fipt) == '\n')
                break;
        }
    }
}
void getinfo2(FILE *fipt) //读取邻接矩阵
{
    rewind(fipt);
    fscanf(fipt, "%d %d", &n, &m);
    fgetc(fipt);
    char temp;
    memset(graph, 0, sizeof(graph));
    for (int i = 1; i <= n; i++)
    {
        temp = fgetc(fipt);
        fgetc(fipt);
        while ((temp = fgetc(fipt)) != '\n')
        {
            graph[i][temp - '0'] = 1;
            if (fgetc(fipt) == '\n')
                break;
        }
    }
}
void bfs11(FILE *fopt, int start)
{
    memset(visited, 0, sizeof(visited));
    fprintf(fopt, "BFS_1 start from:%d\t", start);
    bfs1(fopt, start);
    for (int i = 1; i <= n; i++)
    {
        if (visited[i] == 0)
        {
            bfs1(fopt, i);
        }
    }
}

int main()
{
    FILE *fipt = fopen("input.txt", "r");
    FILE *fopt = fopen("output.txt", "w");
    getinfo1(fipt);
    getinfo2(fipt);
    dfs1(fopt, 1);
    dfs2(fopt, 1);
    bfs11(fopt, 1);
    fprintf(fopt, "\n");
    bfs22(fopt, 1);
    fclose(fipt);
    fclose(fopt);
}
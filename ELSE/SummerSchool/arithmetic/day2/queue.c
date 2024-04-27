#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100000000
struct queue
{
    int list[MAX];
    int front;
    int rear;
    int length;
} q1, q2;
void enqueue(struct queue *q, int data)
{
    q->rear = (q->rear + 1) % MAX;
    q->list[q->rear] = data;
    q->length++;
}
int dequeue(struct queue *q)
{
    q->front = (q->front + 1) % MAX;
    int data = q->list[q->front];
    q->length--;
    return data;
}
int dequeueright(struct queue *q)
{
    int data = q->list[q->rear];
    q->rear = (q->rear - 1 + MAX) % MAX;
    q->length--;
    return data;
}
int main()
{
    q1.front = 0, q1.rear = 0, q1.length = 0;
    q2.front = 0, q2.rear = 0, q2.length = 0;
    int m, n, i;
    char ipt[1000];
    scanf("%d %d", &m, &n);
    for (i = 0; i < m; i++)
    {
        scanf("%s", ipt);
        if (strcmp(ipt, "DeQueue") == 0)
        {
            if (q1.length == 0)
            {
                printf("Empty Queue\n");
            }
            else
            {
                int t = dequeue(&q1);
                printf("%d\n", t);
                if (q1.length < q2.length)
                    enqueue(&q1, dequeue(&q2));
            }
        }
        else if (strcmp(ipt, "DeleteMid") == 0)
        {
            if (q1.length == 0)
            {
                printf("Empty Queue\n");
            }
            else
            {
                int t = dequeueright(&q1);
                printf("%d\n", t);
                if (q1.length < q2.length)
                {
                    enqueue(&q1, dequeue(&q2));
                }
            }
        }
        else
        {
            int data;
            scanf("%d", &data);
            if (q1.length + q2.length >= n)
            {
                printf("Full Queue\n");
                continue;
            }
            enqueue(&q2, data);
            if (q1.length < q2.length)
            {
                enqueue(&q1, dequeue(&q2));
            }
        }
    }
    int flag = 0;
    while (q1.length > 0)
    {
        if (flag)
        {
            printf(" ");
        }
        int t = dequeue(&q1);
        printf("%d", t);
        flag = 1;
    }
    while (q2.length > 0)
    {
        int t = dequeue(&q2);
        printf(" %d", t);
    }
    return 0;
}
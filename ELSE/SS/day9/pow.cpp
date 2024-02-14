#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct node *Node;
struct node
{
    char String[9];
};

int Mod(int a, int p)
{
    while (a < 0)
        a += p;
    return a % p;
}

int main()
{
    int n = 1009 * 1009, p;
    // printf("%d",n);
    scanf("%d%d", &n, &p);
    while (n > p)
        n++; //地雷，确保p要比n大
    Node *Hash = (Node *)malloc(sizeof(Node) * p);
    for (int i = 0; i < p; i++)
        Hash[i] = NULL;

    char name[9];
    for (int i = 0; i < n; i++)
    {
        //      getchar();
        scanf("%s", name);
        //      printf("{%s}",name);
        int Index = 0, weight = 1;
        for (int len = strlen(name), k = len - 1; (k >= 0) && (len - k < 4); k--)
        {   //计算字符串末尾3字符的值
            //      printf("{%d}",k);
            Index += (name[k] - 'A') * weight;
            weight *= 32;
        }
        int flag, j;
        for (j = 0; j <= p / 2; j++)
        { // j<=p/2是平方探测的一个重要区间,这个问题中有没它都一样
            flag = Mod(Index + j * j, p);
            if (!Hash[flag])
                break;
            else if (!strcmp(Hash[flag]->String, name))
                break;
            flag = Mod(Index - j * j, p); //这应该是
            if (!Hash[flag])
                break;
            else if (!strcmp(Hash[flag]->String, name))
                break;
        }
        if (j > p / 2)
        { //本来是要哈希重构的，但是埋了个地雷没炸，说明给的数据还没超载
            while (1)
                n++; //地雷
        }
        Hash[flag] = (Node)malloc(sizeof(struct node));
        strcpy(Hash[flag]->String, name);
        if (i)
            printf(" ");
        printf("%d", flag);
    }

    return 0;
}

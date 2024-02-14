#include <stdio.h>
int find(int *arry, int m)
{ //找到列表中唯一一个非0 值，即为王
    int i;
    for (i = 0; i < m; i++)
    {
        if (arry[i] != 0)
        {
            return arry[i];
        }
    }
    return 0;
}
void deal_index(int *arry, int m, int n, int *index)
{ //用于处理下标的变换
    for (int i = 0; i < n - 1; i++)
    { //下标变化n-1次
        *index = (*index + 1) % m;
        if (arry[*index] == 0)
        { //如果当前为被淘汰的节点，就多递增一次
            i--;
        }
    }
}
int main()
{
    int m, n;
    scanf("%d %d", &m, &n);
    int index = 0;
    int arry[m];
    int cnt = 0;
    for (int i = 0; i < m; i++)
    {
        arry[i] = i + 1; //赋值
    }
    while (1)
    {                                   //循环
        cnt++;                          //计数
        deal_index(arry, m, n, &index); //处理下标变换
        arry[index] = 0;                //标记已被淘汰
        if (cnt == m - 1)
        {                                //已淘汰m-1个
            printf("%d", find(arry, m)); //输出唯一的非0即为王
            return 0;
        }
        index = (index + 1) % m;
        while (arry[index] == 0)
        { //直到找到非0即未被淘汰的为止
            index = (index + 1) % m;
        }
    }
}
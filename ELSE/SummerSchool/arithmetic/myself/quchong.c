#include <stdio.h>
#include <math.h>
#define MAX 100001
int ok_address[MAX], del_address[MAX], ok_num;
struct node
{
    int data;
    int next;
} list[MAX];
int main()
{
    int head_address, n, address, nextaddress, data, flag[MAX] = {0}, ok_num = 0, del_num = 0, value;
    scanf("%d %d", &head_address, &n);
    for (int i = 0; i < n; i++)
    {
        scanf("%d %d %d", &address, &data, &nextaddress);
        list[address].data = data;
        list[address].next = nextaddress;
    }
    while (head_address != -1)
    {
        value = fabs(list[head_address].data);
        if (flag[value] == 0)
        {
            ok_address[ok_num++] = head_address;
            flag[value] = 1;
        }
        else
            del_address[del_num++] = head_address;
        head_address = list[head_address].next;
    }
    for (int i = 0; i < ok_num - 1; i++)
        printf("%05d %d %05d\n", ok_address[i], list[ok_address[i]].data, ok_address[i + 1]);
    printf("%05d %d %d\n", ok_address[ok_num - 1], list[ok_address[ok_num - 1]].data, -1);
    for (int i = 0; i < del_num - 1; i++)
        printf("%05d %d %05d\n", del_address[i], list[del_address[i]].data, del_address[i + 1]);
    printf("%05d %d %d\n", del_address[del_num - 1], list[del_address[del_num - 1]].data, -1);
}
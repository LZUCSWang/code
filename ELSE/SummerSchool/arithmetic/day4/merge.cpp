#include <bits/stdc++.h>
#define MAX 1000001
using namespace std;
int lists1[MAX], lists2[MAX], nows[MAX];
void print(int list[], int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d", list[i]);
        if (i != n - 1)
        {
            printf(" ");
        }
    }
    printf("\n");
}
bool judge(int list[], int n)
{
    for (int i = 0; i < n; i++)
    {
        if (list[i] != nows[i])
        {
            return false;
        }
    }
    return true;
}
void insert_sort(int list[], int n)
{
    bool flag = false;
    for (int i = 1; i < n; i++)
    {
        int nowsitem = list[i];
        int j = i - 1;
        while (j >= 0 & nowsitem < list[j])
        {
            list[j + 1] = list[j];
            j--;
        }
        list[j + 1] = nowsitem;
        // print(list, n);
        if (flag == true)
        {
            printf("Insertion Sort\n");
            print(list, n);
            exit(0);
        }
        if (judge(list, n))
        {
            flag = true;
        }
    }
}
void merge(int list[], int temp[], int mid, int left, int right)
{
    int left_p = left, right_p = mid + 1, t_p = left;
    int temp_num=0,ans=0;
    while (left_p <= mid && right_p <= right)
    {
        if (list[left_p] < list[right_p])
        {
            temp[t_p++] = list[left_p++];
        }
        else
        {
            temp[t_p++] = list[right_p++];
        }
    }
    while (left_p <= mid)
        temp[t_p++] = list[left_p++];
    while (right_p <= right)
        temp[t_p++] = list[right_p++];
    for (int i = left; i <= right; i++)
    {
        list[i] = temp[i];
    }
}
void mesort(int list[], int temp[], int n, int left, int right, bool *flag)
{
    if (left < right)
    {
        int mid = (left + right) >> 1;
        mesort(list, temp, n, left, mid, flag);
        mesort(list, temp, n, mid + 1, right, flag);
        merge(list, temp, mid, left, right);
        if (*flag)
        {
            printf("Merge Sort\n");
            print(list, n);
            exit(0);
        }
        if (judge(list, n))
        {
            *flag = true;
        }
    }
}
void merg_sort(int list[], int n)
{
    bool flag = false;
    int *temp = (int *)malloc(sizeof(int) * n);
    mesort(list, temp, n, 0, n - 1, &flag);
}
void merg_sort_non(int list[], int n)
{
    int *temp = (int *)malloc(sizeof(int) * n);
    int dis = 1;
    bool flag = false;
    while (dis < n)
    {
        for (int i = 0; i < n; i += dis * 2)
        {
            int l1 = i, r1 = i + dis - 1, l2 = r1 + 1, r2 = l2 + dis - 1;
            int t_p = i;
            if (r1 >= n)
            {
                r1 = n - 1;
                l2 = 1;
                r2 = 0;
            }
            else if (l2 >= n)
            {
                l2 = 1, r2 = 0;
            }
            else if (r2 >= n)
            {
                r2 = n - 1;
            }
            while (l1 <= r1 && l2 <= r2)
            {
                if (list[l1] <= list[l2])
                {
                    temp[t_p++] = list[l1++];
                }
                else
                {
                    temp[t_p++] = list[l2++];
                }
            }
            while (l1 <= r1)
            {
                temp[t_p++] = list[l1++];
            }
            while (l2 <= r2)
            {
                temp[t_p++] = list[l2++];
            }
            for (l1 = i; l1 <= r2; l1++)
            {
                list[l1] = temp[l1];
            }
        }
        if (flag)
        {
            printf("Merge Sort\n");
            print(list, n);
            exit(0);
        }
        if (judge(list,n)){
            flag=true;
        }
        dis *= 2;
    }
}
int main()
{
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &lists1[i]);
        lists2[i] = lists1[i];
    }
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &nows[i]);
    }
    insert_sort(lists1, n);
    merg_sort_non(lists2, n);
}
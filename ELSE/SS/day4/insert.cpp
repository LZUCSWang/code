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
void adjust(int list[], int n, int index)
{
    int lag = index, lson = index * 2 + 1, rson = index * 2 + 2;
    if (lson < n && list[lson] > list[lag])
    {
        lag = lson;
    }
    if (rson < n && list[rson] > list[lag])
    {
        lag = rson;
    }
    if (lag == index)
    {
        return;
    }
    swap(list[lag], list[index]);
    adjust(list, n, lag);
}
void heap_sort(int list[], int n)
{
    bool flag = false;
    for (int i = n / 2 - 1; i >= 0; i--)
    {
        adjust(list, n, i);
    }
    for (int i = n - 1; i >= 0; i--)
    {
        swap(list[i], list[0]);
        adjust(list, i, 0);
        if (flag == true)
        {
            printf("Heap Sort\n");
            print(list, n);
            exit(0);
        }
        if (judge(list, n))
        {
            flag = true;
        }
        // print(n);
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
    // print(n);
    insert_sort(lists1, n);
    heap_sort(lists2, n);
    // print(n);
}
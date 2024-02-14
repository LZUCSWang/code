
#include <stdio.h>
#define MAX 100000 // 4096作为 整形数组的结束标识
int len = 0;	   // 测试数组的长度
void insert(int a[], int point, int data)
{
	if (a[point] > data) // 说明 插入值该插入到其前面
	{
		for (int i = len - 1; i >= point; i--)
		{
			a[i + 1] = a[i]; // 向后移动一个 单位 (原point位置的值也向后移动)
		}
		a[point] = data; // 目标值插入到point位置
	}
	else // 如果大于等于其值就 插入到目标点 后面
	{
		for (int i = len - 1; i > point; i--)
		{
			a[i + 1] = a[i]; // 向后移动一个 单位 (原point位置的值也向后移动)
		}
		a[point + 1] = data; // 目标值插入到point位置
	}
}
void BinarySearch(int a[], int low, int high, int data)
{
	if (low == high) // 找到 插入点
	{
		insert(a, low, data); // 参数:数组，插入点，插入数据
		return;
	}
	int mid = (low + high) / 2; // 获取 中间值

	if (a[mid] < data) // mid小于data 递增有序表中说明 得插入在是在mid的右边
	{
		BinarySearch(a, mid + 1, high, data);
	}
	else if (a[mid] > data) // mid大于data 递增有序表中说明 得插入在mid的左边
	{
		BinarySearch(a, low, mid - 1, data);
	}
	else // 如果存在和插入值一样大的数 直接插入
	{
		insert(a, mid, data); // 参数:数组，插入点，插入数据
		return;
	}
	return;
}
int Seq_Search(int *aa, int key)
{
	int i;
	for (i = len; aa[i] != key; i--)
	{
		; // for循环内为空语句
	}
	return i; // 返回0:查找失败;返回值>0:查找成功
}
void print(int *aa)
{
	for (int i = 0; i < len; i++)
	{
		printf("%d ", aa[i]);
	}
	printf("\n");
}
int main()
{
	int aa[MAX], choice = 1;
	printf("Input the length\n");
	scanf("%d", &len);
	printf("Input the arry\n");
	for (int i = 0; i < len; i++)
		scanf("%d", aa + i);

	// 输入要插入的值
	while (choice != 0)
	{

		printf("Input your choice (1 for insert,2 for search,3 for show,0 for exit)\n");
		scanf("%d", &choice);
		if (choice == 1)
		{
			printf("Input the num you want to insert\n");
			int data;
			scanf("%d", &data);
			BinarySearch(aa, 0, len - 1, data);
			len++;
		}
		else if (choice == 2)
		{
			printf("Input the nums you want to search\n");
			int key;
			scanf("%d", &key);
			int ans = Seq_Search(aa, key);
			if (ans == 0)
				printf("Not found\n");
			else
				printf("Found at %d\n", ans + 1);
		}
		else if (choice == 3)
		{
			print(aa);
		}
	}
	return 0;
}

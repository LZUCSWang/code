/*
利用二分查找算法在一个有序表中插入一个元素x，
并保持表的有序性。 
*/
 
#include <stdio.h>
#define END 1 << 12//4096作为 整形数组的结束标识 
 
int get_len(int a[]);//获取数组长度 
void print_array(int a[]);//打印数组
 
int len = 0;//测试数组的长度 
void insert(int a[],int point,int data)
{
	if(a[point] > data)//说明 插入值该插入到其前面 
	{
		for(int i = len - 1;i >= point;i --)
		{
			a[i + 1] = a[i];//向后移动一个 单位 (原point位置的值也向后移动)
		}
		
		a[point] = data;//目标值插入到point位置 
	}
	else//如果大于等于其值就 插入到目标点 后面 
	{
		for(int i = len - 1;i > point;i --)
		{
			a[i + 1] = a[i];//向后移动一个 单位 (原point位置的值也向后移动)
		}
		
		a[point + 1] = data;//目标值插入到point位置
	}
	
}
 
//二分查找 插入位置 并插入 
void BinarySearch(int a[],int low,int high,int data)
{
	if(low == high)//找到 插入点 
	{
		insert(a,low,data);//参数:数组，插入点，插入数据 
		return;
	}
	int mid = (low + high)/2;//获取 中间值
	
	if(a[mid] < data)//mid小于data 递增有序表中说明 得插入在是在mid的右边 
	{
		BinarySearch(a,mid + 1,high,data);
	}
	else if(a[mid] > data)//mid大于data 递增有序表中说明 得插入在mid的左边 
	{
		BinarySearch(a,low,mid - 1,data);
	}
	else//如果存在和插入值一样大的数 直接插入 
	{
		insert(a,mid,data);//参数:数组，插入点，插入数据 
		return; 
	}
	
	return;
}
 
int main()
{
	int a[101] = {1,2,2,15,16,18,20,20,30,33,END};//test 有序表 END为结束符（默认为0，如果不用0需要自己定义结束符） 
	len = get_len(a);//获取元素个数
	
	//print打印 原数组 
    print_array(a);
 
	//输入要插入的值
	int data = 0;
 
	scanf("%d",&data); 
	
	//二分查找 插入位置 并插入 
    BinarySearch(a,0,len - 1,data);
    
    a[len + 1] = END;//增加一个 元素 完毕 添上结束符 
    //print打印 插入后数组 样子 
    print_array(a);
	
	return 0;
} 
 
//打印数组 
void print_array(int a[])
{
	int size = get_len(a);//获取 传入数组的元素长度 
	for(int i = 0;i < size;i ++)
	{
		printf("%d ",a[i]);
	}
	printf("\n");
	return;
}
//获取数组长度 
int get_len(int a[])
{
	int i = 0;
	while(a[i] != END)
	{
		i ++;
	}
 
	return i;
}

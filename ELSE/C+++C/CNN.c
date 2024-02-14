#include<stdio.h>
#include<stdlib.h>

void convolution2(int* input1, int* input2, int* output, int mm, int nn)
{
	//存储地址
	int* xx = (int*)malloc(sizeof(int) * (mm + nn - 1));
	for (int i = 0; i < mm + nn - 1; i++) {
		xx[i] = 0;
	}

	//开始卷积
	//利用时延效果，记录所有乘积后，时间位置一样的相加
	for (int i = 0; i < mm; i++) {
		for (int j = 0; j < nn; j++) {
			xx[i + j] += input1[i] * input2[j];
		}
	}

	for (int i = 0; i < mm + nn - 1; i++) {
		output[i] = xx[i];
	}
}

int main() {
	int mm, nn;
	printf("请输入第一个卷积数目\n");
	scanf_s("%d", &mm);

	//malloc分配空间
	int* input1 = (int*)malloc(sizeof(int) * mm);
	printf("请输入第一个卷积数值\n");
	for (int i = 0; i < mm; i++) {
		scanf_s("%d", &input1[i]);
	}
	printf("请输入第二个卷积数目\n");
	scanf_s("%d", &nn);
	int* input2 = (int*)malloc(sizeof(int) * nn);
	printf("请输入第二个卷积数值\n");
	for (int j = 0; j < nn; j++) {
		scanf_s("%d", &input2[j]);
	}

	//卷积最大空间
	int* output = (int*)malloc(sizeof(int) * (mm + nn - 1));
	convolution2(input1, input2, output, mm, nn);

	printf("卷积结果\n");
	for (int i = 0; i < mm + nn - 1; i++)
	{
		printf("%d ", output[i]);
	}
	printf("\n");

	return 0;
}

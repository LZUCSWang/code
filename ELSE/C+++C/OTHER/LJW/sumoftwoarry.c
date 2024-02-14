#include <stdio.h>
int f(int LX, int LY, int RX, int RY, int datas[300][300], int i, int j);
int main()
{
	int LY, LX, RX, RY, q;
	int datas[300][300], i, j, m, n;
	scanf("%d %d", &m, &n);
	for (i = 0; i < m; i++)
	{
		for (j = 0; j < n; j++)
		{
			scanf("%d", &datas[i][j]);
		}
		scanf("%d", &q);
		for (int i = 1; i <= q; i++)
		{
			scanf("%d %d %d %d", &LX, &LY, &RX, &RY);
			printf("%d", f(LX, LY, RX, RY, datas, i, j));
		}
	}

	return 0;
}
int f(int LX, int LY, int RX, int RY, int datas[300][300], int i, int j)
{
	int sum = 0;
	if (LX <= i && i <= RX && LY <= j && j <= RY)
	{
		sum = sum + datas[i][j];
	}
	return sum;
}

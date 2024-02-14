#include <bits/stdc++.h>
using namespace std;
#define MAX 1010
typedef long long ll;
int datas[MAX][MAX];
int main()
{
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
			datas[i][j] = (n / 4 * (i / 4) + j / 4) * 16 + i % 4 * 4 + j % 4;
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (j == 0)
				printf("%d", datas[i][j]);
			else
				printf(" %d", datas[i][j]);
		}
		puts("");
	}
	return 0;
}
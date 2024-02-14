#include <bits/stdc++.h>
using namespace std;
struct pt
{
	int l, r;
};
pt datas[(int)2e5 + 5];
int n, f[(int)2e5 + 5], p = 0; // f[i]=长度为i的IS最小最后一个数

bool cmp(pt x, pt y)
{
	return x.l < y.l;
}

int main()
{
	cin >> n;
	for (int i = 1; i <= n; i++)
		scanf("%d%d", &datas[i].l, &datas[i].r);
	sort(datas + 1, datas + 1 + n, cmp);
	for (int i = 1; i <= n; i++)
	{
		printf("%d,datas[i]=%d\n", i, datas[i].r);
		if (datas[i].r > f[p])
		{
			printf("datas[i].r = %d , f[p]= %d\n", datas[i].r, f[p]);
			p++, f[p] = datas[i].r;
		}
		else
		{
			f[lower_bound(f + 1, f + p + 1, datas[i].r) - f] = datas[i].r;
			printf("%d\n", f[lower_bound(f + 1, f + p + 1, datas[i].r) - f]);
		}
	}
	cout << p << endl;
	return 0;
}
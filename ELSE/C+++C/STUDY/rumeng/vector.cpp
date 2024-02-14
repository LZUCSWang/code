#include <bits/stdc++.h>
using namespace std;
long double ans, a, b, c, t;
int main()
{
	scanf("%Lf%Lf%Lf", &a, &b, &c);
	t = 0;
	if (c > a + b)
		t = c - a - b;
	ans = (t * t - c * c - a * a - b * b) / 2.0;
	printf("%0.1Lf", ans);
	return 0;
}
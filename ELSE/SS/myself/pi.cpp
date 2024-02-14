#include <iostream>
#include <cstdio>
 
using namespace std;
 
int n, a[100005], tmpA[100005], cnt = 0;
 
void merge_sort(int l, int r, int *A) {
	if (l >= r) return ;
	int mid = (l + r) >> 1;
	merge_sort(l, mid, A);
	merge_sort(mid + 1, r, A);
	int pl = l, pr = mid + 1, tmpp = 0;
	while(pl <= mid && pr <= r) {
		if (A[pl] <= A[pr]) tmpA[tmpp++] = A[pl++];
		else tmpA[tmpp++] = A[pr++], cnt += mid - pl + 1;
	}
	while(pl <= mid) tmpA[tmpp++] = A[pl++];
	while(pr <= r) tmpA[tmpp++] = A[pr++];
	for (int i = 0; i < tmpp; i++) A[i + l] = tmpA[i];
} 
 
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
	merge_sort(1, n, a);
	printf("%d\n", cnt);
	return 0;
}
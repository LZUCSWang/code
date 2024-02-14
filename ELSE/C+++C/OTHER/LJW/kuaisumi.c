#include<stdio.h>
int main()
{
	long long int n,m;
	while(scanf("%lld,%lld",&n,&m)==2){
		int x=1;
		n=n%1000;
		while(m>0){
			if(m%2==1){
				x=(x*n)%1000;
			}
			m=m/2;
			n=(n*n)%1000;
		}
		printf("%d\n",x);
	}
	return 0;	
}

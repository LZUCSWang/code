#include<stdio.h>
void paixu(int *arr){
	for(int i=0;i<2;i++){
		for(int j=0;j<2-i;j++){
			if(arr[j]>arr[j+1]){
				int t;
				t=arr[j];
				arr[j]=arr[j+1];
				arr[j+1]=t;
			}
		}
	}
}
void heidong(int n){
	printf("%d: ",n);
	int x,y,z;
	x=n%10;
	if(n<10){
		y=z=0;
	}
	else if(n<100){
		y=n/10%10;
		z=0;
	}
	else {
		y=n/10%10;
		z=n/100;
	}
	int srr[3]={x,y,z};
	int max,min,next;
	paixu(srr);
	max=srr[2]*100+srr[1]*10+srr[0];
	min=srr[0]*100+srr[1]*10+srr[2];
	next=max-min;
	printf("%d - %d = %d\n",max,min,next);
	if(next!=495)heidong(next);
}
int main(){
	int num;
	while(scanf("%d",&num)!=EOF){
		heidong(num);
		getchar();
	}
}
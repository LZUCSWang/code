#include<stdio.h>
int main(void){
	char datas[81];
	char b[81];
	int i=0,k=0,max,temp,j;
	while((datas[i]=getchar())!='\n'){
		if(datas[i]>='0'&&datas[i]<='9'){
		b[k]=datas[i];
		k++;
		}
		i++;
	}
	datas[i]='0';
	b[k]='0';
	for(k=0;k<i-1;k++){
		max=k;
		for(j=k+1;j<i;j++){
			if(b[j]>b[max]){
				max=j;
			}
		}
		temp=datas[max];
		datas[max]=datas[k];
		datas[k]=temp;
	}
	for(i=0;b[i]!='0';i++){
	printf("%d",b[i]);
	}
	return 0;
}

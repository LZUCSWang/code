#include<stdio.h>
int main(void){
	char datas[81];
	char b[81];
	int i,k=0,temp;
	while((datas[i]=getchar())!='\n'){
		if(datas[i]>='0'&&datas[i]<='9'){
		b[k]=datas[i];
		k++;
		}
		i++;
	}
	datas[i]='\0';
	b[k]='\0';
	for(k=0;b[k]!='\0';k++){
		for(i=k+1;b[i]!='\0';i++){
			if(b[k]<b[i]){
		temp=b[k];
		b[k]=b[i];
		b[i]=temp;
	}
		}
	}
	int sum=0;
	for(i=0;b[i]!='\0';i++){
	sum=sum*10+b[i]-'0';
	}
	printf("%d",sum);
	return 0;
}

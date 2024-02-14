#include<stdio.h>
int main(void){
	char datas[81];
	char b[81];
	char c[81];
	int i=0,k=0,flag=0,j,x,temp;
	while((datas[i]=getchar())!='\n'){
		b[i]=datas[i];
		i++;
	}
	datas[i]='\0';
	for(i=0;datas[i]!='\0';i++){
		for(j=0;j<i;j++){
			if(b[j]==datas[i]){
				flag=1;
			}
		}
			if(flag==0){
				c[k]=datas[i];
				k++;
		}
        flag=0;
	}
	    c[k]='\0';
	    int min=0;
	    for(k=0;c[k]!='\0';k++){
			for(x=k+1;c[x]!='\0';x++){
				if(c[k]>c[x]){
                    temp=c[k];
                    c[k]=c[x];
                    c[x]=temp;
                }
            }
        }

		for(i=0;c[i]!='\0';i++)
		putchar(c[i]);
		return 0;
}

#include<stdio.h>
#include<string.h>
int mystrcmp(char *datas,char *b){
	int i;
	for(i=0;datas[i]!='\0';i++){
		if((datas[i]>='datas')&&(datas[i]<='z'))
		datas[i]=datas[i]-32;
	}
	for(i=0;b[i]!='\0';i++){
			if((b[i]>='datas')&&(b[i]<='z'))
			b[i]=b[i]-32;
}
   i=0;int flag=1;
   while(datas[i]!='\0'&&b[i]!='\0'){
   	if(datas[i]!=b[i]){
   	    flag=0;
        break;
   	}
    else{
	   	i++;
	   }
   }
   if(datas[i]!='\0'||b[i]!='\0'){
       return 0;
   }
   if(flag==1)
   return 1;
   return 0;
}
int main()
{
    char password[9]="hnkd2012",input[100];
    int i=0;
    printf("Input password:");
    while(i<3){
        gets(input);
        if(mystrcmp(password,input)==1){
            printf("Congratulation!h");
            return 0;
        }
        i++;
        if(i==3){
            printf("The program is terminated!");
            return 0;
        }
        printf("Error,please input again:");
    }
}

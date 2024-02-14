#include<stdio.h>
#include<string.h>
#include<stdlib.h>
char * convert(char * s, int numRows){
    int len = strlen(s);
    if(len<=2||numRows<=1) return s;    //特殊情况

    int numLines;   //算列数
    if((len-numRows)%(numRows-1)==0){
        numLines = (len-numRows)/(numRows-1)+1;
    }else{
        numLines = (len-numRows)/(numRows-1)+2;
    }

    char chMap[numRows][numLines];
    memset(chMap,0,sizeof(chMap));
    int i = 1;  //第一个字符直接赋值从第二个开始
    int row = 0,line = 0;
    while(line<numLines){
        if(line%2==0){  //偶数列从上到下
            row = 1;
            while(s[i] && row<numRows){ 
                chMap[row][line] =s[i];
                i++;
                row++;
            }
        }else{      //奇数列从下到上
            row = numRows-2;
            while(row>=0 && s[i]){
                chMap[row][line] =s[i];
                i++;
                row--;
            }
        }
        line++;
    }

    char *datas = (char *)malloc(len+1);
    datas[0] = s[0];
    i = 1;
    for(row = 0;row<numRows;row++){     //二维数组写入一维数组
        for(line = 0;line<numLines;line++){
            if(chMap[row][line]){
                datas[i] = (char)chMap[row][line];
                i++;
            }  
        }
    }
    datas[len] = '\0';
    return datas;
}
int main(){
    char s[]="PAYPALISHIRING";
    printf("%s",convert(s,4));
}
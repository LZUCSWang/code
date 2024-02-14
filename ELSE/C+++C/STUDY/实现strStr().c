#include<stdio.h>
int strStr(char * haystack, char * needle){
    if(strlen(needle)==0||strlen(needle)>strlen(haystack))return 0;
    int hap=0,nep=0;
    while(hap<strlen(haystack)&&nep<strlen(needle)){
        if(haystack[hap]==needle[nep]){
            hap++;nep++;
        }
        else {
            hap=hap-nep+1;
            nep=0;
        }
    }
    if(nep==strlen(needle))return hap;
    else return -1;
}
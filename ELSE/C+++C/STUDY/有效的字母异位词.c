#include<stdbool.h>
bool isAnagram(char * s, char * t){
    if(strlen(s)!=strlen(t))return false;
    int hash1[150]={0},hash2[150]={0};
    for(int i=0;i<strlen(s);i++){
        hash1[s[i]]++;
    }
    for(int i=0;i<strlen(t);i++){
        hash2[t[i]]++;
    }
    for(int i=30;i<123;i++){
        if(hash1[i]!=hash2[i])return false;
    }
    return true;
}
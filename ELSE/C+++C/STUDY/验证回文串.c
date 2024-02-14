#include<stdbool.h>
#include<string.h>
bool isPalindrome(char * s){
    int right=strlen(s)-1,left=0;
    while(left<right){
        if(!isalpha(s[left]))left++;
        else if(!isalpha(s[right]))right++;
        else if(isalpha(s[left])&&isalpha(s[right])&&(tolower(s[left])==tolower(s[right])));
        else return false;
    }
    return true;
}
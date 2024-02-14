#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ÔÚstartÓëendÖĞËÑË÷Æ¥Åä 
int fun(char *str, int start, int end)
{
    char chLeft;        // ×óÀ¨ºÅ
    char chRight;       // ÓÒÀ¨ºÅ
    while((start<=end) && (str[start] != '\0'))
    {
        switch(str[start])
        {
            case '(':
                chLeft = str[start];
                chRight = ')';
                break;
            case '[':
                chLeft = str[start];
                chRight = ']';
                break;
            case '{':
                chLeft = str[start];
                chRight = '}';
                break;

            case ')':
            case ']':
            case '}':
                return 0;
            default:
                chLeft = '\0';
                break;
        }
        if(str[start] == chLeft)
        {
            int a = 1;
            int b=0;
            int t = start+1;
            while((t<=end) && (str[t] != '\0')) // ËÑË÷Æ¥ÅäµÄÓÒÀ¨ºÅ 
            {
                if(str[t] == chLeft)
                    ++a;
                if(str[t] == chRight)
                    ++b;
                if(b>a)
                    return 0;
                if(a == b)      // ÔÙ¶ÔÆ¥ÅäÀ¨ºÅÀïÃæµÄÀ¨ºÅ½øĞĞÆ¥Åä 
                {
                    if(0 == fun(str, start+1, t-1)) // µİ¹éµ÷ÓÃ 
                        return 0;
                    start=t;
                    break;
                }
                ++t;
            }
            if(a>b)
                return 0;
        }
        ++start;
    }
    return 1;
}

int main(void){
    char str[1024];
    fgets(str,1024,stdin);
    int length = strlen(str);
    int i = fun(str, 0, length-1);
    if(i == 1){
        printf("À¨ºÅÆ¥Åä£¡\n");
    }else{
        printf("À¨ºÅ²»Æ¥Åä£¡\n");
    }
    return 0;
}

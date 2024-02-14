/*Symbol       Value
I             1
V             5
X             10
L             50
C             100
D             500
M             1000*/
int match(char ch){
    switch(ch){
        case 'I':return 1;
        case 'V':return 5;
        case 'X':return 10;
        case 'L':return 50;
        case 'C':return 100;
        case 'D':return 500;
        case 'M':return 1000;
    }
    return -1;
}
int romanToInt(char * s){
    int cnt=0;
    for(int i=0;i<strlen(s)-1;i++){
        if(match(s[i])>=match(s[i+1])){
            cnt+=match(s[i]);
        }
        else {
            cnt=cnt+match(s[i+1])-match(s[i]);
            i++;
        }
    }
    return cnt;
}
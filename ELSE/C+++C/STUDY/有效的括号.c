bool isValid(char * s){
    char stack[strlen(s)];
    int ps=0,i=0;
    while(s[i]!='\0'){
        if(s[i]=='('||s[i]=='['||s[i]=='{'){
            stack[ps++]=s[i++];
        }
        else if(s[i]==')'&&stack[ps-1]=='('||s[i]=='}'&&stack[ps-1]=='{'||s[i]==']'&&stack[ps-1]=='['){
            ps--,i++;
        }
    }
    if(ps>=0)return false;
    return true;
}
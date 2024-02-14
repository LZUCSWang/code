int firstUniqChar(char * s){
    int hash[200]={0},i;char target=0;
    for(i=0;i<strlen(s);i++){
        hash[s[i]]++;
    }
    for(i=0;i<strlen(s);i++){
        if(hash[s[i]]==1)return i;
    }
    return -1;
}
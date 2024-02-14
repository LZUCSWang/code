void reverseString(char* s, int sSize){
    int left=0,right=sSize-1;char t;
    while(left<right){
        t=s[left];
        s[left]=s[right];
        s[right]=t;
        left++,right++;
    }
}
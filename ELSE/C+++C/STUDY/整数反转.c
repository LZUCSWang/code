int reverse(int x){
    int t,sigle;long int cnt=0;
    t=(x>0)?x:-x;
    while(t>0){
        sigle=t%10;
        cnt=cnt*10+sigle;
        if(cnt>2147483647||cnt<-2147483646)return 0;
        t/=10;
    }
    return (x>=0)?(int)cnt:(int)cnt;
}
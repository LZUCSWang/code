int climbStairs_digui(int n){
    if(n==1)return 1;
    if(n==2)return 2;
    return climbStairs(n-1)+climbStairs(n-2);
}
int climbStairs_feidigui(int n){
    int arr[10000];
    int p=0;
    arr[1]=1;
    arr[2]=2;
    for(p=3;p<=n;p++){
        arr[p]=arr[p-1]+arr[p-2];
    }
    return arr[n];
}
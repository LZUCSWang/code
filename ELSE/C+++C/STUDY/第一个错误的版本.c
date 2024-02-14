// The API isBadVersion is defined for you.
bool isBadVersion(int version);

int firstBadVersion(int n) {
    int left=1,right=n;
    int mid;
    while(left<right){
        mid=(left+right)/2;
        if(isBadVersion(mid)&&!isBadVersion(mid-1)){
            return mid;
        }
        if(isBadVersion(mid)){
            right=mid;
        }
        if(!isBadVersion(mid)){
            left=mid;
        }
    }
}
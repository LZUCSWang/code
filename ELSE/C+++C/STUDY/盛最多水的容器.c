int maxArea(int* height, int heightSize){
    int left=0,right=heightSize-1;
    int max=0,cnt=0;
    while(left<right){
        max=(right-left)*(height[left]>height[right])?height[right]:height[left];
        cnt=(max>cnt)?max:cnt;
        if(height[left]>height[right])right--;
        else left++;
    }
    return cnt;
}
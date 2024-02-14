
void merge(int* nums1, int nums1Size, int m, int* nums2, int nums2Size, int n){
    if(m==0){
        for(int i=0;i<n;i++){
            nums1[i]=nums2[i];
        }
    }
    int *nums3=(int*)malloc(sizeof(int)*nums1Size);
    int p1=m-1,p2=n-1,p3=nums1Size-1;
    else{    while(p1>=0||p2>=0){
            if(p1>=0&&(p2<0||nums1[p1]>nums2[p2])){
                nums3[p3--]=nums1[p1--];
            }
            else{
                nums3[p3--]=nums2[p2--];
            }
        }
        for(p3=0;p3<nums1Size;p3++){
            nums1[p3]=nums3[p3];
        }}
}
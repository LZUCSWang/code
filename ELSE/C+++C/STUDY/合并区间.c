/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** merge(int** intervals, int intervalsSize, int* intervalsColSize, int* returnSize, int** returnColumnSizes){
    int *cnt=(int *)malloc(sizeof(int)*(*returnSize));
    for(int i=0;i<*intervalsColSize;i++){
        if(intervals[i][1]>=intervals[i+1][0]){
            cnt[i][0]=intervals[i][0];
            cnt[i][1]=intervals[i+1][1];
            i++;
        }
    }
}
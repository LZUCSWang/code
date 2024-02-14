def pro (arr,index,rest):
    if len(arr)==index:
        if rest==0:
            return 1
        else:return 0
    cnt=0
    for zhang in range(1,rest//arr[index]+1):
        cnt+=pro(arr,index+1,rest-zhang*arr[index])
    return cnt
CODE SEGMENT
         assume cs:code
         mov    ax,2
         mov    cx,11;计算2的11次方
    s:   add    ax,ax
         loop   s
         mov    ax,4c00h
         int    21h
CODE ENDS
END

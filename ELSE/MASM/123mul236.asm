CODE SEGMENT
         assume cs:CODE
         mov    ax,236
         mov    cx,123
    s:   add    ax,ax
         loop   s

         mov    ax,4c00H
         int    21H
CODE ENDS
END
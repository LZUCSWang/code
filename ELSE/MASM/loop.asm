
CODE SEGMENT
          assume cs:code
    start:
          mov    ax,0
          add    cx,123
    s:    add    ax,236
          loop   s
          mov    ax,4c00h
          int    21h
CODE ENDS
END start

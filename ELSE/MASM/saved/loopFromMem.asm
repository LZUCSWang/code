
;计算ffff:0006字节单元中的数乘以3，结果存储在dx中
;错误代码，没有注意到要求的是字节单元，所以结果不对
; CODE SEGMENT

;          ASSUME CS:CODE
;          mov    ax, 0ffffH
;          mov    ds,ax
;          mov    cx,3 
;          mov    dx,0
;     s:   add    dx,[0006h]
;          loop   s

;          mov    ax,4c00h
;          int    21h

; CODE ENDS
; end
CODE SEGMENT
         ASSUME CS:CODE
         mov    ax, 0ffffH
         mov    ds,ax
         
         mov    al,[0006h]
         mov    ah,0

         mov    cx, 3
    s:   add    dx,AX
         loop   s

         mov    ax,4c00h
         int    21h
CODE ENDS
end
;字节数据的乘法，不能留进位

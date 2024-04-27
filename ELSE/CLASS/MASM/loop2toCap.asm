assume cs:code,ds:data,ss:stack

data segment
         db 'helloyo',0
         db 'woshias',0
         db 'dianlds',0
         db 'battlef',0
data ends

stack segment

stack ends

code segment
    start:  
            mov   ax,data
            mov   ds,ax
            mov   bx,0
            call  capital
    ; mov  word ptr ds:[dx],10
    ; mov word ptr [dx],10
    ; mov  word ptr [bx+10000],10
            mov   ax,4c00h
            int   21h
    capital:
            push  cx
            push  si
            push  bx
            pushf
            mov   cx,4
    s:      
            push  cx
            mov   si,0
    s0:     
            mov   cl,ds:[bx+si]
            mov   ch,0
            jcxz  ok
            and   byte ptr ds:[bx+si],11011111b
            inc   si
            jmp   short s0
    ok:     
            add   bx,8
            pop   cx
            loop  s
        
            popf
            pop   bx
            pop   si
            pop   cx
            ret
code ends

end start
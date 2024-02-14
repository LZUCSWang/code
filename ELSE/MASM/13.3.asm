assume cs:code
data segment
         db 'conversation',0
data ends
code segment
    start:    mov  ax,0
              mov  es,ax
              mov  word ptr es:[7cH*4],200H
              mov  word ptr es:[7cH*4+2],0
    ;7ch中断类型码指向0:200
        
              mov  cx,offset jmp_nearE-offset jmp_near
              mov  ax,cs
              mov  ds,ax
              mov  si,offset jmp_near
    ;ds:si 指向源地址 jmp_near

              mov  ax,0
              mov  es,ax
              mov  di,200H
    ;es:di 指向目标地址 0:200H
              cld
              rep  movsb
    ;安装程序(进行 jmp_near到0:200H 代码copy)
      

    st2:      mov  ax,data
              mov  ds,ax
              mov  si,0
              mov  ax,0b800h
              mov  es,ax
              mov  di,12*160+72
    st2s:     cmp  byte ptr ds:[si],0
              je   ok
              mov  al,[si]
              mov  es:[di],al
              mov  byte ptr es:[di+1],2                   ;设置颜色
              inc  si
              add  di,2
              mov  bx,offset st2s
              int  7ch

    ok:       mov  ax,4c00H
              int  21H

    jmp_near: push bp
              mov  bp,sp
              mov  ss:[bp+2],bx
              pop  bp
              iret
    ;进行循环因为是near循环段地址不变所以bx直接=st2s

    jmp_nearE:nop

code ends

end start
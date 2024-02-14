mov ax,0x07C0
mov ds,ax
 
jmp near Code
 
;把这5个数据复制到起始地址0x00500的位置
Data:
db 0xAA,0x11,0x22,0x33,0x44
 
Code:
mov ax,0x0050
mov es,ax	       ;目标地址段寄存器初始化
mov di,0	       ;目标地址段偏移寄存器初始化
 
mov ax,0x07c0
mov ds,ax	       ;源地址段寄存器初始化
mov si,Data            ;源地址段偏移寄存器初始化
 
movsb                  ;通过movsb指令复制
 
End:
jmp near End

times 510-($-$$) db 0x00
db 0x55,0xAA
;2.2学号

org 0x7c00
 [bits 16]
 xor ax, ax ; eax = 0
  mov ds, ax
 mov ss, ax
 mov es, ax
 mov fs, ax
 mov gs, ax
    
 ; 初始化栈指针
 mov sp, 0x7c00
 ; mov ax, 0xb000
 ; mov gs, ax
    
 mov ah, 0x03 
 mov bh, 0x00  
 int 0x10 
    
 mov bl, 0x03 ; 青色
 mov al, '2'
 mov ah, 0x09 
 mov cx, 0x01
 int 0x10     
    
 mov ah, 0x02 
 mov bh, 0x00 
 add dl, 1 
 int 0x10 
    
 mov al, '3'
 mov ah, 0x09
 mov cx, 0x01
 int 0x10  
    
 mov ah, 0x02
 mov bh, 0x00  
 add dl, 1  
 int 0x10 
    
 mov al, '3'
 mov ah, 0x09 ;
 mov cx, 0x01 ; 
 int 0x10
    
 mov ah, 0x02 ; 
 mov bh, 0x00 ; 
 add dl, 1 ; 
 int 0x10 ; 
    
 mov al, '3'
 mov ah, 0x09 ; 
 mov cx, 0x01 ; 
 int 0x10 
    
 mov ah, 0x02 ;
 mov bh, 0x00 ; 
 add dl, 1 ; 
 int 0x10 
    
 mov al, '6'
 mov ah, 0x09 
 mov cx, 0x01 
 int 0x10   
    
 mov ah, 0x02 
 mov bh, 0x00 
 add dl, 1 
 int 0x10 
    
 mov al, '0'
 mov ah, 0x09 
 mov cx, 0x01
 int 0x10   
    
 mov ah, 0x02 
 mov bh, 0x00 
 add dl, 1 ; 
 int 0x10 
    
 mov al, '6'
 mov ah, 0x09 
 mov cx, 0x01
 int 0x10   
    
 mov ah, 0x02 
 mov bh, 0x00 
 add dl, 1 ; 
 int 0x10 
    
 mov bl, 0x02 
 mov al, '2'
 mov ah, 0x09 
 mov cx, 0x01
 int 0x10   
    
 mov ah, 0x02 
 mov bh, 0x00 
 add dl, 1 ; 
 int 0x10 
    
    
    
 jmp $ ; 死循环
    
 times 510 - ($ - $$) db 0
 db 0x55, 0xaa
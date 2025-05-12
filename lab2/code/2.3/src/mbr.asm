; 2.3


org 0x7c00
 [bits 16]
 xor ax, ax ; eax = 0

 mov ds, ax
 mov ss, ax
 mov es, ax
 mov fs, ax
 mov gs, ax
    

 mov sp, 0x7c00
 ; mov ax, 0xb000
 ; mov gs, ax
    


       

 kbIOint:
 mov ah, 0x00 ;
 int 0x16 ;
 or al, 0x00 ;
 ; and zf, 0x01;
 jnz input
 jmp kbIOint
    
 input:
    
 mov ah, 0x02 
 mov bh, 0x00 
 add dl, 1 ; 
 int 0x10 ; interrupt
    
 mov ah, 0x09 
 mov cx, 0x01 
 int 0x10   
    
 jmp kbIOint ;
    
 jmp $ ; 死循环
    
 times 510 - ($ - $$) db 0
 db 0x55, 0xaa




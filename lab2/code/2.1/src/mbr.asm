; 中断

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
    
 
    
 ; movecursor:
    
 mov ah, 2 ; 
 mov bh, 0 ; 
 mov dh, 8 ; 
 mov dl, 8 ; 
 int 10h ; interrupt


 mov ah, 3 ;
 mov bh, 0 ;  
 int 10h ; interrupt

 mov ah, 0x04
 
 add dh, 48
 add dl, 48

 mov al,dh
 mov[gs:2*(80*12+8)], ax
 
 mov al,dl
 mov[gs:2*(80*12+10)], ax



    
 ; jmp movecursor
    
 jmp $ ; 死循环
    
 times 510 - ($ - $$) db 0
 db 0x55, 0xaa
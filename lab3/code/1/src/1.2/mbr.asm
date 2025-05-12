; 1.2 mbr.asm

org 0x7c00
[bits 16]
xor ax, ax
mov ds, ax
mov ss, ax
mov es, ax
mov fs, ax
mov gs, ax

mov sp, 0x7c00

; 初始化驱动器号（0x00=软盘，0x80=硬盘）
mov dl, 0x80

; 设置CHS参数（示例：读取柱面0，磁头0，扇区2）
mov cx, 0x0001  ; 柱面号（高8位）和磁头号（低8位）
mov dh, 0x00    ; 磁头号（高8位）
mov cl, 0x02    ; 扇区号（1-63）

; 设置缓冲区地址
mov bx, 0x7e00

; 调用BIOS中断读取扇区
mov ah, 0x02    ; 功能号：读取扇区
mov al, 1       ; 扇区数
int 0x13        ; 调用BIOS

; 检查错误状态
jc disk_error

jmp 0x0000:0x7e00

disk_error:
    jmp $

times 510 - ($ - $$) db 0
db 0x55, 0xaa
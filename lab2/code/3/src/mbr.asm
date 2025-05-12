; 3
; If you meet compile error, try 'sudo apt install gcc-multilib g++-multilib' first

%include "head.include"
; you code here
    mov eax, [a1]
    mov ebx, [a2]
your_if:
; put your implementation here
    cmp eax, 12
    jl lt12 ; if a1 < 12 then
    cmp eax, 24
    jl lt24 ; else if a1 < 24 then
    shl eax, 4  ; a1 = a1 << 4
    mov [if_flag], eax 
    jmp your_while
lt12:
    sar eax, 1 ; a1 /= 2
    inc eax ; a1 ++
    mov [if_flag], eax
    jmp your_while
lt24:
    mov ecx, eax
    sub ecx, 24
    neg ecx 
    imul ecx, eax
    mov [if_flag], ecx
    jmp your_while

your_while:
; put your implementation here
    cmp byte[a2], 12
    jl loopend

    call my_random
    mov ebx, [a2]
    mov ecx, [while_flag]
    mov byte[ecx + ebx - 12] , al
    dec byte[a2]
    jmp your_while

loopend:
%include "end.include"

your_function:
; put your implementation here
    pushad
    mov eax, 0
loop:
    mov ecx, [your_string]
    cmp  byte[ecx + eax], 0
    je funcend
    pushad
    mov  ebx, dword[ecx + eax]
    push ebx
    call print_a_char
    pop ebx
    popad
    add eax, 1
    jmp loop

funcend:
    popad
    ret
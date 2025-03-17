; Architecture: x86_64
; System V AMD64 ABI (Unix-like Systems)

section .text
global kstrlen

kstrlen:
    xor     rax, rax            

.align_loop:
    mov     rsi, rdi            
    add     rsi, rax            
    test    rsi, 7              
    jz      .loop               

    mov     dl, [rsi]           
    test    dl, dl              
    jz      .done               
    inc     rax                 
    jmp     .align_loop

.loop:
    mov     rsi, rdi                    
    add     rsi, rax                    
    mov     rdx, [rsi]                  
    mov     rcx, rdx                    

    sub     rcx, 0x0101010101010101     
    not     rdx                         
    and     rdx, rcx                    
    and     rdx, 0x8080808080808080     
    jnz     .byte_search                

    add     rax, 8                      
    jmp     .loop

.byte_search:
    xor     rdx, rdx            

.byte_loop:
    mov     rsi, rdi            
    add     rsi, rax            
    mov     dl, [rsi + rdx]     
    test    dl, dl              
    jz      .byte_end           
    inc     rdx                 
    cmp     rdx, 8              
    jne     .byte_loop

.byte_end:
    add     rax, rdx         

.done:
    ret
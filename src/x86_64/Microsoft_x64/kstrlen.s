; Architecture: x86_64
; Microsoft x64 Calling Convention

section .text
global kstrlen

; rax = (return) size_t
; rcx =    (1st) const char*    src

kstrlen:        
    push    r12
    push    r13
    mov     r12, 0x0101010101010101
    mov     r13, 0x8080808080808080
    
    mov     rax, rcx

.align:
    test    rcx, 7              
    jz      .aligned_loop               

    mov     r10b, [rcx]           
    test    r10b, r10b              
    jz      .done

    inc     rcx
    jmp     .align

.aligned_loop:
    mov     r10, [rcx]             
    mov     r11, r10 
    sub     r11, r12
    not     r10                    
    and     r10, r11                
    and     r10, r13
    jnz     .unaligned_loop

    add     rcx, 8
    jmp     .aligned_loop

.unaligned_loop:
    mov     r10b, [rcx]
    test    r10b, r10b        
    jz      .done

    inc     rcx      
    jmp     .unaligned_loop

.done:
    pop r13
    pop r12
    sub     rcx, rax
    mov     rax, rcx
    ret
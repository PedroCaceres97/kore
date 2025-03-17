; Architecture: x86_64
; Microsoft x64 Calling Convention

section .text
global kstrcmp

; rax = (return) bool
; rcx =    (1st) const char*    src
; rdx =    (2nd) const char*    dst
kstrcmp:
    push    r12
    push    r13
    mov     r12, 0x0101010101010101
    mov     r13, 0x8080808080808080

    mov     r10, rcx         
    mov     r11, rdx         
    and     r10, 7           
    and     r11, 7           
    cmp     r10, r11      
    je      .align

.unaligned_compare:
    mov     r10, [rcx]
    mov     r11, [rdx]
    cmp     r10, r11
    jne     .nequal

    test    r10, r10
    jz      .equal

    inc     rcx
    inc     rdx
    jmp     .unaligned_compare

.align:
    test    rcx, 7
    jz      .aligned_compare

    mov     r10, [rcx]
    mov     r11, [rdx]
    cmp     r10, r11
    jne     .nequal

    test    r10, r10
    jz      .equal

    inc     rcx
    inc     rdx
    jmp     .align

.aligned_compare:
    mov     r10, [rcx]             
    mov     r11, r10
    sub     r11, r12
    not     r10                    
    and     r10, r11                
    and     r10, r13
    jnz     .unaligned_compare

    mov     r10, [rdx]             
    mov     r11, r10
    sub     r11, r12
    not     r10                    
    and     r10, r11                
    and     r10, r13
    jnz     .unaligned_compare

    mov     r10, [rcx]
    mov     r11, [rdx]
    cmp     r10, r11
    jne     .nequal

    add     rcx, 8
    add     rdx, 8
    jmp     .aligned_compare

.equal:
    mov     eax, 1
    jmp     .done

.nequal:
    mov     eax, 0

.done:
    pop r13
    pop r12
    ret